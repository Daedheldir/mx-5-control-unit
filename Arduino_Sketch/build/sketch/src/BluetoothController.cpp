#include "../include/BluetoothController.h"
#include "../include/LCDController.h"

namespace dh
{
    BluetoothController::BluetoothController() {}

    bool BluetoothController::Init()
    {
        HM10_ELM327.begin(9600);

        //try to connect with obd
        LCDController::Print(0, 0, "BT Init");
        PrintMessage("AT");       //break any active connections
        PrintMessage("AT+ROLE1"); //change role to master
        PrintMessage("AT+IMME1"); //change to wait for connection command
        PrintMessage("AT+RESET"); //restart for changes to take place

        delay(500);

        LCDController::Print(0, 0, "BT Connecting...");
        bool connectionSuccessful = false;

        Serial.println("Flushing BT");
        while (HM10_ELM327.available())
        {
            HM10_ELM327.read();
        }

        PrintMessage("AT+DISC?");
        delay(1000);
        char arr[128];
        HM10_ELM327.readBytes(arr, HM10_ELM327.available());

        Serial.println(arr);

        while (!connectionSuccessful)
        {
            char addressCommand[32];
            sprintf(addressCommand, "AT+CON%s", targetMAC);
            Serial.println(addressCommand);
            PrintMessage(addressCommand); //try to connect
            delay(11000);
            bool newData = ReadData();
            Serial.println(buffer);

            if (!newData)
            {
                LCDController::Print(0, 1, "NO DATA, WAITING");
                delay(2000);
                LCDController::Print(0, 1, "                ");
                continue;
            }
            if (strcmp(buffer, "OK+CONNA") == 0)
            { //if connection accepted
                connectionSuccessful = true;
                LCDController::Print(0, 1, "SUCCESS");
                connectionActive = true;
            }
            else if (strcmp(buffer, "OK+CONNE") == 0)
            {
                connectionSuccessful = false;
                LCDController::Print(0, 1, "ERROR");
                connectionActive = false;
            }
            else if (strcmp(buffer, "OK+CONNF") == 0)
            {
                connectionSuccessful = false;
                LCDController::Print(0, 1, "TIMEOUT");
                connectionActive = false;
            }
            else
            {
                LCDController::Print(0, 1, buffer);
            }
            delay(1000);
        }
    }

    void BluetoothController::GetBuffer(char arr[], size_t arrSize)
    {
        if (arrSize >= BUFFER_LENGTH)
            strncpy(this->buffer, arr, BUFFER_LENGTH);
        else
        {
            Serial.println("ERROR! - passed buffer is too small! Copying only what fits!");
            strncpy(this->buffer, arr, arrSize);
        }
    }

    void BluetoothController::PrintMessage(const char message[])
    {
        HM10_ELM327.println(message);
    }
    bool BluetoothController::ReadData()
    {

        Serial.println("TRY GET DATA");
        delay(100);

        int availableBytes = HM10_ELM327.available();
        Serial.print("Available bytes = ");
        Serial.println(availableBytes);

        if (availableBytes <= 0)
        {
            Serial.println("NO DATA");
            delay(100);
            return false;
        }

        Serial.println("HAS DATA");
        delay(100);
        char message[16];
        sprintf(message, "%d Bytes", availableBytes);
        Serial.println(message);
        delay(100);

        if (availableBytes > BT_BUFFER_SIZE)
        {
            Serial.println("OVERFLOW");
            delay(100);
            Serial.print("Overflow, reading to serial: ");
            Serial.println(HM10_ELM327.readBytes(buffer, availableBytes));
            return false;
        }

        HM10_ELM327.readBytes(buffer, availableBytes);
        return true;
    }
}

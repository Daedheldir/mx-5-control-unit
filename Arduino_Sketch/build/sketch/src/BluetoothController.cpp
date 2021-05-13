#include "../include/BluetoothController.h"
#include "../include/LCDController.h"

namespace dh
{
    BluetoothController::BluetoothController(ConnectionType conType, char targetMAC[])
        : connectionType(conType)
    {
        strncpy(this->targetMAC, targetMAC, 12);
    }

    bool BluetoothController::Init()
    {
        Serial.write("Initializing BT...");
        switch (connectionType)
        {
        case ConnectionType::BT_ELM327:
        {
            activeSerial = &HC05_ELM327;
            activeSerial->begin(9600);

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
            while (activeSerial->available())
            {
                activeSerial->read();
            }

            PrintMessage("AT+DISC?");
            delay(1000);
            char arr[128];
            activeSerial->readBytes(arr, activeSerial->available());

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
            break;
        }
        case ConnectionType::BT_ANDROID:
        {
            activeSerial = &HM10_ANDROID;
            activeSerial->begin(38400);

            Serial.println("Configuring BT...");
            // PrintMessage("AT+RENEW");
            // delay(2000);
            // ReadDataToSerial();
            // PrintMessage("AT+RESET");
            // delay(2000);
            // ReadDataToSerial();
            // PrintMessage("AT+BAUD0"); //set baudRate
            // ReadDataToSerial();

            PrintMessage("AT"); //break any active connections
            delay(100);
            ReadDataToSerial();

            PrintMessage("AT+PSWD?"); //check pairing password
            delay(100);
            ReadDataToSerial();

            PrintMessage("AT+VERSION?"); //check verssion
            delay(100);
            ReadDataToSerial();

            PrintMessage("AT+ADDR?");
            delay(100);
            ReadDataToSerial();

            // PrintMessage("AT+ROLE0"); //change role to master
            // delay(1000);
            // ReadDataToSerial();

            // PrintMessage("AT+IMME1"); //change to wait for connection command
            // delay(1000);
            // ReadDataToSerial();

            // PrintMessage("AT+NAMEOBDAndroid"); //set name
            // delay(1000);
            // ReadDataToSerial();

            // PrintMessage("AT+RESET"); //restart for changes to take place
            // delay(1000);
            // ReadDataToSerial();

            break;
        }
        default:
            break;
        }
        activeSerial->end();
        delay(100);
        activeSerial->begin(9600);
        initialized = true;
    }

    const char *BluetoothController::GetBuffer()
    {
        return buffer;
    }

    void BluetoothController::PrintMessage(const char message[])
    {
        Serial.print("Sending message:");
        Serial.println(message);
        activeSerial->println(message);
    }
    bool BluetoothController::ReadDataToSerial()
    {
        if (ReadData())
        {
            Serial.println(buffer);
            return true;
        }
        return false;
    }
    bool BluetoothController::ReadData()
    {

        //Serial.println("TRY GET DATA");
        delay(100);

        int availableBytes = activeSerial->available();
        //Serial.print("Available bytes = ");
        //Serial.println(availableBytes);

        if (availableBytes <= 0)
        {
            //Serial.println("NO DATA");
            memset(buffer, 0, BT_BUFFER_SIZE);
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
            Serial.println(activeSerial->readBytes(buffer, availableBytes));
            return false;
        }

        activeSerial->readBytes(buffer, availableBytes);
        return true;
    }
}

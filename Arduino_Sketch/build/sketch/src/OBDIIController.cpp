#include "../include/OBDIIController.h"
#include "../include/LCDController.h"
namespace dh
{
    OBDIIController::OBDIIController() {}
    void OBDIIController::Init()
    {
        pinMode(13, OUTPUT);
        digitalWrite(13, LOW);

        LCDController::Print(0, 0, "BT DATA");
        btController.Init();

        //try to estabilish connection with obd
        Serial.println("Attempting to connect to ELM327...");
        LCDController::Clear();
        LCDController::Print(0, 0, "ELM327");
        LCDController::Print(0, 1, "CONNECTING...");

        if (!elm327.begin(HM10_ELM327))
        {
            Serial.println("Couldn't connect to OBD scanner");
            LCDController::Print(0, 1, "ERROR!!! RESTART");

            while (1)
            {
                digitalWrite(13, LOW);
                delay(100);
                digitalWrite(13, HIGH);
                delay(100);
            }
        }

        Serial.println("Connected to ELM327");
        LCDController::Print(0, 1, "CONNECTED");
        delay(500);
    }

    void OBDIIController::Update()
    {
        float tempRPM = elm327.rpm();

        if (elm327.status == ELM_SUCCESS)
        {
            currentRpm = (uint32_t)tempRPM;
            Serial.print("RPM: ");
            Serial.println(currentRpm);
            LCDController::Clear();
            LCDController::Print(0, 0, "RPM");
            LCDController::Print(0, 1, currentRpm);
        }
        else
        {
            Serial.print(F("\tERROR: "));
            Serial.println(elm327.status);

            LCDController::Clear();
            LCDController::Print(0, 0, "ELM327 ERROR");
            LCDController::Print(0, 1, elm327.status);

            delay(100);
        }
    }
}
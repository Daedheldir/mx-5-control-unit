#include "../include/ExhaustController.h"

//on init pwm = 1 then connect brown to calibrate - OPTIONAL, PROBABLY CONF MDE
//disconnect brown
//after that pwm back to 0
//keep brown connected to ground and change pwm to 1
//change state by connecting and disconnecting brown

namespace dh
{
    static bool ExhaustController::calibratedValves = false;
    ExhaustController::ExhaustController() {}
    void ExhaustController::Init()
    {
        calibratedValves = false;

        pinMode(PWR_VALVE_PIN, OUTPUT);
        pinMode(RELAY_CONTROL_PIN, OUTPUT);

        InitValves();
    }
    void ExhaustController::CalibrateValves()
    {
        SetValvesOpen(false);

        SetValvesPWR(false);
        Serial.println("Initialized Exhaust pins");

        delay(100);

        //CALIBRATION, PROBABLY CONFIGURATION MODE

        Serial.println("Enabled pwr");
        SetValvesPWR(true);
        delay(500);
        Serial.println("Enabled control pin, calibration should start");
        SetValvesOpen(true);
        delay(500);
        Serial.println("Disabled control pin");
        SetValvesOpen(false);
        delay(6000);
        Serial.println("Disabled pwr, calibration should be completed");
        SetValvesPWR(false);
        delay(200);

        InitValves();

        calibratedValves = true;
    }
    void ExhaustController::InitValves()
    {
        //Normal Operation
        Serial.println("Enabled control pin");
        SetValvesOpen(true);
        delay(500);
        Serial.println("Enabled PWR, valve should open");
        SetValvesPWR(true);
    }
    void ExhaustController::SetValvesOpen(bool open)
    {
        if (!open)
            digitalWrite(RELAY_CONTROL_PIN, LOW);
        else
            digitalWrite(RELAY_CONTROL_PIN, HIGH);
    }

    void ExhaustController::SetValvesPWR(bool power)
    {
        if (power)
            digitalWrite(PWR_VALVE_PIN, HIGH);
        else
            digitalWrite(PWR_VALVE_PIN, LOW);
    }
}
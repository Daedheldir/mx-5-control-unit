#include "../include/ExhaustController.h"

//on init pwm = 1 then connect brown to calibrate - OPTIONAL, PROBABLY CONF MDE
//disconnect brown
//after that pwm back to 0
//keep brown connected to ground and change pwm to 1
//change state by connecting and disconnecting brown

namespace dh
{
    ExhaustController::ExhaustController() {}
    void ExhaustController::Init()
    {
        pinMode(PWM_VALVE_PIN, OUTPUT);

        pinMode(LEFT_RELAY_CONTROL_PIN, OUTPUT);
        pinMode(RIGHT_RELAY_CONTROL_PIN, OUTPUT);

        SetControlPin(false);

        SetValvesPWMValue(0);
        Serial.println("Initialized Exhaust pins");

        delay(100);

        //CALIBRATION, PROBABLY CONFIGURATION MODE

        Serial.println("Enabled pwm");
        SetValvesPWMValue(1);
        delay(500);
        Serial.println("Enabled control pin, calibration should start");
        SetControlPin(true);
        delay(500);
        Serial.println("Disabled control pin");
        SetControlPin(false);
        delay(10000);
        Serial.println("Disabled pwm, calibration should be completed");
        SetValvesPWMValue(0);
        delay(1000);

        //Normal Operation
        Serial.println("Enabled control pin");
        SetControlPin(true);
        delay(1000);
        Serial.println("Enabled PWM, valve should open");
        SetValvesPWMValue(1);
    }
    void ExhaustController::SetValves(bool open)
    {
        switch (open)
        {
        case false:
            digitalWrite(LEFT_RELAY_CONTROL_PIN, HIGH);
            digitalWrite(RIGHT_RELAY_CONTROL_PIN, LOW);
            digitalWrite(LED_BUILTIN, HIGH);
            break;
        case true:
            digitalWrite(LEFT_RELAY_CONTROL_PIN, LOW);
            digitalWrite(RIGHT_RELAY_CONTROL_PIN, HIGH);
            digitalWrite(LED_BUILTIN, LOW);
            break;
        default:
            break;
        }
    }
    void ExhaustController::SetControlPin(bool status)
    {
        switch (status)
        {
        case false:
            digitalWrite(LEFT_RELAY_CONTROL_PIN, HIGH);
            digitalWrite(RIGHT_RELAY_CONTROL_PIN, HIGH);
            digitalWrite(LED_BUILTIN, HIGH);
            break;
        case true:
            digitalWrite(LEFT_RELAY_CONTROL_PIN, LOW);
            digitalWrite(RIGHT_RELAY_CONTROL_PIN, LOW);
            digitalWrite(LED_BUILTIN, LOW);
            break;
        default:
            break;
        }
    }
    void ExhaustController::SetValvesPWMValue(float val)
    {
        int pinVal = val * 255;
        analogWrite(PWM_VALVE_PIN, pinVal);
    }
}
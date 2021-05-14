#pragma once
#include <Arduino.h>
#include <string.h>

#define LEFT_RELAY_CONTROL_PIN 22
#define RIGHT_RELAY_CONTROL_PIN 23
#define PWM_VALVE_PIN 2

//on init pwm = 1 then connect brown to calibrate
//disconnect brown
//after that pwm back to 0
//keep brown connected to ground and change pwm to 1
//change state by connecting and disconnecting brown

namespace dh
{
    class ExhaustController
    {
    public:
        ExhaustController();
        void Init();

        //float val = <0,1>
        void SetValvesPWMValue(float val);
        void SetValves(bool open);
        void SetControlPin(bool status);
    };
}
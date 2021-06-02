#pragma once
#include <Arduino.h>
#include <string.h>

#define RELAY_CONTROL_PIN 23
#define PWR_VALVE_PIN 25

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

        void CalibrateValves();
        void SetValvesPWR(bool power);
        void SetValvesOpen(bool open);

    private:
        void InitValves();

    private:
        static bool calibratedValves;
    };
}
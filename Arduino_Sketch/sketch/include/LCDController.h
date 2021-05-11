#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

namespace dh
{
    class LCDController
    {
    public:
        static bool Init();
        static void Print(int posX, int posY, char message[]);
        static void Print(int posX, int posY, char message);
        static void Print(int posX, int posY, int message);
        static void Print(int posX, int posY, uint32_t message);
        static void Clear();

    private:
        static LiquidCrystal_I2C lcd; // Set the LCD I2C address
    };

    //LiquidCrystal_I2C LCDController::lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
    //TimerMillis LCDController::timer(500);
} // namespace dh
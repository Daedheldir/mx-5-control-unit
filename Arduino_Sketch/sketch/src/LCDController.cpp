#include "../include/LCDController.h"

namespace dh
{
    LiquidCrystal_I2C LCDController::lcd = LiquidCrystal_I2C(0x27, 16, 2);

    bool LCDController::Init()
    {
        lcd.init();
        lcd.backlight();
    }
    void LCDController::Print(int posX, int posY, char message[])
    {
        lcd.setCursor(posX, posY);
        lcd.print(message);
    }
    void LCDController::Print(int posX, int posY, char message)
    {
        lcd.setCursor(posX, posY);
        lcd.print(message);
    }
    void LCDController::Print(int posX, int posY, int message)
    {
        lcd.setCursor(posX, posY);
        lcd.print(message);
    }
    void LCDController::Print(int posX, int posY, uint32_t message)
    {
        lcd.setCursor(posX, posY);
        lcd.print(message);
    }
    void LCDController::Clear()
    {
        lcd.clear();
    }
    //LiquidCrystal_I2C LCDController::lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
    //TimerMillis LCDController::timer(500);
} // namespace dh
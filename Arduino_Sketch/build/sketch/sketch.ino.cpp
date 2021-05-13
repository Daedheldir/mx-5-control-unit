#include <Arduino.h>
#line 1 "d:\\Programming\\source\\repos\\Arduino\\arduino_car_controller\\Arduino_Sketch\\sketch\\sketch.ino"
#include <LiquidCrystal_I2C.h>
#include "include/LCDController.h"
#include "include/OBDIIController.h"
#include "include/ExhaustController.h"

dh::OBDIIController obdController;
dh::ExhaustController exhaustController;
bool valvesOpen;

#line 10 "d:\\Programming\\source\\repos\\Arduino\\arduino_car_controller\\Arduino_Sketch\\sketch\\sketch.ino"
void setup();
#line 20 "d:\\Programming\\source\\repos\\Arduino\\arduino_car_controller\\Arduino_Sketch\\sketch\\sketch.ino"
void loop();
#line 27 "d:\\Programming\\source\\repos\\Arduino\\arduino_car_controller\\Arduino_Sketch\\sketch\\sketch.ino"
void Init();
#line 10 "d:\\Programming\\source\\repos\\Arduino\\arduino_car_controller\\Arduino_Sketch\\sketch\\sketch.ino"
void setup()
{
  // put your setup code here, to run once:
  Init();

  //obdController.Init();
  exhaustController.Init();
  valvesOpen = false;
}

void loop()
{
  delay(5000);
  exhaustController.SetControlPin(valvesOpen);
  valvesOpen = !valvesOpen;
}

void Init()
{
  Serial.begin(9600);
  Serial.println("Serial initialized");
  dh::LCDController::Init();
}


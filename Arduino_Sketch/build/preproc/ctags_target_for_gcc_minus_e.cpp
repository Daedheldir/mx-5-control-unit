# 1 "d:\\Programming\\source\\repos\\Arduino\\arduino_car_controller\\Arduino_Sketch\\sketch\\sketch.ino"
// #include <LiquidCrystal_I2C.h>
// #include "include/LCDController.h"
// #include "include/OBDIIController.h"
# 5 "d:\\Programming\\source\\repos\\Arduino\\arduino_car_controller\\Arduino_Sketch\\sketch\\sketch.ino" 2
# 6 "d:\\Programming\\source\\repos\\Arduino\\arduino_car_controller\\Arduino_Sketch\\sketch\\sketch.ino" 2

// dh::OBDIIController obdController;
dh::ExhaustController exhaustController;
dh::AndroidCommController androidComms;

void setup()
{
 // put your setup code here, to run once:
 Init();

 //obdController.Init();
}

void loop()
{
 androidComms.Update();
 if (androidComms.GetFlag(dh::AndroidCommController::FLAG_EXHAUST))
  exhaustController.SetControlPin(true);
 else
  exhaustController.SetControlPin(false);
}

void Init()
{
 pinMode(13, 0x1);
 Serial.begin(9600);
 Serial.println("Serial initialized");

 Serial.println("Initializing Exhaust Controller..");
 exhaustController.Init();

 Serial.println("Initializing Android Comms..");
 androidComms.Init();
 Serial.println("Initialization complete.");
 //dh::LCDController::Init();
}

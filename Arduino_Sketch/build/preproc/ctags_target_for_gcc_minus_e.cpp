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
 if (androidComms.GetFlag(dh::AndroidCommController::FLAG_RECEIVED_DATA))
 {
  UpdateExhaustController();
 }
}

void Init()
{
 pinMode(13, 0x1);
 digitalWrite(13, 0x0);
 Serial.begin(9600);
 Serial.println("Serial initialized");

 Serial.println("Initializing Exhaust Controller..");
 exhaustController.Init();

 Serial.println("Initializing Android Comms..");
 androidComms.Init();
 Serial.println("Initialization complete.");
 //dh::LCDController::Init();
}

void UpdateExhaustController()
{
 if (androidComms.GetFlag(dh::AndroidCommController::FLAG_EXHAUST_CALIBRATE))
 {
  exhaustController.CalibrateValves();
  androidComms.SetFlag(dh::AndroidCommController::FLAG_EXHAUST_CALIBRATE, false);
 }
 if (androidComms.GetFlag(dh::AndroidCommController::FLAG_EXHAUST_VALVE))
  exhaustController.SetValvesOpen(true);
 else
  exhaustController.SetValvesOpen(false);

 if (androidComms.GetFlag(dh::AndroidCommController::FLAG_EXHAUST_POWER))
  exhaustController.SetValvesPWR(true);
 else
  exhaustController.SetValvesPWR(false);
}

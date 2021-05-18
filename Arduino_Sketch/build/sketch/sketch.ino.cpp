#include <Arduino.h>
#line 1 "d:\\Programming\\source\\repos\\Arduino\\arduino_car_controller\\Arduino_Sketch\\sketch\\sketch.ino"
// #include <LiquidCrystal_I2C.h>
// #include "include/LCDController.h"
// #include "include/OBDIIController.h"
#include "include/ExhaustController.h"
#include "include/AndroidCommController.h"

// dh::OBDIIController obdController;
dh::ExhaustController exhaustController;
dh::AndroidCommController androidComms;

#line 11 "d:\\Programming\\source\\repos\\Arduino\\arduino_car_controller\\Arduino_Sketch\\sketch\\sketch.ino"
void setup();
#line 19 "d:\\Programming\\source\\repos\\Arduino\\arduino_car_controller\\Arduino_Sketch\\sketch\\sketch.ino"
void loop();
#line 28 "d:\\Programming\\source\\repos\\Arduino\\arduino_car_controller\\Arduino_Sketch\\sketch\\sketch.ino"
void Init();
#line 11 "d:\\Programming\\source\\repos\\Arduino\\arduino_car_controller\\Arduino_Sketch\\sketch\\sketch.ino"
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
		exhaustController.SetValvesOpen(true);
	else
		exhaustController.SetValvesOpen(false);
}

void Init()
{
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);
	Serial.println("Serial initialized");

	Serial.println("Initializing Exhaust Controller..");
	exhaustController.Init();

	Serial.println("Initializing Android Comms..");
	androidComms.Init();
	Serial.println("Initialization complete.");
	//dh::LCDController::Init();
}


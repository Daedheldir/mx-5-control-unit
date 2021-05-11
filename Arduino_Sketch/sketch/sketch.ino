#include <LiquidCrystal_I2C.h>
#include "include/LCDController.h"
#include "include/OBDIIController.h"
#include "include/ExhaustController.h"

dh::OBDIIController obdController;
dh::ExhaustController exhaustController;
bool valvesOpen;

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

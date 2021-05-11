#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <ELMduino.h>

#include "BluetoothController.h"

namespace dh
{
  class OBDIIController
  {
  public:
    OBDIIController();
    void Init();
    void Update();

  private:
    //bluetooth
    BluetoothController btController;
    char btBuffer[BluetoothController::BT_BUFFER_SIZE];

    //obd
    ELM327 elm327;
    uint32_t currentRpm = 0;
  };

}

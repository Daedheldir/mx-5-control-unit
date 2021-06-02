#include "../include/AndroidCommController.h"
#include "../include/CharArrOperations.h"
namespace dh
{
    static const int8_t AndroidCommController::FLAG_EXHAUST_CALIBRATE = 0x01;
    static const int8_t AndroidCommController::FLAG_EXHAUST_VALVE = 0x02;
    static const int8_t AndroidCommController::FLAG_EXHAUST_POWER = 0x04;
    static const int8_t AndroidCommController::FLAG_RECEIVED_DATA = 0x80;
    static int8_t AndroidCommController::commFlags = 0x0;

    AndroidCommController::AndroidCommController() : btController(ConnectionType::BT_ANDROID, "001DA569021E")
    {
    }
    void AndroidCommController::Init()
    {
        btController.Init();
        commFlags = 0x0;
    }
    void AndroidCommController::Update()
    {
        //try to get messages
        if (!btController.ReadDataToSerial())
        {
            SetFlag(FLAG_RECEIVED_DATA, false);
            return;
        }

        Serial.println("Updating android comm");

        //if data received then decrypt it
        SetFlag(FLAG_RECEIVED_DATA, true);

        //decrypt data
        if (CharArrOperations::Contains(btController.GetBuffer(), BluetoothController::BT_BUFFER_SIZE, BTMSG_EXHAUST_CALIBRATE, BT_COMMAND_SIZE))
        {
            //if buffer contains exhaust on message then turn exhaust on
            SetFlag(FLAG_EXHAUST_CALIBRATE, true);
            Serial.println("Exhaust calibration flag changed to true");
        }

        if (CharArrOperations::Contains(btController.GetBuffer(), BluetoothController::BT_BUFFER_SIZE, BTMSG_EXHAUST_VALVE_ON, BT_COMMAND_SIZE))
        {
            //if buffer contains exhaust on message then turn exhaust on
            SetFlag(FLAG_EXHAUST_VALVE, true);
            Serial.println("Exhaust valve flag changed to true");
        }
        if (CharArrOperations::Contains(btController.GetBuffer(), BluetoothController::BT_BUFFER_SIZE, BTMSG_EXHAUST_VALVE_OFF, BT_COMMAND_SIZE))
        {
            //if buffer contains exhaust off message then turn exhaust off
            SetFlag(FLAG_EXHAUST_VALVE, false);
            Serial.println("Exhaust valve flag changed to false");
        }

        if (CharArrOperations::Contains(btController.GetBuffer(), BluetoothController::BT_BUFFER_SIZE, BTMSG_EXHAUST_POWER_ON, BT_COMMAND_SIZE))
        {
            //if buffer contains exhaust off message then turn exhaust off
            SetFlag(FLAG_EXHAUST_POWER, true);
            Serial.println("Exhaust power flag changed to true");
        }
        if (CharArrOperations::Contains(btController.GetBuffer(), BluetoothController::BT_BUFFER_SIZE, BTMSG_EXHAUST_POWER_OFF, BT_COMMAND_SIZE))
        {
            //if buffer contains exhaust off message then turn exhaust off
            SetFlag(FLAG_EXHAUST_POWER, false);
            Serial.println("Exhaust power flag changed to false");
        }
        //
    }
    void AndroidCommController::SetFlag(int8_t flag, bool state)
    {
        if (state)
        {
            commFlags = commFlags | flag;
        }
        else
        {
            commFlags = commFlags & (~flag);
        }
    }
    bool AndroidCommController::GetFlag(int8_t flag)
    {
        return commFlags & flag;
    }
}
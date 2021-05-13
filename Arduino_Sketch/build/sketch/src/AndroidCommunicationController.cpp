#include "../include/AndroidCommController.h"
#include "../include/CharArrOperations.h"
namespace dh
{
    static const int8_t AndroidCommController::FLAG_EXHAUST = 0x1;
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
            return;

        Serial.println("Updating android comm");
        //if data received then decrypt it

        //decrypt data
        if (CharArrOperations::Contains(btController.GetBuffer(), BluetoothController::BT_BUFFER_SIZE, BTMSG_EXHAUST_ON, BT_COMMAND_SIZE))
        {
            //if buffer contains exhaust on message then turn exhaust on
            commFlags = commFlags | FLAG_EXHAUST;
            Serial.println("Exhaust flag changed to true");
        }
        if (CharArrOperations::Contains(btController.GetBuffer(), BluetoothController::BT_BUFFER_SIZE, BTMSG_EXHAUST_OFF, BT_COMMAND_SIZE))
        {
            //if buffer contains exhaust off message then turn exhaust off
            commFlags = commFlags & (~FLAG_EXHAUST);
            Serial.println("Exhaust flag changed to false");
        }
        //
    }

    bool AndroidCommController::GetFlag(int8_t flag)
    {
        return commFlags & flag;
    }
}
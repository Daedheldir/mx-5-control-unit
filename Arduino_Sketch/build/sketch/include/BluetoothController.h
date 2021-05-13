#pragma once
#include <Arduino.h>
#include <string.h>

#define HC05_ELM327 Serial3
#define HM10_ANDROID Serial2

namespace dh
{
    enum ConnectionType
    {
        BT_ELM327,
        BT_ANDROID
    };

    class BluetoothController
    {
    public:
        BluetoothController(ConnectionType conType, char targetMAC[]);

        bool Init();
        bool ReadData();
        bool ReadDataToSerial();
        //sending data
        void PrintMessage(const char message[]);

        const char *GetBuffer();

        bool AttemptConnection();
        bool IsConnectionActive();

        //member variables
    public:
        static const int BT_BUFFER_SIZE = 32;

    private:
        ConnectionType connectionType;
        HardwareSerial *activeSerial;

        bool initialized = false;
        bool connectionActive = false;

        char buffer[BT_BUFFER_SIZE];

        char targetMAC[12] = "001DA569021E";
    };
}
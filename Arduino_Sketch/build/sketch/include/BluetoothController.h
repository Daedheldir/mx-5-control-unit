#pragma once
#include <Arduino.h>
#include <string.h>

#define HM10_ELM327 Serial3

namespace dh
{
    class BluetoothController
    {
    public:
        BluetoothController();

        bool Init();
        bool ReadData();
        void PrintMessage(const char message[]);
        void GetBuffer(char arr[], size_t arrSize);
        bool AttemptConnection();
        bool IsConnectionActive();

        //member variables
    public:
        static const int BT_BUFFER_SIZE = 16;

    private:
        bool initialized = false;
        bool connectionActive = false;

        char buffer[BT_BUFFER_SIZE];

        const char targetMAC[12] = "001DA569021E";
    };
}
#pragma once
#include "BluetoothController.h"
namespace dh
{
	static const size_t BT_COMMAND_SIZE = 7;
	static const char BTMSG_EXHAUST_CALIBRATE[] = "EXH_C01";
	static const char BTMSG_EXHAUST_POWER_ON[] = "EXH_P01";
	static const char BTMSG_EXHAUST_POWER_OFF[] = "EXH_P00";
	static const char BTMSG_EXHAUST_VALVE_ON[] = "EXH_V01";
	static const char BTMSG_EXHAUST_VALVE_OFF[] = "EXH_V00";

	class AndroidCommController
	{
	public:
		AndroidCommController();
		void Init();
		void Update();
		void SetFlag(int8_t flag, bool state);
		bool GetFlag(int8_t flag);

	public:
		static const int8_t FLAG_EXHAUST_CALIBRATE;
		static const int8_t FLAG_EXHAUST_POWER;
		static const int8_t FLAG_EXHAUST_VALVE;
		static const int8_t FLAG_RECEIVED_DATA;

	private:
		BluetoothController btController;
		char buffer[BluetoothController::BT_BUFFER_SIZE];
		static int8_t commFlags;
	};
}
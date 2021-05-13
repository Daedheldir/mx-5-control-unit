#pragma once
#include "BluetoothController.h"
namespace dh
{
	static const size_t BT_COMMAND_SIZE = 7;
	static const char BTMSG_EXHAUST_ON[] = "EXH_001";
	static const char BTMSG_EXHAUST_OFF[] = "EXH_000";

	class AndroidCommController
	{
	public:
		AndroidCommController();

		void Update();

		bool GetFlag(int8_t flag);

	public:
		static const int8_t FLAG_EXHAUST = 0x1;

	private:
		BluetoothController btController;

		static int8_t commFlags = 0x0;
	};
}
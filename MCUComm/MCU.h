#pragma once
#include "Device.h"
#include "SerialPort.h"
#include "atlstr.h"

//microcontroller class
class MCU
{
private:
	//attributes
	Device Pot;
	Device LED;
	SerialPort Comm;
	CString Port;

public:
	//methods
	MCU();
	~MCU();
	bool ReadPot();
	bool ToggleLED();
};
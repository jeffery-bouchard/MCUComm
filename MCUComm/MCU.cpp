#include "MCU.h"
#include "Device.h"
#include "atlstr.h"
#include <iostream>
#include <string>

//constructor with initializer list
MCU::MCU() : Pot(0xFE, "Volts", 0.0196, 2.4, 3.3), LED(0xFF, "", 1, 0, 1), Comm()
{
	Port = "COM3";
	Comm.Open(Port);
}

//destructor
MCU::~MCU()
{
	Comm.Close();
}

//method to send read potentiometer command to MCU
bool MCU::ReadPot()
{
	//declare variables
	bool Value = false;
	unsigned char Result = 0;
	double potVal = 0;
	bool evalRslt = false;

	//get pot command & units
	unsigned char Command = Pot.GetCommand();
	string Units = Pot.GetUnits();

	//send command
	Value = Comm.Write(Command);
	if (Value == false)
	{
		return false;
	}

	//get result
	Value = Comm.Read(Result);
	if (Value == false)
	{
		return false;
	}
	
	//convert results
	potVal = Pot.Convert(Result);
	cout << "potentiometer reads " << potVal << " " << Units << endl;

	//evaluate results
	evalRslt = Pot.Evaluate(potVal);
	if (evalRslt == false)
	{ 
		cout << "potentiometer is outside limits" << endl;
		return false;
	}

	return true;
}

//method to send toggle LED command to MCU
bool MCU::ToggleLED()
{
	//declare variables
	bool Value = false;
	unsigned char Result = 0;
	unsigned char Command = LED.GetCommand();

	//send command
	Value = Comm.Write(Command);
	if (Value == false)
	{
		return false;
	}

	//read result
	Value = Comm.Read(Result);
	if (Value == false)
	{
		return false;
	}

	return true;
}
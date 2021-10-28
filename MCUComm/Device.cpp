#include <iostream>
#include <string>
#include <unordered_map>
#include "Device.h"
#include "atlstr.h"
#include "windows.h"

using namespace std;

//parameterized constructor
Device::Device(unsigned char command, string units, double convfact, double min, double max)
{
	Command = command;
	Units = units;
	ConvFactor = convfact;
	Limits.insert({"min", min});
	Limits.insert({"max", max});
}

//method to convert return byte from MCU to device value (e.g. volts for pot)
double Device::Convert(unsigned char &result)
{
	double value = result * ConvFactor;
	return value;
}

//get command
unsigned char Device::GetCommand()
{
	return Command;
}

//get units
string Device::GetUnits()
{
	return Units;
}

//method to evalute value against limits
bool Device::Evaluate(double &value)
{
	//get limits
	double Min = Limits.at("min");
	double Max = Limits.at("max");

	//evaluate value
	if ((value < Min) | (value > Max))
	{
		return false;
	}
	else
	{
		return true;
	}
}
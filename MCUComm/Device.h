#pragma once
#include <string>
#include <unordered_map>
#include "atlstr.h"
#include "windows.h"

using namespace std;

//device class for MCU components
class Device
{
private:
	//attributes
	unsigned char Command;
	string Units;
	double ConvFactor;
	unordered_map<string, double> Limits;

public:
	//methods
	Device(unsigned char command, string units, double convfact, double min, double max);
	double Convert(unsigned char &result);
	unsigned char GetCommand();
	string GetUnits();
	bool Evaluate(double &value);
};
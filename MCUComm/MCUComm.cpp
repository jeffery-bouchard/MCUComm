#include <iostream>
#include <string>
#include "MCU.h"

using namespace std;

//declare enumeration
enum command { stop, pot, led, help } cmd;

//method to convert command string to enumeration
command CharCmd(string &Command)
{
	if (Command == "stop") return stop;
	else if (Command == "pot") return pot;
	else if (Command == "led") return led;
	else return help;
}

//main method
int main()
{
	//declare variables/objects
	cmd = help;
	string input = "";
	MCU PIC18;
	bool status = false;

	//loop unit command = stop
	while (cmd != stop)
	{
		//get command
		cout << "Enter command: ";
		getline(cin, input);
		if (!input.empty())
		{
			cmd = CharCmd(input);
		}
		else
		{
			cout << "Invalid command. Enter help for list of commands." << endl;
			continue;
		}

		//evaluate command
		switch (cmd)
		{
		//exit program
		case stop:
			cout << "Exiting program" << endl;
			break;
		//read potentiometer
		case pot:
			status = PIC18.ReadPot();
			cout << boolalpha;
			cout << "return value: " << status << endl;
			break;
		//toggle LED
		case led:
			status = PIC18.ToggleLED();
			cout << boolalpha;
			cout << "return value: " << status << endl;
			break;
		//display help menu
		case help:
			cout << "The following commands are supported:" << endl;
			cout << "   pot  : returns MCU potentiometer measurement in volts" << endl;
			cout << "   led  : toggles LED on MCU" << endl;
			cout << "   stop : exits program" << endl;
			break;
		//default to invalid command, display message
		default:
			cout << "Invalid command. Enter help for list of commands." << endl;
			break;
		}

	}

	return 0;
}
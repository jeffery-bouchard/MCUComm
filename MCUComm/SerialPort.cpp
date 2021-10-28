#include <iostream>
#include <iomanip>
#include "SerialPort.h"
#include "windows.h"
#include "atlstr.h"

using namespace std;

//constructor
SerialPort::SerialPort()
{
	//initialize variables
	hPort = { 0 };
	dcb = { 0 };
	bytesWritten = 0;
	bytesRead = 0;
	timeouts = { 0 };
}

//method to open and configure serial port
bool SerialPort::Open(CString port)
{
	//open serial port
	hPort = CreateFile(
		port,
		GENERIC_READ | GENERIC_WRITE,
		0,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0
	);

	//check if serial port exists
	if (hPort == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			cout << "serial port does not exist" << endl;
			return false;
		}
		else
		{
			cout << "error occured checking serial port" << endl;
			return false;
		}
	}

	//check comm state
	if (!GetCommState(hPort, &dcb))
	{
		cout << "error occured getting comm state" << endl;
		return false;
	}

	//setup serial port
	dcb.BaudRate = CBR_9600;   //9600 BPS
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;

	//set comm state
	if (!SetCommState(hPort, &dcb))
	{
		cout << "error occured setting comm state" << endl;
		return false;
	}

	//set timeouts
	timeouts.ReadIntervalTimeout = 1000;
	timeouts.ReadTotalTimeoutConstant = 5000;
	timeouts.ReadTotalTimeoutMultiplier = 3;
	timeouts.WriteTotalTimeoutConstant = 5000;
	timeouts.WriteTotalTimeoutMultiplier = 3;
	if (!SetCommTimeouts(hPort, &timeouts))
	{
		cout << "error occured setting timeouts" << endl;
		return false;
	}

	return true;
}

//method to read byte over serial port
bool SerialPort::Read(unsigned char& rtnVal)
{
	//declare variables
	unsigned char rtn;
	rtnVal = 0;
	bool Value = false;

	//send read command and evaluate result
	Value = ReadFile(hPort, &rtn, 1, &bytesRead, NULL);
	rtnVal = rtn;
	cout << "bytes read: " << bytesRead << endl;
	if (Value == false)
	{
		cout << "error occured reading return byte" << endl;
		return false;
	}
	cout << "byte read: 0x" << setw(2) << setfill('0') << hex << (int)(rtnVal & 0xff) << endl;

	return true;
}

//method to send byte over serial port
bool SerialPort::Write(unsigned char cmd)
{
	//declare variables
	bool Value = false;

	//send write command and evaluate result
	Value = WriteFile(hPort, &cmd, 1, &bytesWritten, NULL);
	cout << "bytes written: " << bytesWritten << endl;
	if (Value == false)
	{
		cout << "error occured sending command over serial port" << endl;
		return false;
	}

	return true;
}

//method to close serial port connection
void SerialPort::Close()
{
	CloseHandle(hPort);
}
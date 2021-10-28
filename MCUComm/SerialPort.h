#pragma once
#include "atlstr.h"
#include "windows.h"

//serial port class
class SerialPort
{
private:
	//attributes
	HANDLE hPort;
	DCB dcb;
	DWORD bytesWritten;
	DWORD bytesRead;
	COMMTIMEOUTS timeouts;

public:
	//methods
	SerialPort();
	bool Open(CString port);
	bool Read(unsigned char& rtnVal);
	bool Write(unsigned char cmd);
	void Close();
};
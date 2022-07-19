# MCUComm

This project is a console application, written in C++, which communicates with a microcontroller over a serial port. Some simple methods are included for reading a potentiometer and toggling an LED, which are connected to the microcontroller. A UML class diagram is included in this repository to clarify the software architecture. This project demostrates interfacing with external devices. Enhancements could be made by adding additional devices connected to the microconrtoller, or by implementing different communication interfaces such as USB or Ethernet. A handful of unit tests are included for the device class to highlight the C++ unit test framework.

To setup the associated hardware, connect a serial port to a microcontroller over the serial port running the corresponding firmware. Note, the the comm port is hard-coded to 'COM3'. This can easily be changed in the code, or an enhacement could be made to make this a user-selectable feature. This application sends single-byte commands over the serial port, and reads back single-byte responses. The included commands are 0xFE for reading a potentiometer, and 0xFF for toggling an LED.

To run the software, launch the application and type the desired command into the prompt. A 'help' command is included, along with 'pot' for reading the potentiometer, and 'led' for toggling the LED. Entering 'stop' exits the program.

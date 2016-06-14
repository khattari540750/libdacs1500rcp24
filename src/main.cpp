#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include "dacs1500rcp24.hpp"


int main(void)
{
	Dacs1500rcp24 dio(0);
	std::string command;
	std::vector<int> values;

	// device open
	dio.open();

	// lamp on -> off
	command = dio.getDigitalOutPutCommand("800000");
	dio.sendCommand(command);
	sleep(2);
	command = dio.getDigitalOutPutCommand("000000");
	dio.sendCommand(command);
	sleep(2);

	// pwm init
	command = dio.getPWMInitializeCommand(3,20000);
	dio.sendCommand(command);

	// pwm init pos
	values.push_back(1450);
	values.push_back(1450);
	command = dio.getPWMPalseChangeCommand(values);
	dio.sendCommand(command);

	// start
	command = dio.getPWMStartCommand();
	dio.sendCommand(command);

	// changePWM
	for (int i=0; i<10; i++) {
    sleep(1);
    if(i%2==0) {
			values[0] = 2400;
			values[1] = 2400;
			command = dio.getPWMPalseChangeCommand(values);
			dio.sendCommand(command);
		}
    else {
			values[0] = 500;
			values[1] = 500;
			command = dio.getPWMPalseChangeCommand(values);
			dio.sendCommand(command);
		}
	}

	// stop
	command = dio.getPWMStopCommand();
	dio.sendCommand(command);

	// device close
	dio.close();

	return 0;
}

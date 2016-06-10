#include "dacs1500rcp24.hpp"

int main(void)
{
	Dacs1500rcp24 dio;

	dio.open();

	dio.close();
	
	return 0;
}



/*
#include "Dio.hpp"
#include <unistd.h>
#include <iostream>
#include <vector>


int main(void)
{
	Dio dio;
	std:: string command;
	std::vector<int> values;

	dio.open();

	dio.ledOn();
	sleep(1);

	// 初期化
	command = dio.getPWMInitializeCommand();
	dio.sendCommandToDio(command);

	//初期位置
	values.push_back(1450);
	values.push_back(1450);
	dio.changePWMPalse(values);
	//dio.changePWMPalse(0, 1450);

	// start
	command = dio.getPWMStartCommand();
	dio.sendCommandToDio(command);

	// 位置変更
	for (int i=0; i<10; i++) {
    sleep(1);
    if(i%2==0) {
			values[0] = 2400;
			values[1] = 2400;
			dio.changePWMPalse(values);
			//dio.changePWMPalse(0,2400);
		}
    else {
			values[0] = 500;
			values[1] = 500;
			dio.changePWMPalse(values);
			//dio.changePWMPalse(0,500);
		}
	}

	sleep(1);
	dio.ledOff();

	dio.close();

	return 0;
}
*/

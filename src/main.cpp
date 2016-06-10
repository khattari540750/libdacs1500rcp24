//#include "dacs1500rcp24.h"
#include "Dio.hpp"
#include <unistd.h>
#include <iostream>


int main(void)
{
	Dio dio;
	std:: string command;

	dio.open();

	dio.ledOn();
	sleep(2);
	dio.ledOff();
	sleep(1);

	// 初期化
	command = dio.getPWMInitializeCommand();
	dio.sendCommandToDio(command);

	//初期位置
	dio.changePWMPalse(0, 1450);

	// start
	command = dio.getPWMStartCommand();
	dio.sendCommandToDio(command);

	// 位置変更
	for (int i=0; i<10; i++) {
    sleep(1);
    if(i%2==0) {
			dio.changePWMPalse(0,2400);
		}
    else {
			dio.changePWMPalse(0,500);
		}
	}

	dio.close();

	return 0;






	/*
	Dio dio;
	char *command;
	int values[2];

	dio.open();

	dio.ledOn();
	sleep(2);
	dio.ledOff();
	sleep(1);

	// 初期化
	command = dio.getPWMInitializeCommand();
	std::cout << command << std::endl;
	dio.sendCommandToDio(command);

	//初期位置
	values[0] = 1450;
	values[1] = 1450;
	dio.changePWMPalse(values);
	//dio.changePWMPalse(0, 1450);

	// start
	command = dio.getPWMStartCommand();
	std::cout << command << std::endl;
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


	dio.close();

	return 0;
	*/







	/*
	char *code;

	initDio();

	// 初期化
	code = getPWMInitializeCode();
	printf("%s\n", code);
	sendCommandCodeToDio(code);

	// PWMパルス幅の初期位置設定
	code = getPWMPalseChangeUsecCode(0,1450);
	printf("%s\n", code);
	sendCommandCodeToDio(code);

	// PWM出力開始
	code = getPWMStartCode();
	printf("%s\n", code);
	sendCommandCodeToDio(code);

  // PWMパルス幅の変更 繰り返し
  int i;
  for (i=0; i<10; i++) {
    sleep(1);
    if(i%2==0) code = getPWMPalseChangeUsecCode(0,2400);
    else code = getPWMPalseChangeUsecCode(0,500);
  	printf("%s\n", code);
  	sendCommandCodeToDio(code);
  }

	exitDio();
	*/
}

//#include "dacs1500rcp24.h"
#include "Dio.h"
#include <unistd.h>

int main(void)
{
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

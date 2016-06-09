#ifndef __Dio__Dio__
#define __Dio__Dio__

#include <string.h>
#include <iostream>
#include "ftd2xx.h"

// #define PWM_OPCODE 'Q'
// #define PWM_DEVICE_ID '0'
// #define PWM_CLOCK_PERIOD 1  // 8us 4us 2us 1us 0.5us 0.25us 0.125us 0.0625usの中から指定する
// #define PWM_PALSE_PERIOD 20000  // us単位 パルス周期/クロック周期が4096を超えないように指定する

class Dio {
public:
  void open();
  void close();

  void sendCommandToDio(char* data);
  //char* getPWMInitializeCommand();
  char* getPWMStartCommand();
  char* toHex(unsigned int x);

private:
  FT_HANDLE ftHandle;
  FT_STATUS ftStatus;
  int PWM_PALSE_FREQUENCY;
  char PWM_DEVICE_ID;
  double pwmClockPeriod;
  int pwmPalsePeriod;
  int PWM_CLOCK_FREQUENCY_LIST[];
};

#endif

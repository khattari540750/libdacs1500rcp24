#ifndef __Dio__Dio__
#define __Dio__Dio__

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include "ftd2xx.h"


class Dio {
public:
  void open();
  void close();
  // void changePWMPalse(int ch, int usec);
  // void changePWMPalse(vector<int> usecList);
  // void clearReadMemory(int i);
  void ledOn();
  void ledOff();
  void sendCommandToDio(std::string command);
  // std::string getPWMInitializeCommand();
  std::string getPWMStartCommand();

private:
  std::string toHex(unsigned int x);

private:
  FT_HANDLE ftHandle;
};

#endif











/*
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include "ftd2xx.h"

// #define PWM_OPCODE 'Q'
 #define PWM_DEVICE_ID '0'
// #define PWM_CLOCK_PERIOD 1  // 8us 4us 2us 1us 0.5us 0.25us 0.125us 0.0625usの中から指定する
// #define PWM_PALSE_PERIOD 20000  // us単位 パルス周期/クロック周期が4096を超えないように指定する

class Dio {
public:
  void open();
  void close();
  void changePWMPalse(int ch, int percent);
  void changePWMPalse(int* data);
  void clearReadMemory(int i);
  void ledOn();
  void ledOff();
  void sendCommandToDio(char* data);
  char* getPWMInitializeCommand();
  char* getPWMStartCommand();
  char* toHex(unsigned int x);

private:
  FT_HANDLE ftHandle;
  FT_STATUS ftStatus;
  int PWM_PALSE_FREQUENCY;
  //char PWM_DEVICE_ID;
  double pwmClockPeriod;
  int pwmPalsePeriod;
  int PWM_CLOCK_FREQUENCY_LIST[];
};
*/

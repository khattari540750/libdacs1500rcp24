#ifndef __libdacs1500rcp24__dacs1500rcp24__
#define __libdacs1500rcp24__dacs1500rcp24__


#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "ftd2xx.h"


class Dacs1500rcp24 {
public:
  Dacs1500rcp24();
  Dacs1500rcp24(int deviceID);
  ~Dacs1500rcp24();

  void open();
  void close();

  std::string getPWMInitializeCommand(int pwmCountClockID, int pwmPalsePeriod);
  std::string getPWMStartCommand();
  std::string getPWMStopCommand();
  std::string getPWMPalseChangeCommand(int ch, int usec);
  std::string getPWMPalseChangeCommand(std::vector<int> usecList);

  void sendCommandToDio(std::string command);

private:
  std::string toHex(unsigned int x);

protected:
  FT_HANDLE ftHandle;
  char deviceID;
};


#endif


































/*
#ifndef __libdacs1500rcp24__dacs1500rcp24__
#define __libdacs1500rcp24__dacs1500rcp24__

#include <stdio.h>
#include <string.h>
#include "ftd2xx.h"

#define PWM_OPCODE 'Q'
#define PWM_DEVICE_ID '0'
#define PWM_CLOCK_PERIOD 1  // 8us 4us 2us 1us 0.5us 0.25us 0.125us 0.0625usの中から指定する
#define PWM_PALSE_PERIOD 20000  // us単位 パルス周期/クロック周期が4096を超えないように指定する

void initDio();
void exitDio();
void sendCommandCodeToDio(char*);
char *getPWMPalseChangeCode(unsigned short, unsigned short);
char *getPWMPalseChangeUsecCode(unsigned short, unsigned short);
char *getPWMInitializeCode();
char *getPWMStartCode();
char *toCommandCode(unsigned int);
void connectCommandCode(char*, char*);
char *toHex(unsigned int);



#endif
*/

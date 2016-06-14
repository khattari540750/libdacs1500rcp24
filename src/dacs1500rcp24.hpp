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

  std::string getDigitalOutPutCommand(std::string bitStrings);

  void sendCommand(std::string command);

private:
  std::string toHex(unsigned int x);

protected:
  FT_HANDLE ftHandle;
  char charDeviceID;
  int  intDeviceID;
};


#endif

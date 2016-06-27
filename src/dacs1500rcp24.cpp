#include "dacs1500rcp24.hpp"


Dacs1500rcp24::Dacs1500rcp24() {
  charDeviceID = '0';
  intDeviceID = 0;
}


Dacs1500rcp24::Dacs1500rcp24(int deviceID) {
  intDeviceID = deviceID;

  std::stringstream ss;
  ss << deviceID;
  std::string str = ss.str();
  charDeviceID = str[0];
}


Dacs1500rcp24::~Dacs1500rcp24() {}


void Dacs1500rcp24::open() {

  // FT_Open(intDeviceID, &ftHandle);
  // FT_ResetDevice(ftHandle);
  // FT_SetTimeouts(ftHandle, 1000, 1000);
  // std::cout << "open dacs1500rcp24 device." << std::endl;


  try {
    if(FT_Open(intDeviceID, &ftHandle) != FT_OK) throw("FT_Open Failed");
    if(FT_ResetDevice(ftHandle) != FT_OK) throw("FT_ResetDevice Failed");
    if(FT_SetTimeouts(ftHandle, 1000, 1000) != FT_OK) throw("FT_SetTimeouts Failed");
    std::cout << "open dacs1500rcp24 device." << std::endl;
  }
  catch(char const *str) {
    FT_Close(ftHandle);
    std::cout << "can't open dacs1500rcp24 device." << std::endl;
    std::cout << str << std::endl;
  }
}


void Dacs1500rcp24::close() {
  FT_ResetDevice(ftHandle);
  FT_Close(ftHandle);
  std::cout << "close dacs1500rcp24 device." << std::endl;



  // try {
  //   if(FT_ResetDevice(ftHandle) != FT_OK) throw("FT_ResetDevice Failed");
  //   if(FT_Close(ftHandle) != FT_OK) throw("FT_Close Failed");
  //   std::cout << "close dacs1500rcp24 device." << std::endl;
  // }
  // catch(std::string str) {
  //   std::cout << str << std::endl;
  //   std::cout << "can't close dacs1500rcp24 device normal termination." << std::endl;
  // }
}


std::string Dacs1500rcp24::getPWMInitializeCommand(int pwmCountClockID, int pwmPalsePeriod) {
  int data = 0;
  std::string result(18, ' ');

  data += 1 << 23;
  data += pwmCountClockID << 20;
  data += 0 << 16;
  data += pwmPalsePeriod;

  result[0] = 'Q';
  result[1] = charDeviceID;
  std::string hexcode = toHex(data);
  for (int i = 0; i < 6; i++) result[2 + i] = hexcode[i];
  result[8] = 0x0D;

  data = (data | (1 << 16));

  result[9] = 'Q';
  result[10] = charDeviceID;
  hexcode = toHex(data);
  for (int i = 0; i < 6; i++) result[11 + i] = hexcode[i];
  result[17] = 0x0D;

  return result;
}


std::string Dacs1500rcp24::getPWMStartCommand() {
  std::string result = "Q 00F000&Q001F000 ";
  result[1] = charDeviceID;
  result[17] = 0x0D;
  return result;
}


std::string Dacs1500rcp24::getPWMStopCommand() {
  std::string result = "Q 00E000&Q001E000 ";
  result[1] = charDeviceID;
  result[17] = 0x0D;
  return result;
}


std::string Dacs1500rcp24::getPWMPalseChangeCommand(int ch, int usec) {
  std::string result(9, ' ');
  int c = 0;
  unsigned int a = 0;
  a += (ch < 12 ? 0 : 1) << 16;
  a += (ch % 12) << 12;
  a += (unsigned int)(usec);
  std::string hex = toHex(a);
  result[c++] = 'Q';
  result[c++] = charDeviceID;
  result[c++] = hex[0];
  result[c++] = hex[1];
  result[c++] = hex[2];
  result[c++] = hex[3];
  result[c++] = hex[4];
  result[c++] = hex[5];
  result[c++] = 0x0D;
  return result;
}


std::string Dacs1500rcp24::getPWMPalseChangeCommand(std::vector<int> usecList) {
  std::string result(usecList.size()*9, ' ');
  int c = 0;
  unsigned int a = 0;
  for (int i = 0; i < usecList.size(); i++) {
    a = 0;
    a += (i < 12 ? 0 : 1) << 16;
    a += (i % 12) << 12;
    a += usecList[i];
    std::string hex = toHex(a);
    result[c++] = 'Q';
    result[c++] = charDeviceID;
    result[c++] = hex[0];
    result[c++] = hex[1];
    result[c++] = hex[2];
    result[c++] = hex[3];
    result[c++] = hex[4];
    result[c++] = hex[5];
    result[c++] = '&';
  }
  result[c - 1] = 0x0D;
  return result;
}


std::string Dacs1500rcp24::getDigitalOutPutCommand(std::string bitStrings) {
  std::string result(9, ' ');
  int c = 0;
  result[c++] = 'W';
  result[c++] = charDeviceID;
  result[c++] = bitStrings[0];
  result[c++] = bitStrings[1];
  result[c++] = bitStrings[2];
  result[c++] = bitStrings[3];
  result[c++] = bitStrings[4];
  result[c++] = bitStrings[5];
  result[c++] = 0x0D;
  return result;
}


void Dacs1500rcp24::sendCommand(std::string command) {
  DWORD BytesWriten = 0;

  FT_Write(ftHandle, (char*)command.c_str(), command.length(), &BytesWriten);
  std::cout << command << std::endl;



  // try {
  //   if (FT_Write(ftHandle, (char*)command.c_str(), command.length(), &BytesWriten) != FT_OK) throw("FT_Write Failed");
  //   std::cout << command << std::endl;
  // }
  // catch(std::string str) {
  //     std::cout << str << std::endl;
  //     std::cout << "can't connect" << std::endl;
  // }
}


std::string Dacs1500rcp24::toHex(unsigned int x) {
  std::string result(6, ' ');
  for (int i = 0; i < 6; i++) {
    if (x % 16 >= 10) {
      result[5 - i] = (char)((int)'A' + (x % 16 - 10));
    } else {
      result[5 - i] = (char)((int)'0' + x % 16);
    }
    x = x / 16;
  }
  return result;
}

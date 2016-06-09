#include "Dio.hpp"


void Dio::open() {
  try {
    if(FT_Open(0, &ftHandle) != FT_OK) throw("FT_Open Failed");
    if(FT_ResetDevice(ftHandle) != FT_OK) throw("FT_ResetDevice Failed");
    if(FT_SetTimeouts(ftHandle, 1000, 1000) != FT_OK) throw("FT_SetTimeouts Failed");
    std::cout << "open dio device." << std::endl;
  }
  catch(const char* str) {
    FT_Close(ftHandle);
    std::cout << "can't open dio device." << std::endl;
		std::cout << str << std::endl;
	}
}


void Dio::close() {
  try {
    if(FT_ResetDevice(ftHandle) != FT_OK) throw("FT_ResetDevice Failed");
    if(FT_Close(ftHandle) != FT_OK) throw("FT_Close Failed");
    std::cout << "close dio device." << std::endl;
  }
  catch(const char* str) {
    std::cout << str << std::endl;
    std::cout << "can't close dio device normal termination." << std::endl;
  }
}


char* Dio::toHex(unsigned int x) {
  staic char result[6];
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

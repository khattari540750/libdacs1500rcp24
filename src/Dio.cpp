#include "Dio.hpp"


void Dio::open() {
  try {
    if(FT_Open(0, &ftHandle) != FT_OK) throw("FT_Open Failed");
    if(FT_ResetDevice(ftHandle) != FT_OK) throw("FT_ResetDevice Failed");
    if(FT_SetTimeouts(ftHandle, 1000, 1000) != FT_OK) throw("FT_SetTimeouts Failed");
  }
  catch(const char* str) {
    FT_Close(ftHandle);
    std::cout << "can't open dio device." std::endl;
		std::cout << str << std::endl;
	}
}


void Dio::close() {
  try {
    if(FT_ResetDevice(ftHandle) != FT_OK) throw("FT_ResetDevice Failed");
    if(FT_Close(ftHandle) != FT_OK) throw("FT_Close Failed");
  }
  catch(const char* str) {
    std::cout << str << std::endl;
    std::cout << "can't Connect dio device & failed normal termination" std::endl;
  }
}


char* Dio::toHex(unsigned int x) {
  static char result[7];
	int	i;

	result[6] = '\0';
	for(i = 0; i < 6; i++){
		if(x % 16 >= 10){
			result[(8-1)-i] = 'A' + (x % 16 - 10);
		} else{
			result[(8-1)-i] = '0' + x % 16;
		}
		x = x / 16;
	}
	return result;
}

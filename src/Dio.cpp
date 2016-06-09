#include "Dio.hpp"


void Dio::open() {
  if (FT_Open(0, &ftHandle) == FT_OK) {
    FT_ResetDevice( ftHandle );                     // デバイスリセット
    FT_SetTimeouts( ftHandle, 1000, 1000 );         // タイムアウトの設定
  } else {
    cout << "Connect Failed" << endl;
  }
}


void Dio::close() {
  ftStatus = FT_Close(ftHandle);
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

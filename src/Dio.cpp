#include "Dio.hpp"


void Dio::open() {
  try {
    if(FT_Open(0, &ftHandle) != FT_OK) throw("FT_Open Failed");
    if(FT_ResetDevice(ftHandle) != FT_OK) throw("FT_ResetDevice Failed");
    if(FT_SetTimeouts(ftHandle, 1000, 1000) != FT_OK) throw("FT_SetTimeouts Failed");
    std::cout << "open dio device." << std::endl;
  }
  catch(std::string str) {
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
  catch(std::string str) {
    std::cout << str << std::endl;
    std::cout << "can't close dio device normal termination." << std::endl;
  }
}


// void Dio::changePWMPalse(int ch, int usec);
// void Dio::changePWMPalse(vector<int> usecList);
// void Dio::clearReadMemory(int i);
void Dio::ledOn() {
  std::string result = "W0800000 ";
  result[8] = 0x0D;
  sendCommandToDio(result);
}


void Dio::ledOff() {
  std::string result = "W0000000 ";
  result[8] = 0x0D;
  sendCommandToDio(result);
}


void Dio::sendCommandToDio(std::string command) {
  DWORD BytesWriten = 0;
  char *tmp = (char *)malloc( strlen(command.c_str()) + 1 );
  std::cout << command << std::endl;
  try {
    if (FT_Write(ftHandle, tmp,  strlen(tmp), &BytesWriten) != FT_OK) throw("FT_Write Failed");
  }
  catch(std::string str) {
      std::cout << str << std::endl;
      std::cout << "can't connect" << std::endl;
  }
}
// std::string Dio::getPWMInitializeCommand();


std::string Dio::getPWMStartCommand() {
  std::string result = "Q000F000&Q001F000 ";
  result[17] = 0x0D;
  return result;
}


std::string Dio::toHex(unsigned int x) {
  std::string result = "      ";
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















/*
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


void Dio::changePWMPalse(int ch, int percent) {
  static char bdata[9];
  int c = 0;
  unsigned int a = 0;

  a += (ch < 12 ? 0 : 1) << 16;
  a += (ch % 12) << 12;

  //a += (unsigned int)(percent * pwmPalsePeriod / pwmClockPeriod / 100);
  a += (unsigned int)(percent);
  char* hex = toHex(a);
  bdata[c++] = 'Q';
  bdata[c++] = PWM_DEVICE_ID;
  bdata[c++] = hex[0];
  bdata[c++] = hex[1];
  bdata[c++] = hex[2];
  bdata[c++] = hex[3];
  bdata[c++] = hex[4];
  bdata[c++] = hex[5];
  bdata[c++] = 0x0D;
  sendCommandToDio(bdata);
}


void Dio::changePWMPalse(int* data) {
  char* bdata;
  bdata = (char *)malloc( sizeof(char) * sizeof(data) );
  int c = 0;
  unsigned int a = 0;

  for (int i = 0; i < sizeof(data); i++) {
    a = 0;
    a += (i < 12 ? 0 : 1) << 16;
    a += (i % 12) << 12;

    // 0～11bit パルス幅の指定
    //a += (unsigned int)(data[i] * pwmPalsePeriod / pwmClockPeriod / 100);
    a += data[i];
    char* hex = toHex(a);
    bdata[c++] = 'Q';
    bdata[c++] = PWM_DEVICE_ID;
    bdata[c++] = hex[0];
    bdata[c++] = hex[1];
    bdata[c++] = hex[2];
    bdata[c++] = hex[3];
    bdata[c++] = hex[4];
    bdata[c++] = hex[5];
    bdata[c++] = '&';
  }
  bdata[c - 1] = 0x0D;
  sendCommandToDio(bdata);

  free(bdata);
}


void Dio::clearReadMemory(int i) {
  char* bdata;
  bdata = (char *)malloc( sizeof( char ) * i );

  try {
    DWORD resive = 0;
    if(FT_Read(ftHandle, bdata, (DWORD)i, &resive) != FT_OK) throw("FT_Read Failed");
  }
  catch(const char* str) {
    std::cout << str << std::endl;
    std::cout << "can't ClearReadMemory." << std::endl;
  }

  free(bdata);
}


void Dio::ledOn() {
  static char result[9];
  strcpy(result, "W0800000");
  result[8] = 0x0D;
  sendCommandToDio(result);
}


void Dio::ledOff() {
  static char result[9];
  strcpy(result, "W0000000");
  result[8] = 0x0D;
  sendCommandToDio(result);
}


void Dio::sendCommandToDio(char* data)
{
  DWORD BytesWriten = 0;
  try {
    if (FT_Write(ftHandle, data, strlen(data), &BytesWriten) != FT_OK) throw("FT_Write Failed");
  }
  catch(const char* str) {
      std::cout << str << std::endl;
      std::cout << "can't connect" << std::endl;
  }
}


char* Dio::getPWMInitializeCommand() {
  int data = 0;
  static char result[18];
  //int clockCode = 7;
  //
  // pwmPalsePeriod = 1000000 / PWM_PALSE_FREQUENCY;
  // // 解像度が4096以内になるようにクロック周波数を設定
  // while(pwmPalsePeriod * PWM_CLOCK_FREQUENCY_LIST[clockCode] / 1000 > 4096) {
  //   clockCode--;
  //   if (clockCode < 0) throw new Exception("指定したパルス幅には設定できません。");
  // }
  // pwmClockPeriod = 1000.0 / PWM_CLOCK_FREQUENCY_LIST[clockCode];


  int clockCode = 3;


  // 23bit パルス周期およびクロック周波数の指定フラグ
  data += 1 << 23;
  // 22～20bit クロック周期の指定コード
  data += clockCode << 20;
  // 16bit チャンネルグループの指定
  data += 0 << 16;
  // 15～0bit パルス周期の指定
  //data += (int)(pwmPalsePeriod / pwmClockPeriod - 1);
  data += (int)(20000);

  // コマンド文字列に変換しresultに追加する
  result[0] = 'Q';  // PWM出力識別コード
  result[1] = PWM_DEVICE_ID; // デバイスID指定
  char* hexcode = toHex(data); // コマンドの内容を16進数に変換
  for (int i = 0; i < 6; i++) result[2 + i] = hexcode[i];  // 変換結果をコピー
  result[8] = 0x0D;  // 区切りマーク

  // チャンネルグループを指定しなおす
  data = (data | (1 << 16));

  // コマンド文字列に変換しresultに追加する
  result[9] = 'Q';  // PWM出力識別コード
  result[10] = PWM_DEVICE_ID; // デバイスID指定
  hexcode = toHex(data); // コマンドの内容を16進数に変換
  for (int i = 0; i < 6; i++) result[11 + i] = hexcode[i];  // 変換結果をコピー
  result[17] = 0x0D;  // 区切りマーク

  return result;
}


char* Dio::getPWMStartCommand() {
  static char result[18];
  strcpy(result, "Q000F000&Q001F000");
  result[17] = 0x0D;
  return result;
}


char* Dio::toHex(unsigned int x) {
  static char result[6];
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
*/

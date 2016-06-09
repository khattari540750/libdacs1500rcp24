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


void Dio::ledOn() {
  static char result[9];
  strcpy(result, "W0800000");
  result[8] = 0x0D;
  sendCommandToDio(result);
}


void Dio::LedOff() {
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

/*
char* getPWMInitializeCommand() {
  int data = 0;
  static char result[18];
  int clockCode = 7;

  pwmPalsePeriod = 1000000 / PWM_PALSE_FREQUENCY;
  // 解像度が4096以内になるようにクロック周波数を設定
  while(pwmPalsePeriod * PWM_CLOCK_FREQUENCY_LIST[clockCode] / 1000 > 4096) {
    clockCode--;
    if (clockCode < 0) throw new Exception("指定したパルス幅には設定できません。");
  }
  pwmClockPeriod = 1000.0 / PWM_CLOCK_FREQUENCY_LIST[clockCode];


  // 23bit パルス周期およびクロック周波数の指定フラグ
  data += 1 << 23;
  // 22～20bit クロック周期の指定コード
  data += clockCode << 20;
  // 16bit チャンネルグループの指定
  data += 0 << 16;
  // 15～0bit パルス周期の指定
  data += (int)(pwmPalsePeriod / pwmClockPeriod - 1);

  // コマンド文字列に変換しresultに追加する
  result[0] = (byte)'Q';  // PWM出力識別コード
  esult[1] = (byte)PWM_DEVICE_ID; // デバイスID指定
  char[] hexcode = toHex(data); // コマンドの内容を16進数に変換
  for (int i = 0; i < 6; i++) result[2 + i] = (byte)hexcode[i];  // 変換結果をコピー
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
*/

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

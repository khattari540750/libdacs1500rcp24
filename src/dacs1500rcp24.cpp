#include "dacs1500rcp24.hpp"


Dacs1500rcp24::Dacs1500rcp24() {
  deviceID = '0';
}


Dacs1500rcp24::Dacs1500rcp24(int deviceID) {
  std::stringstream ss;
  ss << deviceID;
  string str = ss.str();
  deviceID = str[0];
}


Dacs1500rcp24::~Dacs1500rcp24() {}


void Dacs1500rcp24::open() {
  try {
    if(FT_Open(0, &ftHandle) != FT_OK) throw("FT_Open Failed");
    if(FT_ResetDevice(ftHandle) != FT_OK) throw("FT_ResetDevice Failed");
    if(FT_SetTimeouts(ftHandle, 1000, 1000) != FT_OK) throw("FT_SetTimeouts Failed");
    std::cout << "open dacs1500rcp24 device." << std::endl;
  }
  catch(std::string str) {
    FT_Close(ftHandle);
    std::cout << "can't open dacs1500rcp24 device." << std::endl;
    std::cout << str << std::endl;
  }
}


void Dacs1500rcp24::close() {
  try {
    if(FT_ResetDevice(ftHandle) != FT_OK) throw("FT_ResetDevice Failed");
    if(FT_Close(ftHandle) != FT_OK) throw("FT_Close Failed");
    std::cout << "close dacs1500rcp24 device." << std::endl;
  }
  catch(std::string str) {
    std::cout << str << std::endl;
    std::cout << "can't close dacs1500rcp24 device normal termination." << std::endl;
  }
}


std::string Dacs1500rcp24::getPWMInitializeCommand(int pwmCountClockID, int pwmPalsePeriod) {
  int data = 0;
  std::string result(18, ' ');

  data += 1 << 23;
  data += pwmCountClockID << 20;
  data += 0 << 16;
  data += pwmPalsePeriod;

  result[0] = 'Q';
  result[1] = deviceID;
  std::string hexcode = toHex(data);
  for (int i = 0; i < 6; i++) result[2 + i] = hexcode[i];
  result[8] = 0x0D;

  data = (data | (1 << 16));

  result[9] = 'Q';
  result[10] = deviceID;
  hexcode = toHex(data);
  for (int i = 0; i < 6; i++) result[11 + i] = hexcode[i];
  result[17] = 0x0D;

  return result;
}


std::string Dacs1500rcp24::getPWMStartCommand() {
  std::string result = "Q000F000&Q001F000 ";
  result[1] = deviceID;
  result[17] = 0x0D;
  return result;
}


std::string Dacs1500rcp24::getPWMStopCommand() {
  std::string result = "Q000F000&Q001F000 ";
  result[1] = deviceID;
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
  result[c++] = deviceID;
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
    result[c++] = deviceID;
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


void Dacs1500rcp24::sendCommandToDio(std::string command) {
  DWORD BytesWriten = 0;
  try {
    if (FT_Write(ftHandle, (char*)command.c_str(), command.length(), &BytesWriten) != FT_OK) throw("FT_Write Failed");
    std::cout << command << std::endl;
  }
  catch(std::string str) {
      std::cout << str << std::endl;
      std::cout << "can't connect" << std::endl;
  }
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

















/*
#include "dacs1500rcp24.h"

// デジタル入出力ボードとの通信を初期化
void initDio()
{
    if (FT_Open(0, &ftHandle) == FT_OK) {
		FT_ResetDevice( ftHandle );                     // デバイスリセット
		FT_SetTimeouts( ftHandle, NULL, NULL );         // タイムアウトの設定
	} else {
		printf("通信に失敗しました。\n");
	}
}

// デジタル入出力ボードとの通信を終了
// ※クローズ時に電圧出力がされていた場合そのままになってしまうので注意
void exitDio()
{
    ftStatus = FT_Close(ftHandle);
}

// コマンド文字列をデジタル入出力ボードに送る
void sendCommandCodeToDio(char *code)
{
	DWORD dwTxBytes = 0;
	ftStatus = FT_Write(ftHandle, code, strlen(code), &dwTxBytes);
}


// PWMの初期化をするコマンド文字列を取得する関数
char *getPWMInitializeCode()
{
	unsigned int data = 0;
	static char result[20];
	char *ret;
	int i;
	int clockCode;

	// 指定されたクロック周期に合わせて設定コードを取得する
	switch((int)(PWM_CLOCK_PERIOD*10000)) {
		case 80000: clockCode = 0; break;
		case 40000: clockCode = 1; break;
		case 20000: clockCode = 2; break;
		case 10000: clockCode = 3; break;
		case 5000:  clockCode = 4; break;
		case 2500:  clockCode = 5; break;
		case 1250:  clockCode = 6; break;
		case 625:   clockCode = 7; break;
		default: return NULL;
	}

	// 23bit パルス周期およびクロック周波数の指定フラグ
	data += 1 << 23;
	// 22～20bit クロック周期の指定コード
	data += clockCode << 20;
	// 16bit チャンネルグループの指定
	data += 0 << 16;
	// 15～0bit パルス周期の指定
	data += PWM_PALSE_PERIOD / PWM_CLOCK_PERIOD - 1;

	// コマンド文字列に変換しresultに追加する
	ret = toCommandCode(data);
	connectCommandCode(result, ret);

	// チャンネルグループを指定しなおす
	data = (data & 0xFEFFFF) + (1 << 16);

	// コマンド文字列に変換しresultに追加する
	ret = toCommandCode(data);
	connectCommandCode(result, ret);

	return result;
}


// PWMのパルス幅を変更するコマンド文字列を取得する関数
char *getPWMStartCode()
{
	static char result[20];
	strcpy(result, "Q000F000&Q001F000");
	result[17] = 0x0D;
	result[18] = 0x00;
	return result;
}


// PWMのパルス幅を変更するコマンド文字列を取得する関数
char *getPWMPalseChangeCode(unsigned short ch, unsigned short percent)
{
	unsigned int data = 0;

	// 19～12bit チャンネルの指定
	data += (ch<12?0:1) << 16;
	data += (ch%12) << 12;
	// 0～11bit パルス幅の指定
	data += percent * PWM_PALSE_PERIOD / PWM_CLOCK_PERIOD / 100;

	return toCommandCode(data);
}


// PWMのパルス幅を変更するコマンド文字列を取得する関数
char *getPWMPalseChangeUsecCode(unsigned short ch, unsigned short usec)
{
	unsigned int data = 0;

	// 19～12bit チャンネルの指定
	data += (ch<12?0:1) << 16;
	data += (ch%12) << 12;
	// 0～11bit パルス幅の指定
	data += usec;

	return toCommandCode(data);
}


// コマンドの内容をコマンド文字列に変換する関数
char *toCommandCode(unsigned int data)
{
	static char result[10];
	char *hexcode;
	int i;

	result[0] = PWM_OPCODE;  // PWM出力識別コード
	result[1] = PWM_DEVICE_ID;  // デバイスID指定

	hexcode = toHex(data); // コマンドの内容を16進数に変換
	for(i = 0; i < 6; i++) result[2 + i] = hexcode[2 + i];  // 変換結果をコピー

	result[8] = 0x0D;  // 区切りマーク
	result[9] = 0x00;  // NULL文字

	return result;
}


// コマンド文字列をつなげる関数(cmd1はcmd2を追加できる十分な長さの配列が必要)
void connectCommandCode(char *cmd1, char *cmd2)
{
	int i = 0, j;
	while(cmd1[i] >= 'A' && cmd1[i] <= 'Z') i += 9;
	if(i > 0) cmd1[i-1] = '&';
	for(j = 0; j < 10; j++) cmd1[i + j] = cmd2[j];
}


// 16進数の文字列に変換する関数
// ※16進数で6桁まで対応
char *toHex(unsigned int x)
{
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
*/

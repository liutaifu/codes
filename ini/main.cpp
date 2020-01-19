#include <iostream>
#include <string>
#include "RegKeyIni.h"

using namespace std;

int main()
{
		RegKeyIni *reg = RegKeyIni::GetInstance();//new RegKeyIni();
		char s_con[1024];
		//s_con = (char *)malloc(1024);
		reg->GetContentIni();
		//s_con = reg->GetRegKeyContent();

		memset(s_con,0,sizeof(s_con));
		//reg->ReadPrivateProfileString("LogPath","/opt/log",s_con);
		reg->ReadPrivateProfileString();
		cout << "s_con is "<< s_con << endl;


		reg->UpdatePrivateProfileString("TerminalDbHost","106.15.38.100");
		reg->DeleteInstance();
		return 0;
}

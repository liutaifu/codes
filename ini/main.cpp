#include <iostream>
#include <string>
#include "RegKeyIni.h"

using namespace std;

int main()
{
		RegKeyIni *reg = RegKeyIni::GetInstance();//new RegKeyIni();
		char *s_con;
		s_con = (char *)malloc(1024);
		reg->GetContentIni();
		s_con = reg->GetRegKeyContent();

		cout << "s_con is "<< s_con << endl;
		reg->DeleteInstance();
		return 0;
}

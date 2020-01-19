#include <iostream>
#include <string>
#include "RegKeyIni.h"
#include "parseIni/ParseIni.h"

using namespace std;

RegKeyIni::RegKeyIni()
{
}
RegKeyIni::~RegKeyIni()
{
}
RegKeyIni *RegKeyIni::m_RegKey = NULL;
void RegKeyIni::GetContentIni(/*char *con*/)
{
		int ret = 0;
		//char buf[1024];
		memset(contentIni,0,sizeof(contentIni));
		ret = PrivateProfileOpen(contentIni);
		if(!ret)
				cout << "success!"<< endl;
		else
				cout << "failed!\n"<< endl;
		
		//strcpy(con,buf);
}
RegKeyIni *RegKeyIni::GetInstance()
{
		if(!m_RegKey)
		{
				m_RegKey = new RegKeyIni();
		}
		
		return m_RegKey;
}
char * RegKeyIni::GetRegKeyContent()
{
		return contentIni;
}
void RegKeyIni::DeleteInstance()
{
	if(m_RegKey)
		delete m_RegKey;
}
void RegKeyIni::ReadPrivateProfileString(char *key,char *defPa,char *pBuf)
{
//		const char *keyC = key->c_str();
//		const char *defP = defPa->c_str();
//		char *buf = NULL;
	
//		buf = (char *)malloc(256);
		GetPrivateProfileString(contentIni,NULL,key,defPa,pBuf);

		cout <<key<<" is "<< pBuf<<endl;
}
void RegKeyIni::UpdatePrivateProfileString(char *key,char *defPa)
{
		WritePrivateProfileString(contentIni,NULL,key,defPa);
}

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
void RegKeyIni::ReadPrivateProfileString(string *key,string *defPa,string *pBuf)
{
	GetPrivateProfileString(contentIni,key,defPa,pBuf);
}

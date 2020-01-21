#include <iostream>
#include <string>
#include "RegKeyIni.h"
#include "../parseIni/ParseIni.h"

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
		memset(contentIni,0,sizeof(contentIni));
		ret = PrivateProfileOpen(contentIni);
		if(!ret)
				cout << "success!"<< endl;
		else
				cout << "failed!\n"<< endl;
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

void RegKeyIni::GetPrivateByString(char* reKey,const char* key,const char* def)
{
		char pBuf[256];
		memset(pBuf,0,sizeof(pBuf));
		GetPrivateProfileString(contentIni,NULL,key,def,pBuf);
		strcpy(reKey,pBuf);
}
void RegKeyIni::ReadPrivateProfileString()
{
	logPath = (char*)malloc(256);
	GetPrivateByString(logPath,"LogPath","/opt/log");
	filePreName = (char*)malloc(256);
	GetPrivateByString(filePreName,"FILENAMEPREFIX","Terminal");
	spCenterHost = (char*)malloc(256);
	GetPrivateByString(spCenterHost,"SPCenterHost","10.8.128.56");
	spCenterPort = (char*)malloc(256);
	GetPrivateByString(spCenterPort,"SPCenterPort","9022");
	httpPort = (char*)malloc(256);
	GetPrivateByString(httpPort,"HTTPPort","9092");
	listenNum = (char*)malloc(256);
	GetPrivateByString(listenNum,"ListenNum","10240");
	terminalDbHost = (char*)malloc(256);
	GetPrivateByString(terminalDbHost,"TerminalDbHost","");
	terminalDbUser = (char*)malloc(256);
	GetPrivateByString(terminalDbUser,"TerminalDbUser","");
	terminalDbPass = (char*)malloc(256);
	GetPrivateByString(terminalDbPass,"TerminalDbPass","");
	terminalDbName = (char*)malloc(256);
	GetPrivateByString(terminalDbName,"TerminalDbNAME","");
}
void RegKeyIni::UpdatePrivateProfileString(const char *keyN,char *defP)
{
	WritePrivateProfileString(contentIni,NULL,keyN,defP);
}
char* RegKeyIni::GetLogPath()
{
	return logPath;
}
char* RegKeyIni::GetFilePreName()
{
	return filePreName;
}
char* RegKeyIni::GetSpCenterHost()
{
	return spCenterHost;
}
int RegKeyIni::GetSpCenterPort()
{
	return atoi(spCenterPort);
}
int RegKeyIni::GetHttpPort()
{
	return atoi(httpPort);
}
int RegKeyIni::GetListenNum()
{
	return atoi(listenNum);
}
char* RegKeyIni::GetTerminalDbHost()
{
	return terminalDbHost;
}
char* RegKeyIni::GetTerminalDbUser()
{
	return terminalDbUser;
}
char* RegKeyIni::GetTerminalDbPass()
{
	return terminalDbPass;
}
char* RegKeyIni::GetTerminalDbName()
{
	return terminalDbName;
}

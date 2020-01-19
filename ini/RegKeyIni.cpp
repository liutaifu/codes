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
void RegKeyIni::ReadPrivateProfileString()
{
	char pBuf[256];
	memset(pBuf,0,sizeof(pbuf));
	GetPrivateProfileString(contentIni,NULL,"LogPath","/opt/log",pBuf);
	strcpy(logPath,pBuf);
	GetPrivateProfileString(contentIni,NULL,"LogPath","/opt/log",pBuf);
	strcpy(logPath,pBuf);
	GetPrivateProfileString(contentIni,NULL,"LogPath","/opt/log",pBuf);
	strcpy(logPath,pBuf);
	GetPrivateProfileString(contentIni,NULL,"LogPath","/opt/log",pBuf);
	strcpy(logPath,pBuf);
	GetPrivateProfileString(contentIni,NULL,"LogPath","/opt/log",pBuf);
	strcpy(logPath,pBuf);
	GetPrivateProfileString(contentIni,NULL,"LogPath","/opt/log",pBuf);
	strcpy(logPath,pBuf);
	GetPrivateProfileString(contentIni,NULL,"LogPath","/opt/log",pBuf);
	strcpy(logPath,pBuf);
	GetPrivateProfileString(contentIni,NULL,"LogPath","/opt/log",pBuf);
	strcpy(logPath,pBuf);
	GetPrivateProfileString(contentIni,NULL,"LogPath","/opt/log",pBuf);
	strcpy(logPath,pBuf);
}
void RegKeyIni::UpdatePrivateProfileString(char *keyN,char *defP)
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
char* RegKeyIni::GetSpCenterPort()
{
	return spCenterPort;
char* RegKeyIni::GetHttpPort()
{
	return httpPort;
}
char* RegKeyIni::GetTerminalDbHost()
{
	return terminalDbHost;
}
char* RegKeyIni::GetTerminalDbUser()
{
	return terminalDbUser;
char* RegKeyIni::GetTerminalDbPass()
{
	return terminalDbPass;

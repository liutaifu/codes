#ifndef __PARSEINI__H_
#define __PARSEINI__H_

void WritePrivateProfileString(char *oriBuf,char *firstKey,char *str,char *newName);
void GetPrivateProfileString(char *oriBuf,char *firstKey,char *str,char *defName,char *pbuf);
int PrivateProfileOpen(char *oriBuf/*,char *pname*/);
void CreateLogFile(char *path);
void GetLocalTime(char* time,int format);
#endif

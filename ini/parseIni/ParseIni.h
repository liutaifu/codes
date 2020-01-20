#ifndef __PARSEINI__H_
#define __PARSEINI__H_

void WritePrivateProfileString(char *oriBuf,const char *firstKey,const char *str,char *newName);
void GetPrivateProfileString(char *oriBuf,const char *firstKey,const char *str,const char *defName,char *pbuf);
int PrivateProfileOpen(char *oriBuf/*,char *pname*/);
int CreateLogDir(char *path);
void GetLocalTime(char* time,int format);
#endif

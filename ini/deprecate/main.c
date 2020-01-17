#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "ParseIni.h"
#include <sys/time.h>
#include <time.h>

void OpenAndWrite(char *path)
{
		int i = 0;
		char timeBuf[512];
		FILE *fd = NULL;

		fd = fopen(path,"aw+");

		memset(timeBuf,0,sizeof(timeBuf));
		GetLocalTime(timeBuf,0);
		while('\0' != timeBuf[i++]);
		strcpy(&(timeBuf[i-1])," heloworld!\n");
		fwrite(timeBuf,sizeof(timeBuf),1,fd);

		fclose(fd);
}
int main(int argc,char *argv[])
{
		int i = 0;
	//	char *ret = NULL;
		char ret[1024];
		char buf[256];
		time_t t_n;
		char localTime[128];
		printf("input %d parameters ,argv[1] %s\n",argc,argv[1]);


		memset(buf,0,sizeof(buf));
		memset(ret,0,sizeof(ret));
		memset(localTime,0,sizeof(localTime));
		if(PrivateProfileOpen(ret,"config.ini"))
		{
				perror("PrivateProfileOpen failed!\n");
		}
		else
				printf("PrivateProfileOpen success %s\n",buf);
		GetPrivateProfileString(ret,"LOG","LogPath","log",buf);

		printf("LogPath is %s\n",buf);

		CreateLogFile(buf);
		GetLocalTime(localTime,1);
		while( '\0' != localTime[i++]);
		strcpy(&(localTime[i-1]),"-log.txt");
		i = 0;
		while( '\0' != buf[i++]);
		buf[i - 1] = '/';
		strcpy(&buf[i],localTime);
		printf("file  is %s\n",buf);
		OpenAndWrite(buf);
//		time(&t_n);
//		printf("date is %s\n",ctime(&t_n));

/*
   GetPrivateProfileString(ret,"LOG","HTTPPort","9002",buf);

		printf("HTTPPort is %s\n",buf);
		GetPrivateProfileString(ret,"LOG","TerminalDbHost","10.8.12.34",buf);

		printf("TerminalDbHost is %s\n",buf);

		WritePrivateProfileString(ret,"ATTM","TerminalDbHost","12.12.12.12");
*/

		return 0;
}

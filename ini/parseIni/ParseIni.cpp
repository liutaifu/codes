#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "ParseIni.h"
#include <sys/stat.h>
#include <sys/time.h>

#include "debug.h"
//#include <time.h>

//#define F_MODE S_IRWXU | S_IRUSR｜S_IWUSR ｜S_IXUSR
#define F_MODE  0x777 

//static char iniBuf[1024];

void GetLocalTime(char* tim, int format)
{
		char l_time[128];
		time_t t_n;
		time (&t_n);
		memset(l_time,0,sizeof(l_time));

		if (format)
		{
				strftime(l_time,sizeof(l_time),"%F",localtime(&t_n));
		}
		else
		{
				strftime(l_time,sizeof(l_time),"%F %T",localtime(&t_n));
		}
		strcpy(tim,l_time);
}

int LengthOfString(const char* buf)
{
		int i = 0, j = 0;
		while(buf[i] != '\0')
		{
				j++;
				i++;
		}
		return j;
}

void CreateLogFile(char *path)
{
		if(!access(path,F_OK))
		{
				perror("file is exist!\n");
		}
		else
		{
				if(!mkdir(path,F_MODE))
				{
						perror("create dir success!\n");
				}
				else
				{
						perror("create dir failed!\n");
				}
		}
}
void WritePrivateProfileString(char *oriBuf,const char *firstKey,const char *str,char *newName)
{
		size_t len = 0;
		FILE *fd_r = NULL;
		int index = 0, i =0,j = 0;
		int in_n = 0, in_s = 0;
		char new_Buf[1024];
		char w_buf[512];

		fd_r = fopen("config.ini","w+");
		if( NULL == fd_r )
		{
				perror("open aa.ini falied!\n");
		}
		memset(new_Buf,0,sizeof(new_Buf));


		if( NULL == str )
		{
				perror("input the string is NULL\n");
				return;
		}
//		printf("the default is %s the key is %s\n",oriBuf,str);

/*		while(newName[i] != '\0')
		{
				in_n++;
				printf("newName the length of %c is %d\n",newName[i],in_n);
				i++;
		}
		i = j = 0;
		while(str[i] != '\0')
		{
				index++;
				printf("str the length of %c is %d\n",str[i],index);
				i++;
		}*/
		in_n = LengthOfString(newName);
		index = LengthOfString(str);
#ifdef DEBUG
		printf("the length of %s index is %d in_n is %d\n",str,index,in_n);
#endif
		i = j = 0;
		while(1)
		{
				if(!strncmp(&(oriBuf[j]),str,index))
				{
						i = j;
#ifdef DEBUG
						printf("* oriBuf[%d] is %s\n",j,&(oriBuf[j]));
#endif
						while(oriBuf[j+index+1] != ',')
						{
								j++;
								in_s++;
						}
						j = i;
#ifdef DEBUG
						printf("** oriBuf[%d] is %s\n",j,&(oriBuf[j+index+1]));
#endif
						strncpy(new_Buf,oriBuf,j+index+1);
#ifdef DEBUG
		printf("*** newBuf is %s\n",new_Buf);
#endif
						strcpy(&(new_Buf[j+index+1]),newName);
#ifdef DEBUG
		printf("**** newBuf is %s\n",new_Buf);
#endif
						strcpy(&(new_Buf[j+index+in_n]),&(oriBuf[j+index+1+in_s]));
						
						break;
/*
   						if(oriBuf[j+index+1] == ',')
						{
								strcpy(pbuf,defName);
						printf("defname %s pbuf is %s\n",defName,pbuf);
								break;
						}
						else
						{
								while(oriBuf[j+index+1] != ',')
								{
										pbuf[i] = oriBuf[j+index+1];
										j++;
										i++;
								}
								break;
						}
*/
				}
				else
				{
#ifdef DEBUG
						printf("oriBuf[%d] is %s\n",j,&(oriBuf[j]));
#endif
						j++;
						continue;
				}
		}

		printf("newBuf is %s\n",new_Buf);
		memset(w_buf,0,sizeof(w_buf));
		i = j = 0;
		while( '\0' != new_Buf[i])
		{
				if( ',' != new_Buf[i] )

				{
						w_buf[j] = new_Buf[i];
						i++;
						j++;
				}
				else
				{
						w_buf[j+1] = '\n';
						if ( -1 == fwrite(w_buf,sizeof(w_buf),1,fd_r))
						{
								perror("write error!\n");
						}
						i++;
						j = 0;
						memset(w_buf,0,sizeof(w_buf));
				}
		}
		fclose(fd_r);
}
void GetPrivateProfileString(char *oriBuf,const char *firstKey,const char *str,const char *defName,char *pbuf)
{
		int index = 0;
		int i = 0 ,j = 0;

		if( NULL == str )
		{
				perror("input the string is NULL\n");
				return;
		}
/*
		while(str[i] != '\0')
		{
				index++;
				printf("the length of %c is %d\n",str[i],index);
				i++;
		}
		*/
		index = LengthOfString(str);
#ifdef DEBUG
		printf("the length of %s is %d\n",str,index);

		printf("oriBuf is %s\n",oriBuf);
#endif

		while(1)
		{
				if(!strncmp(&(oriBuf[j]),str,index))
				{
#ifdef DEBUG
						printf("* oriBuf[%d] is %c\n",j,(oriBuf[j+index+1]));
#endif
						if(oriBuf[j+index+1] == ',')
						{
								strcpy(pbuf,defName);
								break;
						}
						else
						{
								while(oriBuf[j+index+1] != ',')
								{
										pbuf[i] = oriBuf[j+index+1];
										j++;
										i++;
								}
								pbuf[i] = '\0';
								break;
						}
				}
				else
				{
#ifdef DEBUG
						printf("oriBuf[%d] is %s\n",j,&(oriBuf[j]));
#endif
						j++;
						continue;
				}
		}
}
int PrivateProfileOpen(char *paBuf/*,char *pname*/)
{
		int ret,i,j;
		FILE *fd = NULL;
		size_t len = 0;
		char *buf = NULL;
		char iniBuf[1024];


		memset(iniBuf,0,sizeof(iniBuf));
		fd = fopen("config.ini","r");
		if (fd == NULL)
		{
				perror("open file failed!\n");
				return -1;
		}

		i = 0;
		while(1)
		{
				j = 0;
				ret = getline(&buf,&len,fd);
				if ( -1 == ret )
				{

						perror("read to the end!\n");
						break;
				}
				else
				{
				//		printf("buf is %s  buf[0] is %d\n",buf,buf[0]);
	
#if 0
						if( '\n' == buf[0])
						{
								printf("this line is empty line\n");
								continue;
						}
#endif
/*						strncpy(&(iniBuf[i]),buf,len);
						i += len;
						iniBuf[i] =',';
*/
						while(buf[j] != '\0')
						{
								//perror("buf transfer to iniBuf\n");
								iniBuf[i++] = buf[j++];
						}
						iniBuf[i - 1] = ',';
				}
		}

		fclose(fd);
		printf("Parse ini is %s\n",iniBuf);
		strcpy(paBuf,iniBuf);
		return 0;
}

/*
int main(int argc,char *argv[])
{
		char *ret = NULL;
		char buf[256];
		char aa[256];
		printf("input %d parameters ,argv[1] %s\n",argc,argv[1]);


		memset(buf,0,sizeof(buf));
		memset(aa,0,sizeof(aa));
		strcpy(aa,"LogPath");
		ret = PrivateProfileOpen("config.ini");
		if(!ret)
		{
				perror("PrivateProfileOpen failed!\n");
		}
		else
				printf("PrivateProfileOpen success %s\n",buf);
		GetPrivateProfileString(ret,"LOG","LogPath","log",buf);

		printf("LogPath is %s\n",buf);
		GetPrivateProfileString(ret,"LOG","HTTPPort","9002",buf);

		printf("HTTPPort is %s\n",buf);
		GetPrivateProfileString(ret,"LOG","TerminalDbHost","10.8.12.34",buf);

		printf("TerminalDbHost is %s\n",buf);

		WritePrivateProfileString(ret,"ATTM","TerminalDbHost","12.12.12.12");



		return 0;
}*/

#include <iostream>
#include <pthread.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Clog.h"
#include "../RegKeyIni/RegKeyIni.h"
#include "../parseIni/ParseIni.h"
#include "../parseIni/debug.h"


using namespace std;

Clog::Clog()
{
}
Clog::~Clog()
{
}

Clog* Clog::m_clog = NULL;
pthread_mutex_t Clog::log_mutex;

void Clog::WriteLog(string *log)
{
		string logs;
		char *timeN = NULL;
		timeN = (char*)malloc(64);
		//GetCurrentTime(timeN,0);
		GetLocalTime(timeN,0);

		logs = filePre + timeN + ":" + *log +"\n";
#ifdef DEBUG
		cout <<"the length is "<<logs.length()<<endl;
#endif
		pthread_mutex_lock(&log_mutex);
		if(logs.length() == fwrite(logs.c_str(),1,logs.length(),fd))
		{
				perror("write logs success!\n");
		}
		else
				perror("write logs failed!\n");
		pthread_mutex_unlock(&log_mutex);
}

void Clog::GetCurrentTime(char *buf,int flag)
{
		time_t ct;
		time(&ct);
		if(flag)
				strftime(buf,64,"%F",localtime(&ct));
		else
				strftime(buf,64,"%F %T",localtime(&ct));
		cout <<"current time is "<<buf<<endl;
}

void Clog::OpenLog()
{
		RegKeyIni *reg = RegKeyIni::GetInstance();
		logPa = (char*)malloc(64);

		logPa = reg->GetLogPath();
#ifdef DEBUG
		cout <<"logPa is "<<logPa<<endl;
#endif
		logPreName = (char*)malloc(64);
		logPreName = reg->GetFilePreName();
#ifdef DEBUG
		cout <<"logPreName is "<<logPreName<<endl;
#endif

		char *timeN = NULL;
		timeN = (char*)malloc(64);
		//GetCurrentTime(timeN,1);
		GetLocalTime(timeN,1);
		fileName = logPa;
		filePre = logPreName;
		fileName = fileName + "/"+ filePre + timeN + "-log.txt";
#ifdef DEBUG
		cout <<"fileName is "<<fileName<<endl;
#endif

		if(CreateLogDir(logPa))
		{
				perror("create log dir failed!\n");
				return;
		}
		else
		{
				perror("log dir is ok!\n");
		}

		fd = fopen(fileName.c_str(),"aw+");
		if(!fd)
		{
				perror("open log file error!\n");
		}
		if(chmod(fileName.c_str(),F_MODE))
		{
				perror("chmod file failed!\n");
		}
		else
				perror("chmod file success!\n");
}

Clog* Clog::ClogInit()
{
		pthread_mutex_init(&log_mutex,NULL);
		if(!m_clog)
				m_clog = new Clog();

		return m_clog;
}

void Clog::DeleteClog()
{
		if(m_clog)
				delete m_clog;
		pthread_mutex_destroy(&log_mutex);
}

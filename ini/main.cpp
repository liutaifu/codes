#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <sys/select.h>
#include "RegKeyIni/RegKeyIni.h"
#include "Clog/Clog.h"
#include "Cabinet/Cabinet.h"

using namespace std;

void *handleAccept(void *arg)
{
		Cabinet *cab = (Cabinet *)arg;
		cab->CabinetSocketAccept();
}

void *handleData(void *arg)
{
		int ret = 0;
		struct timeval tv;
		fd_set cab_fds;
		SocketListIT it;
		Cabinet *cab = (Cabinet *)arg;
		while(1)
		{
#if 0
				if(cab->m_sockList.empty())
				{
						sleep(1);
						continue;
				}
				cout<<"socklist size "<<cab->m_sockList.size()<<endl;
				pthread_mutex_lock(&cab->sock_mutex);
				for(it = cab->m_sockList.begin();it != cab->m_sockList.end();)
				{
						ret = cab->CabinetSocketReceive((*it));
						if(-1 == ret )
						{
								cout<<"cabinet client timeout"<<endl;
								it++;
						}else if( 2 == ret)
						{
								it = cab->m_sockList.erase(it);
						}
						else
						{
								cout<<"TBD"<<endl;
								it++;
						}
				}
				pthread_mutex_unlock(&cab->sock_mutex);
#else
				if(cab->m_sockList.empty())
				{
						sleep(10);
						continue;
				}
				//pthread_mutex_lock(&cab->sock_mutex);
				cab->CabinetSelectAllReceive();
				//pthread_mutex_unlock(&cab->sock_mutex);
#endif
		}
}
int main()
{
		RegKeyIni *reg = RegKeyIni::GetInstance();//new RegKeyIni();
		char s_con[1024];
		//s_con = (char *)malloc(1024);
		reg->GetContentIni();
		cout << "the ini is "<< reg->GetRegKeyContent()<<endl;

		reg->ReadPrivateProfileString();



#if 1
		Cabinet* cab = Cabinet::GetInstance();

		cout <<"socket id "<< cab->m_socket.GenSocket();
		cout <<endl;
		cab->SetCabinetParameter(reg->GetSpCenterPort(),
						reg->GetListenNum());

		cout <<"port is "<<cab->GetPort()<<endl;

		cout <<"listenNum is "<<cab->GetListenNum()<<endl;

		pthread_t thread[10];
		if(!pthread_create(&thread[0],NULL,handleAccept,(void*)cab))
				cout<<"create socketaccept success!\n"<<endl;
		//cab->CabinetSocketAccept();

		pthread_create(&thread[1],NULL,handleData,(void *)cab);

		while(1);
#else
		Clog *log = Clog::ClogInit();
		log->OpenLog();
		string slog = "today is beautul day!";
		log->WriteLog(&slog);
		cout << "logPath is "<< reg->GetLogPath() << endl;
		cout << "fileprename is "<< reg->GetFilePreName() << endl;
		cout << "spcenterhost is "<< reg->GetSpCenterHost() << endl;
		cout << "spcenterport is "<< reg->GetSpCenterPort() << endl;
		cout << "httpport is "<< reg->GetHttpPort() << endl;
		cout << "terminaldbhost is "<< reg->GetTerminalDbHost() << endl;
		cout << "terminaldbuser is "<< reg->GetTerminalDbUser() << endl;
		cout << "terminaldbpass is "<< reg->GetTerminalDbPass() << endl;
		cout << "terminaldbname is "<< reg->GetTerminalDbName() << endl;
#endif

	//	reg->UpdatePrivateProfileString("TerminalDbHost","106.15.38.100");
		reg->DeleteInstance();
#if 0
		log->DeleteClog();
#endif
		return 0;
}

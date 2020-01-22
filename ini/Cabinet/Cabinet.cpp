#include <iostream>
#include <sys/select.h>
#include <pthread.h>

#include "Cabinet.h"
//#include "../Socket/Socket.h"

using namespace std;

Cabinet::Cabinet()
{
}

Cabinet::~Cabinet()
{
}

Cabinet* Cabinet::m_cab = NULL;

Cabinet* Cabinet::GetInstance()
{
		if(!m_cab)
				m_cab = new Cabinet();
		return m_cab;
}

void* Cabinet::CabinetSocketAccept()
{
		int ret = 0;
		struct timeval tv;
		fd_set cab_fds;
		pthread_mutex_init(&sock_mutex,NULL);
		c_sockId = 0;
		c_sockId = m_socket.GenSocket();
		if( -1 == m_socket.GenBind(c_sockId,c_port))
		{
				cout <<"cabinet bind failed!"<<endl;
		}
		if( -1 == m_socket.GenListen(c_sockId,c_listenNum))
		{
				cout <<"cabinet listen failed!"<<endl;
		}
		m_sockList.clear();
		while(1)
		{
				/*
				tv.tv_sec = 1;
				tv.tv_usec = 0;
				FD_ZERO(&cab_fds);
				FD_SET(c_sockId,&cab_fds);
*/
				c_acceptId = 0;
				c_acceptId = m_socket.GenAccept(c_sockId);
				if(c_acceptId < 0)
				{
						cout <<"cabinet accept failed!\n"<<endl;
				}
				if(CheckCabinetExist(c_acceptId))
						continue;
				pthread_mutex_lock(&sock_mutex);
				m_sockList.push_back(&m_socket);
				pthread_mutex_unlock(&sock_mutex);
	/*					
				ret = select(c_acceptId+1,&cab_fds,NULL,NULL,&tv);
				if( -1 == ret )
				{
						cout << "cabinet accept select failed!\n"<< endl;
				}
				if(FD_ISSET(c_sockId,&cab_fds))
				{
						c_acceptId = m_socket.GenAccept(c_sockId);
						if(c_acceptId < 0)
						{
								cout <<"cabinet accept failed!\n"<<endl;
						}
				}
						*/
		}
}

void Cabinet::CabinetSocketSendData(Socket *acc_sock,char *buf,int len)
{
		m_socket.GenSendData(acc_sock->GetAcceptId(),buf,len);
		/*
		int ret = 0;
		ret = send(acc_sock->GetAcceptId(),buf,len,0);
		if( -1 == ret )
		{
				cout<<"send data error!"<<endl;
		}
		 */
}
int Cabinet::CabinetSocketReceive(Socket *acc_sock)
{
		int ret = 0;
		int flag = 0;
		long accept = 0;
		fd_set fds;
		struct timeval tv;
	/*	
		char buf[1024];
		memset(buf,0,sizeof(buf));
		ret = recv(acc_sock->GetAcceptId(),buf,sizeof(buf),0);
		*/
		accept = acc_sock->GetAcceptId();
		FD_ZERO(&fds);
		FD_SET(accept,&fds);

		tv.tv_sec = 1;
		tv.tv_usec = 0;
		ret = select(accept+1,&fds,NULL,NULL,&tv);
		if( 0 == ret )
		{
				cout<<"time is out,no data from client"<<endl;
				return -1;
		}
		else if( -1 == ret )
		{
				cout <<"an error occur!\n"<<endl;
		}
		else
		{
				flag = ret;
				if(FD_ISSET(accept,&fds))
				{
						ret  = m_socket.GenRecvData(accept);
						if( -1 == ret )
						{
							cout<<"recv error!"<<endl;
						}else if(ret)
						{
							cout<<"recv data "<<endl;
						}
						else
						{
							cout<<"client close!\n"<<endl;
							if(1 == flag)
									return 2;
									//DeleteCabinetExist(acc_sock->GetAcceptId());
						}
				}
		}
		return 0;
}
void Cabinet::DeleteCabinetExist(int c_acceptId)
{
		SocketListIT it;
		pthread_mutex_lock(&sock_mutex);
		for(it = m_sockList.begin();it != m_sockList.end();)
		{
				if((*it)->GetAcceptId() == c_acceptId)
						it = m_sockList.erase(it);
				else
						it++;
		}
		pthread_mutex_unlock(&sock_mutex);
}
Socket* Cabinet::CheckCabinetExist(int c_acceptId)
{
		SocketListIT it;
				cout<<"1"<<endl;
		if(m_sockList.empty())
				return NULL;
		for(it = m_sockList.begin();it != m_sockList.end();it++)
		{
				cout<<"2"<<endl;
				if((*it)->GetAcceptId() == c_acceptId)
						return *it;
		}
		return NULL;
}

void Cabinet::DeleteInstance()
{
		if(m_cab)
				delete m_cab;
}
void Cabinet::SetCabinetParameter(int port,int listenNum)
{
		c_port = port;
		c_listenNum = listenNum;
}
int Cabinet::GetPort()
{
		return c_port;
}
int Cabinet::GetListenNum()
{
		return c_listenNum;
}

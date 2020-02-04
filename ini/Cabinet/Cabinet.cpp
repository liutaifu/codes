#include <iostream>
#include <sys/select.h>
#include <pthread.h>
#include <unistd.h>

#include "Cabinet.h"
//#include "../Socket/Socket.h"

using namespace std;

#define DEBUG 1

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
		//fd_set cab_fds;
		SocketListIT it;
		Socket *tempSock;
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
				tempSock = new Socket();
				c_acceptId = 0;
				c_acceptId = tempSock->GenAccept(c_sockId);
				//c_acceptId = m_socket.GenAccept(c_sockId);
				if(c_acceptId < 0)
				{
						cout <<"cabinet accept failed!\n"<<endl;
				}
				if(CheckCabinetExist(c_acceptId))
						continue;
				pthread_mutex_lock(&sock_mutex);
				tempSock->SetAcceptId(c_acceptId);
					
#if DEBUG
				cout<<"insert id "<<tempSock->GetAcceptId()<<endl;
				cout<<"insert clientport "<<tempSock->GetClientPort()<<endl;
#endif

				m_sockList.insert(m_sockList.begin(),tempSock);
				//m_sockList.push_back(&m_socket);
				pthread_mutex_unlock(&sock_mutex);
				tempSock->~Socket();
#if DEBUG
				cout<<"after insert socklist size "<<m_sockList.size()<<endl;
				for(it = m_sockList.begin();it != m_sockList.end();it++)
				{
					cout<<"acceptid "<<(*it)->GetAcceptId()<<endl;
					cout<<"accept clientport "<<(*it)->GetClientPort()<<endl;
				}
#endif
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
				cout<<"time is out,no data from client"<<" acceptId "<<accept<<endl;
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
void Cabinet::CabinetSelectAllReceive()
{
		int ret = 0;
		int flag = 0;
		struct timeval tv;
		fd_set cab_fds;
		SocketListIT it;

		FD_ZERO(&cab_fds);

		/*
		 * 需要优化此处，避免每次都需要FD_SET*/
		pthread_mutex_lock(&sock_mutex);
		for(it = m_sockList.begin();it != m_sockList.end();it++)
		{
			FD_SET((*it)->GetAcceptId(),&cab_fds);
		}
		pthread_mutex_unlock(&sock_mutex);
		it = m_sockList.begin();
		while(1)
		{
			tv.tv_sec = 0;
			tv.tv_usec = 500;

			ret = select((*it)->GetAcceptId()+1,&cab_fds,NULL,NULL,&tv);
			if( -1 == ret )
			{
				cout << "cabinet accept select failed!\n"<< endl;
			}
			else if( 0 == ret )
			{
				sleep(2);
				cout<<"select timeout"<<endl;
				break;
			}
			else
			{
				flag = ret;
				for(it = m_sockList.begin();it != m_sockList.end();++it)
				{
					if(FD_ISSET((*it)->GetAcceptId(),&cab_fds))
					{
						ret  = m_socket.GenRecvData((*it)->GetAcceptId());
						if( -1 == ret )
						{
							cout<<"recv error!"<<endl;
						}
						else if(ret)
						{
							cout<<"recv data "<<endl;
						}
						else
						{
							if(1 == flag)
							{
								sleep(2);
								//cout<<"client close!\n"<<endl;
								//	return 2;客户端断开连接
								DeleteCabinetExist((*it)->GetAcceptId());
								if(m_sockList.empty())
								{
									break;
								}
							}
						}
					}
				}
				break;
			}
		}
/*
 *		while(1)
		{
		}
		*/
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
						++it;
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
				cout<<"id "<< (*it)->GetAcceptId()<<" check id "<<c_acceptId<<endl;
				if((*it)->GetAcceptId() == c_acceptId)
				{
						return *it; //先把acceptid赋值给m_sockList导致if始终成立。
						//解决方式就是初始化不赋值acceptid，在insert之前设置。
				}
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

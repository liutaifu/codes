#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Socket.h"
#include "Config.h"
#include "../parseIni/debug.h"

using namespace std;

Socket::Socket()
{
}
Socket::~Socket()
{
}

Socket* Socket::m_sock = NULL;

int Socket::GenSocket()
{
		int ret = 0;

		ret = socket(AF,SS,0);
		if( -1 == ret )
		{
				cout <<"create socket failed!"<<endl;
		}
		sock_id = ret;
		return ret;
}

int Socket::GenBind(int socket,int port)
{
		struct sockaddr_in addr;
		memset(&addr,0,sizeof(sockaddr_in));

		addr.sin_family = AF;
		addr.sin_addr.s_addr = htonl(INY);
		addr.sin_port = htons(port);
		if(bind(socket,(struct sockaddr*)&addr,sizeof(struct sockaddr)))
		{
				cout <<"bind failed!"<<endl;
				return -1;
		}
		else
				cout <<"bind success!"<<endl;
		return 0;
}

int Socket::GenListen(int socket,int numListen)
{
		if(listen(socket,numListen))
		{
				cout<<"listen failed!\n"<<endl;
				return -1;

		}
		else
				cout<<"listen success!\n"<<endl;
		return 0;
}

int Socket::GenAccept(int socket)
{
		int ret = 0;
		struct sockaddr_in client_addr;
		socklen_t len = sizeof(struct sockaddr);
		memset(&client_addr,0,sizeof(sockaddr_in));

		ret = accept(socket,(struct sockaddr*)&client_addr,&len);
		if( -1 == ret )
				cout<<"accept failed!"<<endl;
		accept_id = ret;
		cout<<"client ip "<<inet_ntoa(client_addr.sin_addr)<<
				" port "<<ntohs(client_addr.sin_port)<<endl;
		return ret;
}

int Socket::GenRecvData(int accept)
{
		int ret = 0;
		char buf[1024];
		fd_set fds;
		struct timeval tv;


		while(1)
		{
				FD_ZERO(&fds);
				FD_SET(accept,&fds);

				tv.tv_sec = 5;
				tv.tv_usec = 0;

				ret = select(accept,&fds,NULL,NULL,&tv);
				if( 0 == ret )
				{
						cout<<"time is pass!"<<endl;
						continue;
				}
				else if( -1 == ret )
						cout<<"an error occur!\n"<<endl;
				else
				{
						if(FD_ISSET(accept,&fds))
						{
								memset(buf,0,sizeof(buf));
								ret = read(accept,buf,sizeof(buf) - 1);
								if( -1 == ret )
								{
										cout <<"read error!\n"<<endl;
										break;
								}
								else
										cout <<"read data is "<<buf<<endl;
						}
				}
		}
}
int Socket::GenSendData(int accept,char *buf,int len)
{
		if( -1 == write(accept,buf,len))
		{
				cout <<"write data error!\n"<<endl;
		}
		else
		{
				cout<<"write data success "<<len<<endl;
		}
}

Socket* Socket::GetInstance()
{
		if(!m_sock)
				m_sock = new Socket();

		return m_sock;
}

void Socket::DeleteInstance()
{
		if(m_sock)
				delete m_sock;
}

int Socket::GenConnect()
{
}

int Socket::GetSocketId()
{
		return sock_id;
}

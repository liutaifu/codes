#include <iostream>


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

void Cabinet::CabinetSocketFunc()
{
		int ret = 0;
		struct timeval tv;
		fd_set cab_fds;
		c_sockId = m_socket.GenSocket();
		if( -1 == m_socket.GenBind(c_sockId,c_port))
		{
				cout <<"cabinet bind failed!"<<endl;
		}
		if( -1 == m_socket.GenListen(c_sockId,c_listenNum))
		{
				cout <<"cabinet listen failed!"<<endl;
		}
		while(1)
		{
				tv.sec = 1;
				tv.usec = 0;
				FD_ZERO(&cab_fds);
				FD_SET(c_sockId,&cab_fds);

				ret = select(c_sockId,&cab_fds,NULL,NULL,&tv);
				if( -1 == ret )
				{
						cout << "cabinet select failed!\n"<< endl;
				}
				if(FD_ISSET(c_sockId,&cab_fds))
				{
						c_acceptId = m_socket.GenAccept(c_sockId);
						if(c_acceptId < 0)
						{
								cout <<"cabinet accept failed!\n"<<endl;
						}
				}
		}
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

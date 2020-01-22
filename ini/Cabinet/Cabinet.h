#include "../Socket/Socket.h"

using namespace std;

class Cabinet
{
		public:
				Cabinet();
				~Cabinet();
				static Cabinet* GetInstance();
				void DeleteInstance();

				void SetCabinetParameter(int port,int listenNum);
				int GetPort();
				int GetListenNum();
				void* CabinetSocketAccept();
				int CabinetSocketReceive(Socket *acc_sock);
				void CabinetSocketSendData(Socket *acc_sock,char *buf,int len);
				Socket* CheckCabinetExist(int c_acceptId);
				void DeleteCabinetExist(int c_acceptId);


				Socket m_socket;
				SocketList m_sockList;
				pthread_mutex_t sock_mutex;
				//RegKeyIni m_regkey;
		private:
				static Cabinet *m_cab;
				int c_port;
				int c_listenNum;
				int c_sockId;
				int c_acceptId;
};

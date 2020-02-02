#include <vector>

using namespace std;

class Socket
{
		public:
				Socket();
				Socket(const Socket & sock);
				Socket & operator=(const Socket & sock);
				~Socket();
				int GenSocket();
				int GenBind(int sock,int port);
				int GenListen(int sock,int numListen);
				int GenAccept(int sock);
				int GenConnect();
				int GenRecvData(int accept);
				int GenSendData(int accept,char* buf,int len);
				static Socket *GetInstance();
				static void DeleteInstance();

				int GetSocketId();
				int GetAcceptId();
				char* GetClientIp();
				int GetClientPort();
				void SetAcceptId(int acceptid);
				void SetClientParameter(void *s_addr);

		private:
				int sock_id;
				int accept_id;
				static Socket *m_sock;
				char *cli_ip;
				int cli_port;
				//需要实现赋值函数和深拷贝
};

typedef vector<Socket *> SocketList;
typedef vector<Socket *>::iterator SocketListIT;

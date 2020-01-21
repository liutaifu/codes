using namespace std;

class Socket
{
		public:
				Socket();
				~Socket();
				int GenSocket();
				int GenBind(int sock,int port);
				int GenListen(int sock,int numListen);
				int GenAccept(int sock);
				int GenConnect();
				int GenRecvData(int accept);
				int GenSendData(int accept,char* buf,int len);
				Socket *GetInstance();
				void DeleteInstance();

				int GetSocketId();

		private:
				int sock_id;
				int accept_id;
				static Socket *m_sock;
};

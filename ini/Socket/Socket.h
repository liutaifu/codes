using namespace std;

class Socket
{
		public:
				Socket();
				~Socket();
				int GenSocket();
				int GenBind(int sock,char *port);
				int GenListen(int sock,int numListen);
				int GenAccept(int sock);
				int GenConnect();
				int GenRecvData(int accept);
				int GenSendData(int accept);

		private:
				int sock_id;
				int accept_id;
};

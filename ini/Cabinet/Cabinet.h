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
				void CabinetSocketFunc();


				Socket m_socket;
				//RegKeyIni m_regkey;
		private:
				static Cabinet *m_cab;
				int c_port;
				int c_listenNum;
				int c_sockId;
				int c_acceptId;
};

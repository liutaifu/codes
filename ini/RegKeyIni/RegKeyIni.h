using namespace std;

class RegKeyIni
{
		public:
				RegKeyIni();
				~RegKeyIni();
				void GetContentIni(/*char *con*/);
				static RegKeyIni *GetInstance();
				void DeleteInstance();
				char *GetRegKeyContent();
				void GetPrivateByString(char*,const char*,const char*);
				void ReadPrivateProfileString();
				void UpdatePrivateProfileString(const char *key,char *defPa);

				char *GetLogPath();
				char *GetFilePreName();
				char *GetSpCenterHost();
				int GetSpCenterPort();
				int GetHttpPort();
				int GetListenNum();
				char *GetTerminalDbHost();
				char *GetTerminalDbUser();
				char *GetTerminalDbPass();
				char *GetTerminalDbName();
		private:
				char contentIni[512];
				static RegKeyIni * m_RegKey;
				char *logPath;
				char *filePreName;
				char *spCenterHost;
				char *spCenterPort;
				char *httpPort;
				char *listenNum;
				char *terminalDbHost;
				char *terminalDbUser;
				char *terminalDbPass;
				char *terminalDbName;
};

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
				void ReadPrivateProfileString();
				void UpdatePrivateProfileString(char *key,char *defPa);

				char *GetLogPath();
				char *GetFilePreName();
				char *GetSpCenterHost();
				char *GetSpCenterPort();
				char *GetHttpPort();
				char *GetTerminalDbHost();
				char *GetTerminalDbUser();
				char *GetTerminalDbPass();
		private:
				char contentIni[512];
				static RegKeyIni * m_RegKey;
				char *logPath;
				char *filePreName;
				char *spCenterHost;
				char *spCenterPort;
				char *httpPort;
				char *terminalDbHost;
				char *terminalDbUser;
				char *terminalDbPass;
};

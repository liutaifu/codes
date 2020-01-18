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
				void ReadPrivateProfileString(string *key,string *defPa,string *pBuf);
		private:
				char contentIni[512];
				static RegKeyIni * m_RegKey;
};

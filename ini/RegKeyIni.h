using namespace std;

class RegKeyIni
{
		public:
				RegKeyIni();
				~RegKeyIni();
				void GetContentIni(/*char *con*/);
				static RegKeyIni *GetInstance();
				char *GetRegKeyContent();
		private:
				char contentIni[512];
				static RegKeyIni * m_RegKey;
};

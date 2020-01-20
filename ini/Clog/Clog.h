using namespace std;

class Clog
{
		public:
				Clog();
				~Clog();
				void WriteLog(string *log);
				void OpenLog();
				static Clog* ClogInit();
				void DeleteClog();
				void GetCurrentTime(char *buf,int flag);


				static pthread_mutex_t log_mutex;

		private:
				FILE *fd;
				char *logPa;
				char *logPreName;
				static Clog *m_clog;
				string fileName;
				string filePre;
};

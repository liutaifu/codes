#include <iostream>
#include <string>
#include "RegKeyIni/RegKeyIni.h"
#include "Clog/Clog.h"

using namespace std;

int main()
{
		RegKeyIni *reg = RegKeyIni::GetInstance();//new RegKeyIni();
		char s_con[1024];
		//s_con = (char *)malloc(1024);
		reg->GetContentIni();
		cout << "the ini is "<< reg->GetRegKeyContent()<<endl;

		reg->ReadPrivateProfileString();

		Clog *log = Clog::ClogInit();
		log->OpenLog();
		string slog = "today is beautul day!";
		log->WriteLog(&slog);
#if 0
		cout << "logPath is "<< reg->GetLogPath() << endl;
		cout << "fileprename is "<< reg->GetFilePreName() << endl;
		cout << "spcenterhost is "<< reg->GetSpCenterHost() << endl;
		cout << "spcenterport is "<< reg->GetSpCenterPort() << endl;
		cout << "httpport is "<< reg->GetHttpPort() << endl;
		cout << "terminaldbhost is "<< reg->GetTerminalDbHost() << endl;
		cout << "terminaldbuser is "<< reg->GetTerminalDbUser() << endl;
		cout << "terminaldbpass is "<< reg->GetTerminalDbPass() << endl;
		cout << "terminaldbname is "<< reg->GetTerminalDbName() << endl;
#endif

	//	reg->UpdatePrivateProfileString("TerminalDbHost","106.15.38.100");
		reg->DeleteInstance();
		log->DeleteClog();
		return 0;
}

#include "Main.h"
#include "Check.h"


using namespace std;
int main(int argc, char** argv)
{
	//���..\Check\·������û�����ļ�
	char * path = "./Check/";
	vector<string> files;
	WriteToLog(GetTime());
	WriteToLog("--��ʼ���з���--\n");

	while(true)
	{

		//�����û���µ��ļ������У�����vector files�д洢
		CheckFile(path, files);	

		for (int iter = 0; iter < files.size();iter++)
		{	
		//	string cmd="D:/HWCV/config/HWCV-exe ";
		//	cmd += files[iter];

		//	WinExec((char*)cmd.c_str(),SW_HIDE);

			try{
				ShellExecute(NULL,"open",
					"HWCV-exe.exe",
					(char*)files[iter].c_str(),
					NULL,
					SW_SHOWNORMAL);
			}catch(exception e)
			{
			
			}
		}
		files.clear();

		Sleep(SLEEP_TIME);
	}
	
	WriteToLog(GetTime());
	WriteToLog("--��������--\n");
	
	return 1;
}

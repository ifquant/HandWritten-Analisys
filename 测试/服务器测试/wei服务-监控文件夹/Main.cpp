#include "Main.h"
#include "Check.h"

using namespace std;

#define SLEEP_TIME	1000						//2000����ˢ��һ��

int main(int argc, char** argv)
{
	//���..\Check\·������û�����ļ�
	char * path = "D:\\HWCV\\Check\\";
//	char * path = "D:\\2017.2.28\\BJJB0702\\BJJB0702\\check\\";
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
			string EE = files[iter];

			try
			{
				ShellExecute(NULL,"open",
				"HWCV-exe.exe",
				(char*)files[iter].c_str(),
				NULL,
				SW_SHOWNORMAL);
//				EE += " ������������\n";
//				WriteToLog((char*)EE.c_str());

				Sleep(SLEEP_TIME);
			}
			catch(void)
			{
				EE += " ����\n";
				WriteToLog((char*)EE.c_str());
				Sleep(SLEEP_TIME);
				continue;
			}


		}
		files.clear();

		Sleep(SLEEP_TIME);
	}
	
	WriteToLog(GetTime());
	WriteToLog("--��������--\n");
	
	return 1;
}

/*
�������ļ���segmentation.cpp ��������ʵ���ļ�
*/
#include "segmentation.h"

/*������*/
int main(int argc,char* argv[])
{
	FILE *file = NULL;
	string checkpath="D:/HWCV/Check/";

	//��ȡ�����ļ��������ø������
	ReadConfig("D:/HWCV/config/configure.cfg");
	cout<<"ReadConfig success"<<endl;

	//��ʼ��log�ļ�
	memset(g_log_rec, 0, sizeof(g_log_rec));	
	strcat(g_log_rec, "\n");
	strcat(g_log_rec, GetTime());
	strcat(g_log_rec, "  �����ļ���ȡ��� ");

	vector<string> stuNum;

	while(true)
	{
		//��ѯ���ݿ�
		stuNum.clear();
		DbStu(stuNum);
		for(int i=0;i<stuNum.size();i++)
		{
			//���Ⱥϳɵ�ַ
			string temp = checkpath;
			temp +=stuNum[i];
			file = fopen((char*)temp.c_str(),"w");
			fclose(file);  
			SaveLog(".", g_log_adr, "a");
		}

		Sleep(SLEEP_TIME);

	}
	/*����ֵ*/
	return 0;
}



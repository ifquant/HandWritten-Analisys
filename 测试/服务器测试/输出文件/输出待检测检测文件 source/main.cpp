/*
�������ļ���segmentation.cpp ��������ʵ���ļ�
*/
#include "main.h"
//#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )//û�н�������

/*������*/
char *adr="D:/process.csv";
int main(int argc,char* argv[])
{

//	cout<<"��ʼ����"<<fpname1<<endl;
	//char *fpname1 = "010209400748";
	/*��������*/
	cout<<"1"<<endl;
	vector<string> stuNum;

	//��ȡ�����ļ��������ø������
	memset(g_log_rec, 0, sizeof(g_log_rec));
	strcat(g_log_rec, GetTime());
	if (!ReadConfig("D:/HWCV/config/configure.cfg"))
	{
		cout<<"!ReadConfig"<<endl;
		strcat(g_log_rec, ",config failed��\n");
		SaveLog(g_log_rec, adr, "a");

		return 0;
	}
	cout<<"ReadConfig success"<<endl;

	//��ѯ���ݿ�
	cout<<"2"<<endl;
	DbStu(stuNum);

	//����·��();
	FILE *fp;
	string name="D:/HWCV/Check/";
	cout<<"��������������"<<stuNum.size()<<endl;
	for(int i=0; i<stuNum.size();i++)
	{
		string temp=name;
		temp+=stuNum[i];
		fp=fopen((char*)temp.c_str(),"w+");
		fclose(fp);
		fp=NULL;

		system("pause");
	}

	/*����ֵ*/
	return 0;
}



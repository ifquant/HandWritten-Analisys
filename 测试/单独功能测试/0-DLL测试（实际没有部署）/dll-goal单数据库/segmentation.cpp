/*
�������ļ���segmentation.cpp ��������ʵ���ļ�
*/
#include "segmentation.h"

/*������*/
extern "C" _declspec(dllexport) char * __stdcall  WINAPI TEST(char *fpname1)
{
	return fpname1;//���ļ��е�·��
}
extern "C" _declspec(dllexport) char * __stdcall  WINAPI HWCV(char *fpname1, char *dest){

	/*��ȡ�����ļ��������ø������*/
	ReadConfig("D:\\HWCV\\config\\configure.cfg");

	/*��ʼ��log�ļ�*/
	memset(g_log_rec, 0, sizeof(g_log_rec));
	time_t timer;
	struct tm *tblock;
	timer = time(NULL);
	tblock = localtime(&timer);
	strcat(g_log_rec, "\n----------------------HWCV.dll--�����ݿ�----\n");
	strcat(g_log_rec, asctime(tblock));
	SaveLog(g_log_rec, g_log_adr, "a");

	vector<string>  dateVec, subjectVec,stuNum2;

	/*��ѯ���ݿ�*/
	string stuNum = fpname1;
	DbImg(stuNum, dateVec, subjectVec, stuNum2);


	memset(g_log_rec, 0, sizeof(g_log_rec));
	/*����·��*/
	for (int cp_i = 0; cp_i < dateVec.size(); cp_i++)
	{
		/*���������log�ļ�*/
		strcat(g_log_rec, stuNum.c_str());
		strcat(g_log_rec, "\t");
		strcat(g_log_rec, dateVec[cp_i].c_str());
		strcat(g_log_rec, "\t");
		strcat(g_log_rec, subjectVec[cp_i].c_str());
		strcat(g_log_rec, "\t");
		strcat(g_log_rec, stuNum2[cp_i].c_str());

		strcat(g_log_rec, "\n");
	}
	SaveLog(g_log_rec, g_log_adr, "a");

	/*���ص���ҳ���*/
/*	char out[200] = "��ǰʱ��Ϊ��";
	strcat(out, asctime(tblock));
	strcat(out, "<br>����ѧ��Ϊ��");
	strcat(out, fpname1);
	strcat(out, "<br>");
	sprintf(dest, out);
*/
	/*����ֵ*/
	return "SUCCEED";
}



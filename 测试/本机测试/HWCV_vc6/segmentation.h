/*
ͷ�ļ���segmentation.h ������ͷ�ļ�
*/
#pragma once
#ifdef WIN32                            //����VC6��STL��һЩ����ȫ֧�����
#pragma warning (disable: 4514 4786)
#endif
#include "StdAfx.h"
#include "path.h"
#include "Point.h"
#include "process.h"

using namespace std;

/*����ȫ�ֱ���*/


int		g_bi_threshold = 230;				/* ȫ�ֱ��� ��ֵ����ֵ*/
double  g_std_kesa[50][50];			/* ȫ�ֱ��� ��׼������*/
float   g_doubt_threshold = 0.12;	/* ȫ�ֱ��� ����������ֵ*/
string  g_dir = "Y:/";						/* ȫ�ֱ��� ��·����Ŀ¼*/
int		g_cheat_num_threshold = 0;	/* ȫ�ֱ��� Ĭ��������ֵ*/
int		g_conti = 1;					/* ȫ�ֱ��� Ĭ�����ױȽϵ�ͼƬ*/

int g_all_img_num = 0;				/* ȫ�ֱ��� �Ѽ�����ȫ��ͼƬ����*/
int g_doubt_img_num = 0;			/* ȫ�ֱ��� �Ѽ������ɵ�ͼƬ����*/
int g_all_stu_num = 0;				/* ȫ�ֱ��� �Ѽ�����ȫ��ѧ������*/
int g_doubt_stu_num = 0;			/* ȫ�ֱ��� �Ѽ������ɵ�ѧ������*/

bool g_output_cmd_config = false;	/*ȫ�ֱ��� �����������*/
bool g_output_txt_config = false;	/*ȫ�ֱ��� ����м��ļ�ѡ��*/
char g_log_adr[50] = "D:/HWCV/log_ori.txt";	/*ȫ�ֱ��� ������־�洢��ַ*/
char g_log_rec[500] = { 0 };		/*ȫ�ֱ��� ������־ר�ñ���*/
char g_err_adr[50]= "D:/HWCV/err_ori.txt";					/*������־·��*/
/*ȫ�ֱ��� ���txt����ļ�*/
/*ȫ�ֱ��� ���txt����ļ���ַ*/



time_t ltime;
char *srcTime=NULL;
char timeNow[32]={0};
char msg[100]={0};
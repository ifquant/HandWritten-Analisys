/*
ͷ�ļ���segmentation.h ������ͷ�ļ�
*/
#pragma once
#ifdef WIN32                            //����VC6��STL��һЩ����ȫ֧�����
#pragma warning (disable: 4514 4786)
#endif
#include "StdAfx.h"
#include "DBop.h"
#include "path.h"
#include "Point.h"
#include "process.h"

using namespace std;

/*����ȫ�ֱ���*/


int		g_bi_threshold;				/* ȫ�ֱ��� ��ֵ����ֵ*/
double  g_std_kesa[50][50];			/* ȫ�ֱ��� ��׼������*/
float   g_doubt_threshold = 0.12;	/* ȫ�ֱ��� ����������ֵ*/
string  g_dir;						/* ȫ�ֱ��� ��·����Ŀ¼*/
int		g_cheat_num_threshold = 0;	/* ȫ�ֱ��� Ĭ��������ֵ*/
int		g_conti;					/* ȫ�ֱ��� Ĭ�����ױȽϵ�ͼƬ*/

int g_all_img_num = 0;				/* ȫ�ֱ��� �Ѽ�����ȫ��ͼƬ����*/
int g_doubt_img_num = 0;			/* ȫ�ֱ��� �Ѽ������ɵ�ͼƬ����*/
int g_all_stu_num = 0;				/* ȫ�ֱ��� �Ѽ�����ȫ��ѧ������*/
int g_doubt_stu_num = 0;			/* ȫ�ֱ��� �Ѽ������ɵ�ѧ������*/

//string g_db_hostName = "192.168.200.97";	/*ȫ�ֱ��� ������ip������*/
//string g_db_dBName = "purple";			/*ȫ�ֱ��� ������ODBC����Դ*/
//string g_db_userName = "BJSH";			/*ȫ�ֱ��� �������û���*/
//string g_db_password = "bjshadmin";		/*ȫ�ֱ��� ����������*/
string g_db_hostName = "localhost";		/*ȫ�ֱ��� ������ip������*/
string g_db_dBName = "orcl123";			/*ȫ�ֱ��� ������ODBC����Դ*/
string g_db_userName = "yannsy";		/*ȫ�ֱ��� �������û���*/
string g_db_password = "123456";		/*ȫ�ֱ��� ����������*/

string	g_db_qurry_start = "200906";		/*ȫ�ֱ��� ���ݿ��ѯ_��ʼ����*/
string	g_db_qurry_end	 = "201610";		/*ȫ�ֱ��� ���ݿ��ѯ_��������*/
string	g_db_qurry_zone  = "0";		/*ȫ�ֱ��� ���ݿ��ѯ_�ض�����*/
string	g_db_qurry_stu_num = "0";	/*ȫ�ֱ��� ���ݿ��ѯ_�ض�����*/
bool	g_db_qurry_all   = true;	/*ȫ�ֱ��� ���ݿ��ѯ_��ѯȫ�����*/
string  g_db_hoster_zk;				/*ȫ�ֱ��� ���ݿ��û���zk������Ժ��zk�����ص�yannsy��*/


bool g_output_cmd_config = false;	/*ȫ�ֱ��� �����������*/
bool g_output_txt_config = false;	/*ȫ�ֱ��� ����м��ļ�ѡ��*/
char *g_log_adr = "D:/HWCV/log_ori.txt";	/*ȫ�ֱ��� ������־�洢��ַ*/
char g_log_rec[500] = { 0 };		/*ȫ�ֱ��� ������־ר�ñ���*/
char g_err_adr[30] = "D:/HWCV/err_ori.txt";					/*������־·��*/
/*ȫ�ֱ��� ���txt����ļ�*/
/*ȫ�ֱ��� ���txt����ļ���ַ*/


int _Check(char *fpname1, char *dest);
/*
ͷ�ļ���DBop.h  ���ݿ����ͷ�ļ�
*/
#pragma once
#import "C:\\Program Files\\Common Files\\System\\ado\\msado15.dll" no_namespace rename("EOF","EndOfFile")
#include <vector> 
#include <string> 
#include <iostream> 
#include <windows.h> 
#include <iomanip> 
#include <stdio.h> 

using namespace std;

/*ȫ�ֱ���*/

extern char g_log_adr[50];				/*ȫ�ֱ��� ������־�洢��ַ*/
extern char g_log_rec[500];				/*ȫ�ֱ��� ������־ר�ñ���*/
extern FILE *g_log_fpzz;				/*ȫ�ֱ��� ������־ר���ļ����*/

extern string g_db_hostName;		/*ȫ�ֱ��� ������ip������*/
extern string g_db_dBName;			/*ȫ�ֱ��� ������ODBC����Դ*/
extern string g_db_userName;		/*ȫ�ֱ��� �������û���*/
extern string g_db_password;		/*ȫ�ֱ��� ����������*/

extern string g_db_qurry_start;		/*ȫ�ֱ��� ���ݿ��ѯ_��ʼ����*/
extern string g_db_qurry_end;		/*ȫ�ֱ��� ���ݿ��ѯ_��������*/
extern string g_db_qurry_zone;		/*ȫ�ֱ��� ���ݿ��ѯ_�ض�����*/
extern string g_db_qurry_stu_num;	/*ȫ�ֱ��� ���ݿ��ѯ_�ض�����*/
extern bool   g_db_qurry_all;		/*ȫ�ֱ��� ���ݿ��ѯ_��ѯȫ�����*/
extern string g_db_hoster_zk;		/*ȫ�ֱ��� ���ݿ��û���zk������Ժ��zk�����ص�yannsy��*/
/*****************************************����ԭ��*************************************/


/**
���ܣ�	��ѯ����ѧ����ѧ�ţ������е�ָ��λ�õ����ݿ���Ϣ(ѧ��)ȫ���洢����Ϊstu��vector<string>�͵ı�����

@���� stu ѧ��ѧ�Ŵ洢
@����ֵ �ɹ�1 ʧ��0
*/
int DbStu(vector<string>& stu);

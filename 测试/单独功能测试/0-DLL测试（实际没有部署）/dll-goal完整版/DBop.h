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

extern char *g_log_adr;				/*ȫ�ֱ��� ������־�洢��ַ*/
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
�����ܣ�	����string���stu���洢ѧ�š������������д��˵Ŀ�����Ϣ,���ֱ�洢�ڲ�ͬ�ı�����

@���� stuNum ѧ��
@���� date<vector>	����ʱ��
@���� subject<vector> ���Կ�Ŀ
@���� stuNum<vector> ����
@����ֵ �ɹ�1 ʧ��0
*/
int DbImg(string stuNum, vector<string>& dateVec, vector<string>& subjectVec, vector<string>& stuNum2);


/**
�����ܣ�	����ѧ�����ݿ���Ϣ,����ѧ���ļ���������������������ݿ���

@���� stuNum��ѧ��
@���� subject�����Կ�Ŀ
@���� flagCheat�����ױ��
@����ֵ �ɹ�1ʧ��0
*/
int DbUpdate(string stuNum, vector<string> dateVec, vector<string> subjectVec, vector<string> stuNum2, vector<string> flagVec);
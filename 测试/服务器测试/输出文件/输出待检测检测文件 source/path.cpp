/*
ʵ���ļ���path.cpp ·������ʵ���ļ�
*/
#include "path.h"


/**
��ȡ�����ص�ǰʱ��
 */
char* GetTime()
{
	time(&g_ltime);
	g_srcTime = ctime(&g_ltime);
	strncpy(g_timeNow, g_srcTime, strlen(g_srcTime) - 1);  //����������
	g_timeNow[strlen(g_srcTime) - 1] = '\0';   //�ӽ�����'\0'

	return g_timeNow;
}


/**
��ȡ�����ļ��������ø������

@���� filename �����ļ���·��
@����ֵ �ɹ�1  ʧ��0
*/
int ReadConfig(char *filename)
{
	ifstream file(filename);

	if (!file)/*"�����ļ������ڣ�"*/
	{
		/*д��ʱ��*/
		memset(g_log_rec, 0, sizeof(g_log_rec));
//		cout<<"read"<<endl;

		strcat(g_log_rec, "--ERR:�����ļ�������!");
		SaveLog(g_log_rec, g_log_adr, "a");

		return 0;
	}

	cout<<"1.1"<<endl;
	/*���裺��ʼ��ȡ��Ϣ*/
	/*�����������ַ�*/
	string temp;
	file >> temp >> temp;
	/*---����6�����ο�������Ϣ��ͼƬ�ԱȲ���*/
	file >> temp >> temp >> temp >> temp >> temp >>temp;
	file  >> g_dir >> temp >> temp >> temp;
	string g_log_adr_t;
	file  >> g_log_adr_t >> temp;

	memset(g_log_adr, 0, sizeof(g_log_adr));
	strcpy(g_log_adr, (char*)g_log_adr_t.c_str());
	cout<<"1.2"<<endl;

	//if (g_bi_threshold < 0 || g_bi_threshold >255)/*�������־������Ϣ*/{		
	//	memset(g_log_rec, 0, sizeof(g_log_rec));
	//	strcat(g_log_rec, "--MSG:���ò�������-�ʼ�ͼ��ԱȲ���!");
	//	strcat(g_log_rec, g_dir.c_str());
	//	SaveLog(g_log_rec, g_err_adr, "a");

	//	return 0;
	//}


	/*---����6�����ο�������Ϣ���������ò���*/
	file >> temp >> temp >> g_db_hostName >> temp >> g_db_dBName >> temp >> g_db_userName >> temp >> g_db_password >> temp >> g_db_hoster_zk >> temp;

	cout<<"1.3"<<endl;
	///*�������*/
	////if (strcmp(g_db_hostName.c_str(), "") || g_bi_threshold >255 || g_bi_threshold < 1)/*�������־������Ϣ*/{
	//	memset(g_log_rec, 0, sizeof(g_log_rec));
	//	/*time_t timer;
	//	struct tm *tblock;
	//	timer = time(NULL);
	//	tblock = localtime(&timer);
	//	strcat(g_log_rec, asctime(tblock));*/
	//	strcat(g_log_rec, "--MSG:-�������ò���!");
	//	strcat(g_log_rec, g_db_password.c_str());
	//	strcat(g_log_rec, "\n");

	//	SaveLog(g_log_rec, g_err_adr, "a");

//		return 0;
//	}


	/*---����5�����ο�������Ϣ�����Ʋ���*/
	//����
	file >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp;

	///*�������*/
	//if (0)/*�������־������Ϣ*/{
	//	memset(g_log_rec, 0, sizeof(g_log_rec));
	///*	time_t timer;
	//	struct tm *tblock;
	//	timer = time(NULL);
	//	tblock = localtime(&timer);
	//	strcat(g_log_rec, asctime(tblock));*/
	//	strcat(g_log_rec, "--ERR:���ò�������-���Ʋ���!");
	//	SaveLog(g_log_rec, g_err_adr, "a");

	//	return 0;
	//}

	/*---����5�����ο�������Ϣ�����ݿ��ѯ����*/
	file >> temp >> temp >> g_db_qurry_start >> temp >> g_db_qurry_end >> temp >> g_db_qurry_zone >> temp >> g_db_qurry_stu_num >> temp >> g_db_qurry_all >> temp;

	///*�������*/
	//if (0)/*�������־������Ϣ*/{
	//	memset(g_log_rec, 0, sizeof(g_log_rec));
	//	/*time_t timer;
	//	struct tm *tblock;
	//	timer = time(NULL);
	//	tblock = localtime(&timer);
	//	strcat(g_log_rec, asctime(tblock));*/
	//	strcat(g_log_rec, "--ERR:���ò�������-���ݿ��ѯ����!");
	//	SaveLog(g_log_rec, g_err_adr, "a");

	//	return 0;
	//}



	//if (g_doubt_threshold < 0.01)
	//{
	//	memset(g_log_rec, 0, sizeof(g_log_rec));
	//	/*time_t timer;
	//	struct tm *tblock;
	//	timer = time(NULL);
	//	tblock = localtime(&timer);
	//	strcat(g_log_rec, asctime(tblock));*/
	//	strcat(g_log_rec, "--ERR:���ò�������-�ʼ�ͼ��ԱȲ���!");
	//	SaveLog(g_log_rec, g_err_adr, "a");
	//
	//	return 0;
	//}

	//if (g_conti < 0 || g_conti > 10 || g_conti == NULL)
	//{
	//	memset(g_log_rec, 0, sizeof(g_log_rec));
	///*	time_t timer;
	//	struct tm *tblock;
	//	timer = time(NULL);
	//	tblock = localtime(&timer);
	//	strcat(g_log_rec, asctime(tblock));*/
	//	strcat(g_log_rec, "--ERR:���ò�������-�ʼ�ͼ��ԱȲ���!\n\n");
	//	SaveLog(g_log_rec, g_err_adr, "a");

	//	return 0;
	//}
	file.close();/*�ر��ļ����*/

	return 1;
}


/**
�������ܣ��洢�������ݵ�txt�ļ�

@������ record �洢�����
@���� g_txt_file_path �洢��λ��
@����ֵ 1�ɹ� 0ʧ��
*/
int SaveLog(char *txt, string txt_file_path, char *type)
{
	FILE* fpzz = fopen(txt_file_path.c_str(), type);  //�����ļ�	
	if (!fpzz) 	return 0; 
	//Ҫ���ش������
	fprintf(fpzz, txt); //�ӿ���̨�ж��벢���ı����
	fclose(fpzz);
	fpzz = NULL;//��Ҫָ��գ������ָ��ԭ���ļ���ַ  

	return 1;
}

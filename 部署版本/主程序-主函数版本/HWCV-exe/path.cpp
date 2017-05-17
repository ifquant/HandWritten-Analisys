/*
ʵ���ļ���path.cpp ·������ʵ���ļ�
*/
#include "path.h"


/**
��ȡ�����ص�ǰʱ��
 */
char* GetTime()
{
	time( &ltime );
	srcTime = ctime( &ltime );
	strncpy(timeNow, srcTime, strlen(srcTime)-1);  //����������
	timeNow[strlen(srcTime)-1] = '\0';   //�ӽ�����'\0'

	return timeNow;
}


/**
����ѧ����Ϣ�����ļ�·���������ļ���ȡ

@���� date ��������
@���� subject ���Կ�Ŀ
@���� stuNum ����
@����ֵ �������ɵ��ļ�·��
*/
string CrPath(string date, string subject, string stuNum)
{
	string temp = g_dir; temp += date; temp += "/";
	temp += subject.substr(0, 4); temp += "/";
	temp += stuNum; temp += ".jpg";

	return temp;
}


/*
���ܣ���ȡ��׼���ļ�
@���� filesname �ļ���
@���� col ����
@���� _vector ��ȡ���ı�׼��浽vector��
@����ֵ �ɹ�1ʧ��0
*/
int ReadScanf(const string &filename, const int &cols, vector<double *> &_vector)
{
	// ���ܣ���filename �е����ݣ���cols�У���ȡ��_vector�У�_vector����Ϊ��ά����
	FILE *fp = fopen(filename.c_str(), "r");//�򿪲���ȡ�ļ�
	bool flag = true;
	int i = 0;

	//	printf("--read_scanf--");
	if (!fp){ return 0; }
	while (flag){
		double *point = new double[cols];
		for (i = 0; i<cols; i++){ //��ȡ���ݣ�����_vector[cols]��
			if (EOF == fscanf(fp, "%lf", &point[i])) {
				flag = false; break;
			}
			if (EOF == fgetc(fp)) {
				flag = false; i++; break;
			}
		}
		if (cols == i)
			_vector.push_back(point);
	}
	fclose(fp);

	return 1;
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
		cout<<"read"<<endl;

		strcat(g_log_rec, "--ERR:�����ļ�������!");
		SaveLog(g_log_rec, g_err_adr, "a");

		return 0;
	}

	/*���裺��ʼ��ȡ��Ϣ*/

	string temp;/*�����������ַ�*/
	file >> temp >> temp;
	/*---����6�����ο�������Ϣ��ͼƬ�ԱȲ���*/
	file >> temp >> temp >> temp >> temp >> temp >>temp;
	file  >> g_dir >> temp >> temp >> temp;
	string g_log_adr_t;
	file  >> g_log_adr_t >> temp;

	memset(g_log_adr, 0, sizeof(g_log_adr));
	strcpy(g_log_adr, (char*)g_log_adr_t.c_str());

	//if (g_bi_threshold < 0 || g_bi_threshold >255)/*�������־������Ϣ*/{		
	//	memset(g_log_rec, 0, sizeof(g_log_rec));
	//	strcat(g_log_rec, "--MSG:���ò�������-�ʼ�ͼ��ԱȲ���!");
	//	strcat(g_log_rec, g_dir.c_str());
	//	SaveLog(g_log_rec, g_err_adr, "a");

	//	return 0;
	//}


	/*---����6�����ο�������Ϣ���������ò���*/
	file >> temp >> temp >> g_db_hostName >> temp >> g_db_dBName >> temp >> g_db_userName >> temp >> g_db_password >> temp >> g_db_hoster_zk >> temp;

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
	if (NULL == fpzz) 
	{
		return 0; 
	}//Ҫ���ش������
	fprintf(fpzz, txt); //�ӿ���̨�ж��벢���ı����
	fclose(fpzz);
	fpzz = NULL;//��Ҫָ��գ������ָ��ԭ���ļ���ַ  

	return 1;
}


/*
���ܣ������м����ͼ��(��ʵ�֣�û�б�Ҫ)
@����
@����
@����ֵ
*/
int SaveImg(IplImage *img, char *g_process_img_adr){
	/*char processPic[100] = "E:/imggj/";
	char *namePic = new char[20];
	bool flag = false;
	string xuehao = path, kaoshihao = path;
	int num_iter = sizeof(path);
	for (int iter = 0; iter < num_iter; iter++)
	{
		if (path[iter] == 'x')
		{
			flag = true;
			break;
		}
	}
	if (flag)
	{
		xuehao = xuehao.substr(27, 13);
		kaoshihao = kaoshihao.substr(40, 5);
	}
	else
	{
		xuehao = xuehao.substr(27, 12);
		kaoshihao = kaoshihao.substr(39, 5);
	}
	strcat(processPic, xuehao.c_str());
	_mkdir(processPic);
	strcat(processPic, kaoshihao.c_str());
	strcat(processPic, ".jpg");
	cvSaveImage(processPic, imggj);*/
	return 1;
}
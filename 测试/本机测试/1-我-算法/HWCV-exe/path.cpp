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


	/*---����6�����ο�������Ϣ���������ò���*/
	file >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp;


	/*---����5�����ο�������Ϣ�����Ʋ���*/
	file >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp;

	/*---����5�����ο�������Ϣ�����ݿ��ѯ����*/
	file >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp;

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
	return 1;
}


/*
���ܣ���ȡָ��Ŀ¼�µ��ļ�
@���� path ·��
@���� files ���vector��ʽ���ļ�
*/
void getFiles(string path, vector<string>& files)
{
	using namespace std;//�����������ռ�
	//�ļ����  
	long   hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,����֮  

			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("/").append(fileinfo.name), files);
			} //�������,�����б�  
			else
			{
				files.push_back(p.assign(path).append("/").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}
}


/*
���ܣ���ȡָ��Ŀ¼�µ�Ŀ¼
@���� path Ŀ¼
@���� files ���ص�Ŀ¼vector
@����ֵ �ɹ�1ʧ��0
*/
int getFolders(string path, vector<string>& files)
{
	using namespace std;//�����������ռ�
	//�ļ����  
	long   hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;
	string p;

	int i = 0;
	if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
			{
				files.push_back(p.assign(path).append("/").append(fileinfo.name));
				printf("�ļ��У�%s\n", files[i].c_str());
				i++;
			}

		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}
	return 0;

}


/*
���ܣ�����Ŀ¼
*/
int searchDir(char *path, vector<string> &dir)
{
	using namespace std;
	struct _finddata_t fa;//�����ҵ��Ľṹ��
	long handle;
	int flag = 0;
	char temp[100] = { 0 };
	string path_temp = path;
	//	path_temp=path_temp.substr(0,path_temp.length()-1);

	if ((handle = _findfirst(strcat(path, "*"), &fa)) == -1L)//�������Ŀ¼�Ļ�
		return 0;

	do//��Ŀ¼����ִ��ѭ��
	{
		if (fa.attrib == _A_SUBDIR && ~strcmp(fa.name, ".") && ~strcmp(fa.name, ".."))
		{
			strcat(temp, path_temp.c_str());
			strcat(temp, fa.name);

			if (flag++)
				dir.push_back(temp);
			else;

			memset(temp, 0, 100);
		}
	} while (_findnext(handle, &fa) == 0); /* �ɹ��ҵ�ʱ����0*/

	_findclose(handle);

	return 0;

}
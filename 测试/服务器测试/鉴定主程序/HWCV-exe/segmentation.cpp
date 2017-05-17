/*
�������ļ���segmentation.cpp ��������ʵ���ļ�
*/
#include "segmentation.h"
//#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )//û�н�������

int ComputeImage(vector<string> files, vector<int> flag_exist,  double bzckesa[50][50], double *wcd, int conti)
{
	cout << "ComputeImage" << endl;
	int i, ii, jj, size;
	double	bzcu[50][50] = { 0 };			//��׼���е�u
	double	featurep[50][50][30] = { 0 };	//����ͼ�����������������ʼ��//��ʲô	//30
	int		feature[50][50][30] = { 0 };	//����ͼ�������ֵ
	int		featx[50][50] = { 0 };			//ѭ����ֵ��feature
	int		featureall;					//ͼ������ֵ��				//��ʲô��

	size = flag_exist.size();
	for (i = 0; i < size; i++)
	{
		memset(featx, 0, sizeof(featx));
		cout << "singlefeature:" << (char*)files[flag_exist[i]].c_str() << endl;
		//����ļ��������


		singlefeature((char*)files[flag_exist[i]].c_str(), featx);				//featx[][50]
		featureall = 0;                                    //ͼ������ֵ�͵ĳ�ʼ��
		for (ii = 0; ii < 48; ii++)                             //��featx������,��ͷ���ܲ����ú�������
			for (jj = ii + 1; jj < 47; jj++)
			{
			feature[ii][jj][i] = featx[ii][jj];
			featureall = featureall + featx[ii][jj];
			}
		//��������������featurep��ʽ(5)  ���׼���е�u�ĺ�
		for (ii = 0; ii < 48; ii++)
			for (jj = ii + 1; jj < 47; jj++)
			{
			featurep[ii][jj][i] = (double)featx[ii][jj] / featureall;
			bzcu[ii][jj] += (double)featx[ii][jj] / featureall * 1000;     //��׼���ֵ��С,���зŴ�1��
			}
	}
	//������һ���˵�ÿһ��ͼƬ��
	for (ii = 0; ii < 48; ii++)//���׼���е�u
		for (jj = ii + 1; jj < 47; jj++)
			bzcu[ii][jj] = bzcu[ii][jj] / size;
	//�������Ծ��Ǵ�Ȩ����wcd
	for (i = 0; i < size; i++)
		for (ii = 0; ii < 48; ii++)
			for (jj = ii + 1; jj < 47; jj++)
				if (featurep[ii][jj][i] * featurep[ii][jj][conti] != 0 && bzckesa[ii][jj] != -1)
					wcd[i] += pow((featurep[ii][jj][i] - featurep[ii][jj][conti]), 2) / ((featurep[ii][jj][i] + featurep[ii][jj][conti])*bzckesa[ii][jj]);

	memset(feature, 0, sizeof(feature));
	memset(featurep, 0, sizeof(featurep));

	return 1;
}


/*������*/
int main(int argc,char* argv[])
{
	if(argc<2) return -1;
	//for(int iii=0;iii<argc;iii++)
	//	cout<<"argv"<<iii<<" "<<argv[iii]<<endl;
	char *fpname1 = argv[1];

//	cout<<"��ʼ����"<<fpname1<<endl;
	//char *fpname1 = "010209400748";
	/*��������*/
	int		i, ii, jj;
	double  bzckesa[50][50] = { 0 };
	double  wcd[30] = { 0 };

	int		featdif[30] = { 0 };
	float	maxx = 0;			//�������ֵ�ı����ֵ
	int		xyimgnum = 0;				//����ͼƬ����Ŀ
	char	str[80];					//�洢��ַ

	vector<string> suspict;		//��¼����ͼƬ��ַ
	vector<float> suspict_wcd;	//����ͼƬ��wcdֵ
	vector<string> files;		//�洢�������п����ļ�·��
	vector<string> dateVec, subjectVec, stuNum2;
	vector<string> flagVec;//��¼�鵽��ѧ�������п�����Ϣ

	//��ȡ�����ļ��������ø������
	memset(g_log_rec, 0, sizeof(g_log_rec));
	strcat(g_log_rec, GetTime());
	if (!ReadConfig("D:/HWCV/config/configure.cfg"))
	{
		strcat(g_log_rec, ",config failed��\n");
		SaveLog(g_log_rec, g_log_adr, "a");
		return 0;
	}
	cout<<"ReadConfig success"<<endl;

	//��ʼ��log�ļ�
	strcat(g_log_rec, ",");
	strcat(g_log_rec, fpname1);//����
	strcat(g_log_rec, ",");

	/*
	string temp=g_db_hostName;
	temp+=g_db_dBName;temp+=g_db_userName;temp+=g_db_password;
	SaveLog((char*)temp.c_str(), g_log_adr, "a");
	*/

	/*���裺��ȡ��׼���ļ�*/
	int bzccolumns = 47;//txt�ļ�����47��
	vector<double *> output_bzc;
	if (!ReadScanf("D:\\HWCV\\config\\stdfile.db", bzccolumns, output_bzc)) return 0;
	for (ii = 0; ii < 48; ii++)//output_vector����Ϊ��ά����;�������Ԫ�أ�
		for (jj = ii + 1; jj < 47; jj++)
			bzckesa[ii][jj] = output_bzc[ii][jj];

	//��ѯ���ݿ�
	string stuNum = fpname1;
	cout << "��ѯ���ݿ�" << endl;
	DbImg(stuNum, dateVec, subjectVec, stuNum2);

	//����·��();
	cout << "����·��-dateVec�ĸ�����" << dateVec.size() << endl;
	vector<int> flag_exist;
	fstream _file;
	for (int cp_i = 0; cp_i < dateVec.size(); cp_i++)
	{
		string path_t = CrPath(dateVec[cp_i], subjectVec[cp_i], stuNum2[cp_i]); 
		cout << path_t << endl;
		SaveLog((char*)path_t.c_str(), "D:/HWCV/1.txt", "a"); 
		SaveLog("\n", "D:/HWCV/1.txt", "a");
		files.push_back(path_t);
		_file.open(path_t.c_str(), ios::in);

		if (_file) 
		{
			//SaveLog("OK", "D:/HWCV/1.txt", "a");
			flag_exist.push_back(cp_i);
		}
	}
	int size = flag_exist.size();
	cout << "����size������" << size << endl;
	if (size == 0)
	{
		system("pause");
		return 0; //û�ҵ��ˣ�ֱ�ӷ���	
	}
	//��ʼ��ÿһ��ͼƬ���д���
	cout << "��ÿһ��ͼƬ���д���" << endl;
	for (int r = 0; r < size; r++)
	{
		memset(wcd, 0, sizeof(wcd));
		ComputeImage(files, flag_exist, bzckesa, wcd, r);

		xyimgnum = 0;
		int flagc = 0;
		//��������
		for (i = 0; i < files.size(); i++)
		{
			if (i == flag_exist[flagc])
			{
				flagc++;
				if (wcd[i]>0.12)
				{
					flagVec.push_back("1");//���ɱ��1
					xyimgnum++;
					suspict.push_back(files[i].c_str());
					suspict_wcd.push_back(wcd[i]);
				}
				else
				{
					flagVec.push_back("0");//���ɱ��1
				}
			}
			else
			{
				flagVec.push_back("0");//���ɱ��1
				continue;
			}
		}

		// ��֤��������
		if (xyimgnum < 3)
		{
			break;
		}
		flagVec.clear();
	}

	// ����������ݿ�
	cout << "�������ݿ�" << endl;
	DbUpdate(stuNum, dateVec, subjectVec, stuNum2, flagVec);

	// ���������log�ļ�
	char pic_num[20];
	_itoa(size, pic_num, 10);
	strcat(g_log_rec, pic_num);
	if (xyimgnum > 0)
	{
		g_stu_sus++;
		//�������ͼƬ������csv
		char b[20];
		sprintf(b, ",%d", xyimgnum);
		strcat(g_log_rec, b);
		strcat(g_log_rec, "\n");
		//����������ͼ��
		for (i = 0; i < xyimgnum; i++)
		{
			strcat(g_log_rec, ",,,");
			strcat(g_log_rec, suspict[i].c_str());
			strcat(g_log_rec, ",");
			float sim=(1.0-suspict_wcd[i])*100;
			char a[20];
			sprintf(a, "%g", sim);
			strcat(g_log_rec, a);
			strcat(g_log_rec, "%%\n");
		}
	}
	else strcat(g_log_rec, "\n"); 
	//strcat(g_log_rec, "\n");

	SaveLog(g_log_rec, g_log_adr, "a");
	cout << "�������log�ļ���" << g_log_adr <<" ���"<< endl;


	/*�ƺ�*/
	suspict.clear();
	suspict_wcd.clear();
	output_bzc.clear();
	memset(g_log_rec, 0, sizeof(g_log_rec));
	memset(bzckesa, 0, sizeof(bzckesa));
	memset(wcd, 0, sizeof(wcd));
	memset(featdif, 0, sizeof(featdif));
	files.clear();
	dateVec.clear();
	subjectVec.clear();
	stuNum2.clear();
	flagVec.clear();

	system("pause");
	/*����ֵ*/
	return 0;
}



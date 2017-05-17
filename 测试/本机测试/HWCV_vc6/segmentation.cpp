/*
�������ļ���segmentation.cpp ��������ʵ���ļ�
*/
#include "segmentation.h"
//#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )//�޽�������
/*������*/


int main(int argc, char* argv[])
{
	/*��������*/
	string dir = "E:/xiangmu/Img/imgjiaobiao/010211100518"; //�洢Ŀ¼
	//string dir;
	//if (argc < 2)
	//	return -1;
	//else
	//	dir = argv[1];
	cout << (char*)dir.c_str() << endl;
	char	record[2400] = { 0 };
	FILE*	fpzz = NULL;//��Ҫע��
	int		i, ii, jj, feature[50][50][30] = { 0 }, featureall = 0;
	double	featurep[50][50][30] = { 0 };
	double  bzcu[50][50] = { 0 };
	double  bzckesa[50][50] = { 0 };
	double  wcd[30] = { 0 };

	int		featx[50][50] = { 0 };
	int		featdif[30] = { 0 };
	float	maxx = 0;			//�������ֵ�ı����ֵ
	int		xyimgnum = 0;				//����ͼƬ����Ŀ

	vector<string> suspict;		//��¼����ͼƬ��ַ
	vector<float> suspict_wcd;	//����ͼƬ��wcdֵ
	vector<string> files;		//�洢�������п����ļ�·��
	/*��ȡ�����ļ��������ø������*/
	if (!ReadConfig("D:/HWCV/config/configure.cfg"))
	{
//		SaveLog("\t�����ļ���ȡʧ��\n", g_log_adr, "a");
		SaveLog("\n0\n", g_log_adr, "a");
		return 0;
	}
	char path[100] = "E:/xiangmu/Img/imgjiaobiao/";



	/*���裺��ȡ��׼���ļ�*/
	int bzccolumns = 47;//txt�ļ�����47��
	vector<double *> output_bzc;
	if (!ReadScanf("D:\\HWCV\\config\\stdfile.db", bzccolumns, output_bzc))
	{
		memset(g_log_rec, 0, sizeof(g_log_rec));

//		SaveLog("\n��ȡ·����D:\\HWCV\\config\\stdfile.db �ı�׼���ļ�ʧ�ܣ�\n", g_log_adr, "a");
		SaveLog("\n0\n", g_log_adr, "a");
		return 0;
	}
//	cout<<"��׼�"<<endl;
	for (ii = 0; ii < 48; ii++)//output_vector����Ϊ��ά����;�������Ԫ�أ�
		for (jj = ii + 1; jj < 47; jj++)
		{
			bzckesa[ii][jj] = output_bzc[ii][jj];
//			cout<<	bzckesa[ii][jj];
		}
//		cout<<endl;

	//��ʼ���
	//-------------------------------------------------------------//
	getFiles(dir.c_str(), files);	//������ǰ�ļ����µ������ļ�
	int size = files.size();
	cout << "�����ļ�����" <<size<< endl;

	//��ʼ��ÿһ��ͼƬ���д���
	for (int r = 0; r<size; r++)
	{
		memset(wcd, 0, sizeof(wcd));
		cout<<"-��ÿһ��ͼƬ���д���-��"<<files[r].c_str()<<endl;
		ComputeImage(files, bzckesa, wcd, r);
		xyimgnum = 0;
		//�󿨷���������ֵ 
		for (i = 0; i < size; i++)
		{
			cout << files[i].c_str()<< "  " << wcd[i] << endl;
			if (wcd[i]>0.12)
			{
				xyimgnum++;
				suspict.push_back(files[i].c_str());
				suspict_wcd.push_back(wcd[i]);
			}
		}
		if (xyimgnum<3) break;
	}

	/*���������log�ļ�*/
	strcat(g_log_rec, "\n");
	memset(g_log_rec, 0, sizeof(g_log_rec));
//	strcat(g_log_rec, GetTime());
//	strcat(g_log_rec, "\t�������ţ�");
	strcat(g_log_rec, dir.substr(27, 22).c_str());
	strcat(g_log_rec, "\t");//ͼƬ����Ϊ��
	char pic_num[20];
	_itoa(size, pic_num, 10);
	strcat(g_log_rec, pic_num);
	if (xyimgnum > 0)
	{
		char b[20];
		sprintf(b, "\t%d", xyimgnum);
		strcat(g_log_rec, b);
		strcat(g_log_rec, "\n");
		for (i = 0; i < xyimgnum; i++)
		{
			cout << "����ͼ��" << files[i].c_str() << endl;
			strcat(g_log_rec, "\t\t\t");//\t����ͼ��
			strcat(g_log_rec, suspict[i].c_str());
			strcat(g_log_rec, "\t");//���ƶȣ�
			float sim = (1.0 - suspict_wcd[i]) * 100;
			char a[20];
			sprintf(a, "%g", sim);
			strcat(g_log_rec, a);
			strcat(g_log_rec, "%%\n");
		}
	}
	else
	{
//		strcat(g_log_rec, "\t�ÿ���û������ͼ��\n");
		strcat(g_log_rec, "\t0\n");
		cout << "�ÿ���������ͼ��" << endl;
	}
	SaveLog(g_log_rec, g_log_adr, "a");


	/*�ƺ�*/
	suspict.clear();
	suspict_wcd.clear();
	memset(g_log_rec, 0, sizeof(g_log_rec));
	memset(feature, 0, sizeof(feature));
	memset(featurep, 0, sizeof(featurep));
	memset(bzckesa, 0, sizeof(bzckesa));
	memset(wcd, 0, sizeof(wcd));
	memset(featdif, 0, sizeof(featdif));
	files.clear();
	memset(g_log_rec, 0, sizeof(g_log_rec));

	/*����ֵ*/
	system("pause");
	return 0;
}

///*
//�������ļ���segmentation.cpp ��������ʵ���ļ�
//*/
//#include "segmentation.h"
////#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )//�޽�������
///*������*/
//int ComputeImage(vector<string> files, double bzckesa[50][50], double *wcd, int conti);
//int main(int argc, char* argv[])
//{
//	/*��������*/
//	string dir = "E:\\xiangmu\\Img\\imgjiaobiao\\010211100518"; //�洢Ŀ¼
//	//string dir;
//	//if (argc < 2)
//	//	return -1;
//	//else
//	//	dir = argv[1];
//	cout << (char*)dir.c_str() << endl;
//	char	record[2400] = { 0 };
//	FILE*	fpzz = NULL;//��Ҫע��
//	int		i, ii, jj, feature[50][50][30] = { 0 }, featureall = 0;
//	double	featurep[50][50][30] = { 0 };
//	double  bzcu[50][50] = { 0 };
//	double  bzckesa[50][50] = { 0 };
//	double  wcd[30] = { 0 };
//
//	int		featx[50][50] = { 0 };
//	int		featdif[30] = { 0 };
//	float	maxx = 0;			//�������ֵ�ı����ֵ
//	int		xyimgnum = 0;				//����ͼƬ����Ŀ
//	char	str[80];					//�洢��ַ
//
//	vector<string> suspict;		//��¼����ͼƬ��ַ
//	vector<float> suspict_wcd;	//����ͼƬ��wcdֵ
//	vector<string> files;		//�洢�������п����ļ�·��
//
//	/*��ȡ�����ļ��������ø������*/
//	if (!ReadConfig("D:/HWCV/config/configure.cfg"))
//	{
//		//		SaveLog("\t�����ļ���ȡʧ��\n", g_log_adr, "a");
//		SaveLog("\n0\n", g_log_adr, "a");
//		return 0;
//	}
//	char path[100] = "E:/xiangmu/Img/imgjiaobiao/";
//
//
//
//	/*���裺��ȡ��׼���ļ�*/
//	int bzccolumns = 47;//txt�ļ�����47��
//	vector<double *> output_bzc;
//	if (!ReadScanf("D:\\HWCV\\config\\stdfile.db", bzccolumns, output_bzc))
//	{
//		memset(g_log_rec, 0, sizeof(g_log_rec));
//
//		//		SaveLog("\n��ȡ·����D:\\HWCV\\config\\stdfile.db �ı�׼���ļ�ʧ�ܣ�\n", g_log_adr, "a");
//		SaveLog("\n0\n", g_log_adr, "a");
//		return 0;
//	}
//
//	//��ʼ���
//	//-------------------------------------------------------------//
//	getFiles(dir.c_str(), files);	//������ǰ�ļ����µ������ļ�
//	int size = files.size();
//
//	for (i = 0; i < size; i++)
//	{
//		//		cout << ".";
//		memset(str, 0, sizeof(str));
//		memset(featx, 0, sizeof(featx));
//		memset(bzcu, 0, sizeof(bzcu));
//
//		strcpy(str, files[i].c_str());
//		singlefeature(str, featx);//featx[][50]
//
//		featureall = 0;                       //ͼ������ֵ�͵ĳ�ʼ��
//		for (ii = 0; ii < 48; ii++)           //��featx������,��ͷ���ܲ����ú�������
//			for (jj = ii + 1; jj < 47; jj++)
//			{
//			feature[ii][jj][i] = featx[ii][jj];
//			featureall = featureall + featx[ii][jj];
//			}
//		/*��������������featurep��ʽ(5)  ���׼���е�u�ĺ�*/
//		for (ii = 0; ii < 48; ii++)
//			for (jj = ii + 1; jj < 47; jj++)
//			{
//			featurep[ii][jj][i] = (double)featx[ii][jj] / featureall;
//			bzcu[ii][jj] += (double)featx[ii][jj] / featureall * 1000;     //��׼���ֵ��С,���зŴ�1��
//			}
//	}/*������ȫ��ͼƬ*/
//
//	/*���׼����u*/
//	for (ii = 0; ii < 48; ii++)
//		for (jj = ii + 1; jj < 47; jj++)
//			bzcu[ii][jj] = bzcu[ii][jj] / size;
//
//
//	for (ii = 0; ii < 48; ii++)//output_vector����Ϊ��ά����;�������Ԫ�أ�
//		for (jj = ii + 1; jj < 47; jj++)
//			bzckesa[ii][jj] = output_bzc[ii][jj];
//
//	/*�������ԣ�����Ȩ����wcd*/
//	for (i = 0; i < size; i++)
//		for (ii = 0; ii < 48; ii++)
//			for (jj = ii + 1; jj < 47; jj++)
//				if (featurep[ii][jj][i] * featurep[ii][jj][g_conti] != 0 && bzckesa[ii][jj] != -1)
//					wcd[i] += pow((featurep[ii][jj][i] - featurep[ii][jj][g_conti]), 2) / ((featurep[ii][jj][i] + featurep[ii][jj][g_conti])*bzckesa[ii][jj]);
//
//	//������������ɵ�ͼ��1�������ɵ�ͼ��0
//	for (i = 0; i < size; i++)
//	{
//		if (wcd[i] > 0.12)
//		{
//			xyimgnum++;
//			suspict.push_back(files[i].c_str());
//			suspict_wcd.push_back(wcd[i]);
//		}
//	}
//
//	/*���������log�ļ�*/
//	strcat(g_log_rec, "\n");
//	memset(g_log_rec, 0, sizeof(g_log_rec));
//	//	strcat(g_log_rec, GetTime());
//	//	strcat(g_log_rec, "\t�������ţ�");
//	strcat(g_log_rec, dir.substr(27, 22).c_str());
//	strcat(g_log_rec, "\t");//ͼƬ����Ϊ��
//	char pic_num[20];
//	_itoa(size, pic_num, 10);
//	strcat(g_log_rec, pic_num);
//	if (xyimgnum > 0)
//	{
//		char b[20];
//		sprintf(b, "\t%d", xyimgnum);
//		strcat(g_log_rec, b);
//		strcat(g_log_rec, "\n");
//		for (i = 0; i < xyimgnum; i++)
//		{
//			//			cout << "����ͼ��" << files[i].c_str() << endl;
//			strcat(g_log_rec, "\t\t\t");//\t����ͼ��
//			strcat(g_log_rec, suspict[i].c_str());
//			strcat(g_log_rec, "\t");//���ƶȣ�
//			float sim = (1.0 - suspict_wcd[i]) * 100;
//			char a[20];
//			sprintf(a, "%g", sim);
//			strcat(g_log_rec, a);
//			strcat(g_log_rec, "%%\n");
//		}
//	}
//	else
//	{
//		//		strcat(g_log_rec, "\t�ÿ���û������ͼ��\n");
//		strcat(g_log_rec, "\t0\n");
//		//		cout << "�ÿ���������ͼ��" << endl;
//	}
//	SaveLog(g_log_rec, g_log_adr, "a");
//
//
//	/*�ƺ�*/
//	suspict.clear();
//	suspict_wcd.clear();
//	memset(g_log_rec, 0, sizeof(g_log_rec));
//	memset(feature, 0, sizeof(feature));
//	memset(featurep, 0, sizeof(featurep));
//	memset(bzckesa, 0, sizeof(bzckesa));
//	memset(wcd, 0, sizeof(wcd));
//	memset(featdif, 0, sizeof(featdif));
//	files.clear();
//	memset(g_log_rec, 0, sizeof(g_log_rec));
//
//	/*����ֵ*/
//	return 0;
//}
//
//
//int ComputeImage(vector<string> files, double bzckesa[50][50], double *wcd, int conti)
//{
//	int i, ii, jj, k, size;
//	double	bzcu[50][50] = { 0 };			//��׼���е�u
//	double	featurep[50][50][30] = { 0 };	//����ͼ�����������������ʼ��//��ʲô	//30
//	int		feature[50][50][30] = { 0 };	//����ͼ�������ֵ��ʼ��	//����ͼ��ָ��ʲô��˼	//30�ҳ�30��λ�û���50��λ�����ơ�����������num_dir==49������������
//	int		featx[50][50] = { 0 };			//ѭ����ֵ��feature
//	int		featureall;					//ͼ������ֵ��				//��ʲô��
//	IplImage* imglk[30];				//����ͼ����				//30
//
//	size = files.size();
//	for (i = 0; i < size; i++)
//	{
//		memset(featx, 0, sizeof(featx));
//		//		strcpy(str,files[i].c_str());
//		imglk[i] = singlefeature((char*)files[i].c_str(), featx);				//featx[][50]
//		featureall = 0;                                    //ͼ������ֵ�͵ĳ�ʼ��
//		for (ii = 0; ii<48; ii++)                             //��featx������,��ͷ���ܲ����ú�������
//			for (jj = ii + 1; jj<47; jj++)
//			{
//			feature[ii][jj][i] = featx[ii][jj];
//			featureall = featureall + featx[ii][jj];
//			}
//		//��������������featurep��ʽ(5)  ���׼���е�u�ĺ�
//		for (ii = 0; ii<48; ii++)
//			for (jj = ii + 1; jj<47; jj++)
//			{
//			featurep[ii][jj][i] = (double)featx[ii][jj] / featureall;
//			bzcu[ii][jj] += (double)featx[ii][jj] / featureall * 1000;     //��׼���ֵ��С,���зŴ�1��
//			}
//	}
//	//������һ���˵�ÿһ��ͼƬ��
//	for (ii = 0; ii<48; ii++)//���׼���е�u
//		for (jj = ii + 1; jj<47; jj++)
//			bzcu[ii][jj] = bzcu[ii][jj] / size;
//	//�������Ծ��Ǵ�Ȩ����wcd
//	for (i = 0; i < size; i++)
//		for (ii = 0; ii<48; ii++)
//			for (jj = ii + 1; jj<47; jj++)
//				if (featurep[ii][jj][i] * featurep[ii][jj][conti] != 0 && bzckesa[ii][jj] != -1)
//					wcd[i] += pow((featurep[ii][jj][i] - featurep[ii][jj][conti]), 2) / ((featurep[ii][jj][i] + featurep[ii][jj][conti])*bzckesa[ii][jj]);
//	memset(imglk, 0, sizeof(imglk));
//	memset(feature, 0, sizeof(feature));
//	memset(featurep, 0, sizeof(featurep));
//
//	return 1;
//}

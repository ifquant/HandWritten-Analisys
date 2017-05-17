/*
�������ļ���segmentation.cpp ��������ʵ���ļ�
*/
#include "segmentation.h"

/*������*/
extern "C" _declspec(dllexport) char * __stdcall  WINAPI TEST(char *fpname1)
{
	return fpname1;//���ļ��е�·��
}
extern "C" _declspec(dllexport) char * __stdcall  WINAPI HWCV(char *fpname1, char *dest){

	/*��ȡ�����ļ��������ø������*/
	ReadConfig("D:\\HWCV\\config\\configure.cfg");

	/*��ʼ��log�ļ�*/
	memset(g_log_rec, 0, sizeof(g_log_rec));
	time_t timer;
	struct tm *tblock;
	timer = time(NULL);
	tblock = localtime(&timer);
	strcat(g_log_rec, "\n-----------------------------------HWCV������----\n");
	strcat(g_log_rec, asctime(tblock));
	SaveLog(g_log_rec, g_log_adr, "a");


	/*��������*/
	vector<string> suspict;		//��¼����ͼƬ��ַ
	vector<float> suspict_wcd;	//����ͼƬ��wcdֵ
	vector<string> files;		//�洢�������п����ļ�·��
	vector<string> dateVec, subjectVec, stuNum2;
	vector<string> flagVec;//��¼�鵽��ѧ�������п�����Ϣ

	int		i, ii, jj, feature[50][50][30] = { 0 }, featureall = 0;
	double	featurep[50][50][30] = { 0 };
	double  bzcu[50][50] = { 0 };
	double  bzckesa[50][50] = { 0 };
	double  wcd[30] = { 0 };

	int		featx[50][50] = { 0 };
	int		featdif[30] = { 0 };
	float	maxx = 0;			//�������ֵ�ı����ֵ
	int		xyimgnum = 0;				//����ͼƬ����Ŀ
	char	str[80];					//�洢��ַ

	/*��ѯ���ݿ�*/
	string stuNum = fpname1;
	SaveLog(fpname1, "D:\\HWCV\\numtxt.txt", "a");
	DbImg(stuNum, dateVec, subjectVec, stuNum2);


	/*����·��*/
	for (int cp_i = 0; cp_i < dateVec.size(); cp_i++)
	{
		files.push_back(CrPath(dateVec[cp_i], subjectVec[cp_i], stuNum2[cp_i]));
	}
	int size = files.size();/*�ҵ���·��������*/

	/*��ÿһ��ͼƬ���д���*/
	for (i = 0; i < size; i++)
	{
		memset(str, 0, sizeof(str));
		memset(featx, 0, sizeof(featx));
		memset(bzcu, 0, sizeof(bzcu));

		strcpy(str, files[i].c_str());

		singlefeature(str, featx);//featx[][50]
		featureall = 0;                       //ͼ������ֵ�͵ĳ�ʼ��
		for (ii = 0; ii < 48; ii++)           //��featx������,��ͷ���ܲ����ú�������
			for (jj = ii + 1; jj < 47; jj++)
			{
			feature[ii][jj][i] = featx[ii][jj];
			featureall = featureall + featx[ii][jj];
			}
		/*��������������featurep��ʽ(5)  ���׼���е�u�ĺ�*/
		for (ii = 0; ii < 48; ii++)
			for (jj = ii + 1; jj < 47; jj++)
			{
			featurep[ii][jj][i] = (double)featx[ii][jj] / featureall;
			bzcu[ii][jj] += (double)featx[ii][jj] / featureall * 1000;     //��׼���ֵ��С,���зŴ�1��
			}
	}/*������ȫ��ͼƬ*/

	/*���׼����u*/
	for (ii = 0; ii < 48; ii++)
		for (jj = ii + 1; jj < 47; jj++)
			bzcu[ii][jj] = bzcu[ii][jj] / size;


	/*���裺��ȡ��׼���ļ�*/
	int bzccolumns = 47;//txt�ļ�����47��
	vector<double *> output_bzc;
	if (!ReadScanf("D:\\HWCV\\config\\stdfile.db", bzccolumns, output_bzc)) return 0;
	for (ii = 0; ii < 48; ii++)//output_vector����Ϊ��ά����;�������Ԫ�أ�
		for (jj = ii + 1; jj < 47; jj++)
			bzckesa[ii][jj] = output_bzc[ii][jj];

	/*�������ԣ�����Ȩ����wcd*/
	for (i = 0; i < size; i++)
		for (ii = 0; ii < 48; ii++)
			for (jj = ii + 1; jj < 47; jj++)
				if (featurep[ii][jj][i] * featurep[ii][jj][g_conti] != 0 && bzckesa[ii][jj] != -1)
					wcd[i] += pow((featurep[ii][jj][i] - featurep[ii][jj][g_conti]), 2) / ((featurep[ii][jj][i] + featurep[ii][jj][g_conti])*bzckesa[ii][jj]);

	/*�󿨷���������ֵ*/
	for (i = 0; i < size; i++)
	{
		if (wcd[i] > 0.12)
		{
			xyimgnum++;
			suspict.push_back(files[i].c_str());
			suspict_wcd.push_back(wcd[i]);
			flagVec.push_back("1");//���ɱ��1
		}
		else
		{
			flagVec.push_back("0");
		}
	}

	/*����������ݿ�*/
	DbUpdate(stuNum, dateVec, subjectVec, stuNum2, flagVec);


	/*���������log�ļ�*/
	memset(g_log_rec, 0, sizeof(g_log_rec));
	strcpy(g_log_rec, "ͼƬ����Ϊ��");
	char pic_num[20];
	_itoa(size, pic_num, 10);
	strcat(g_log_rec, pic_num);
	if (xyimgnum > 0)
	{
		strcat(g_log_rec, "\n");
		for (i = 0; i < xyimgnum; i++)
		{
			strcat(g_log_rec, "\t");
			strcat(g_log_rec, suspict[i].c_str());
			strcat(g_log_rec, "\t");
			char a[20];
			sprintf(a, "%g", suspict_wcd[i]);
			strcat(g_log_rec, a);
			strcat(g_log_rec, "\n");
		}
	}
	else strcat(g_log_rec, "\tû������ͼ��\n");
	SaveLog(g_log_rec, g_log_adr, "a");


	/*�ƺ�*/
	suspict.clear();
	suspict_wcd.clear();
	output_bzc.clear();
	memset(g_log_rec, 0, sizeof(g_log_rec));
	memset(feature, 0, sizeof(feature));
	memset(featurep, 0, sizeof(featurep));
	memset(bzckesa, 0, sizeof(bzckesa));
	memset(wcd, 0, sizeof(wcd));
	memset(featdif, 0, sizeof(featdif));
	files.clear();
	dateVec.clear();
	subjectVec.clear();
	stuNum2.clear();
	flagVec.clear();


	/*���ص���ҳ���*/
	char out[40] = "��ǰʱ��Ϊ��";
	//strcat(out, asctime(tblock));
	//strcat(out, "<br>����ѧ��Ϊ��");
	strcat(out, fpname1);
	strcat(out, "\n");
	//if(xyimgnum>0)
	//	strcat(out,"���ף�<br>");
	sprintf(dest, out);

	/*����ֵ*/
	return "return_OK";
}



/*
�������ļ���segmentation.cpp ��������ʵ���ļ�
*/
#include "segmentation.h"
#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )//�޽�������
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

	vector<string> suspict;		//��¼����ͼƬ��ַ
	vector<float> suspict_wcd;	//����ͼƬ��wcdֵ
	vector<string> files;		//�洢�������п����ļ�·��
	vector<string> dateVec, subjectVec, stuNum2;
	vector<string> flagVec;//��¼�鵽��ѧ�������п�����Ϣ

	/*��ȡ�����ļ��������ø������*/
	if (!ReadConfig("D:/HWCV/config/configure.cfg"))
	{
		SaveLog("\t�����ļ���ȡʧ��\n", g_log_adr, "a");

		return 0;
	}

//	cout<<"ReadConfig success"<<endl;
//
//	string temp=g_db_hostName;
//	temp+=g_db_dBName;temp+=g_db_userName;temp+=g_db_password;
//	SaveLog((char*)temp.c_str(), g_log_adr, "a");
//
	//��ѯ���ݿ�
	string stuNum = fpname1;
	if (!DbImg(stuNum, dateVec, subjectVec, stuNum2))
	{
		memset(g_log_rec, 0, sizeof(g_log_rec));

		strcat(g_log_rec, GetTime());

		strcat(g_log_rec, "\t���ݿ��ѯ��������Ϊ��");
		strcat(g_log_rec,fpname1);
		strcat(g_log_rec, "��ѧ��\n");
		SaveLog(g_log_rec, g_log_adr, "a");

		return 0;
	}
	//SaveLog("�ɹ�DB������\n", g_log_adr, "a");
//	cout << "�ɹ�DB\n����Ϊ��" << subjectVec.size() << endl;

	//����·��
	int nn = 0;
	for (int cp_i = 0; cp_i < subjectVec.size(); cp_i++)
	{
		if (!strcmp(subjectVec[cp_i].substr(0, 1).c_str(), "4") || !strcmp(subjectVec[cp_i].substr(0, 1).c_str(), "9"))
		{
//			cout << "��ͼ��" <<subjectVec[cp_i].c_str()<<" "<<dateVec[cp_i].c_str()<<" "<<stuNum2[cp_i].c_str()<< endl;
			continue;
		}
		files.push_back(CrPath(dateVec[cp_i], subjectVec[cp_i], stuNum2[cp_i]));
		
//		cout<<"PATH:"<<files[nn++].c_str()<<endl;
		
//		SaveLog((char*)files[cp_i].c_str(), g_log_adr, "a");
//		SaveLog("\n", g_log_adr, "a");

	}
//	cout << "����·������" << endl;

	int size = files.size();/*�ҵ���·��������*/
	/*��ÿһ��ͼƬ���д���*/

	int realSize = 0;
	for (i = 0; i < size; i++)
	{
		memset(str, 0, sizeof(str));
		memset(featx, 0, sizeof(featx));
		memset(bzcu, 0, sizeof(bzcu));

		strcpy(str, files[i].c_str());
		try{
			singlefeature(str, featx);//featx[][50]
			//����������ͼ��˵��ͼ������ճ�����
			realSize += 1;
		}
		catch (_com_error e)
		{
			//û����������ͼ��˵���˵�ַ�µ�ͼ�񲻿���
			memset(g_log_rec, 0, sizeof(g_log_rec));

			strcat(g_log_rec, "\n��ȡ·����");
			strcat(g_log_rec, str);
			strcat(g_log_rec, " ��ͼ��ʧ��:");
			strcat(g_log_rec, (char*)e.Description());
			strcat(g_log_rec, " ��ͼ��ʧ�ܣ�\n");
			SaveLog(g_log_rec, g_log_adr, "a");

			continue;
		}
//		cout << "����opencv\n" << endl;
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
	if (realSize == 0)
	{
		SaveLog("\t�˿���û��һ������ͼ����ã�\n", g_log_adr, "a");
		return 0;
	}
	/*���׼����u*/
	for (ii = 0; ii < 48; ii++)
		for (jj = ii + 1; jj < 47; jj++)
			bzcu[ii][jj] = bzcu[ii][jj] / realSize;


	/*���裺��ȡ��׼���ļ�*/
	int bzccolumns = 47;//txt�ļ�����47��
	vector<double *> output_bzc;
	if (!ReadScanf("D:\\HWCV\\config\\stdfile.db", bzccolumns, output_bzc))
	{
		memset(g_log_rec, 0, sizeof(g_log_rec));

		SaveLog("\n��ȡ·����D:\\HWCV\\config\\stdfile.db �ı�׼���ļ�ʧ�ܣ�\n", g_log_adr, "a");
		return 0;
	}
	for (ii = 0; ii < 48; ii++)//output_vector����Ϊ��ά����;�������Ԫ�أ�
		for (jj = ii + 1; jj < 47; jj++)
			bzckesa[ii][jj] = output_bzc[ii][jj];

	/*�������ԣ�����Ȩ����wcd*/
	for (i = 0; i < realSize; i++)
		for (ii = 0; ii < 48; ii++)
			for (jj = ii + 1; jj < 47; jj++)
				if (featurep[ii][jj][i] * featurep[ii][jj][g_conti] != 0 && bzckesa[ii][jj] != -1)
					wcd[i] += pow((featurep[ii][jj][i] - featurep[ii][jj][g_conti]), 2) / ((featurep[ii][jj][i] + featurep[ii][jj][g_conti])*bzckesa[ii][jj]);

	//������������ɵ�ͼ��1�������ɵ�ͼ��0
	for (i = 0; i < dateVec.size(); i++)
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
	
	//����������ݿ�
	DbUpdate(stuNum, dateVec, subjectVec, stuNum2, flagVec);
//	cout << "���ݿ�������" << endl;

	/*���������log�ļ�*/
	strcat(g_log_rec, "\n");
	memset(g_log_rec, 0, sizeof(g_log_rec));
	strcat(g_log_rec, GetTime());
	strcat(g_log_rec, "\t�������ţ�");
	strcat(g_log_rec, fpname1);
	strcat(g_log_rec, " ͼƬ����Ϊ��");
	char pic_num[20];
	_itoa(realSize, pic_num, 10);
	strcat(g_log_rec, pic_num);
	if (xyimgnum > 0)
	{
		
	/*	strcat(g_log_rec, "\t");
		strcat(g_log_rec, suspict[0].c_str());
		strcat(g_log_rec, "\t");
		char a[20];
		sprintf(a, "%g", suspict_wcd[0]);
		strcat(g_log_rec, a);
	*/	strcat(g_log_rec, "\n");
		for (i = 0; i < xyimgnum; i++)
		{
			strcat(g_log_rec, "\t\t\t\t����ͼ��");
			strcat(g_log_rec, suspict[i].c_str());
			strcat(g_log_rec, "\t���ƶȣ�");
			float sim=(1.0-suspict_wcd[i])*100;
			char a[20];
			sprintf(a, "%g", sim);
			strcat(g_log_rec, a);
			strcat(g_log_rec, "%%\n");
		}
	}
	else 
		strcat(g_log_rec, "\t�ÿ���û������ͼ��\n"); 
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

	/*����ֵ*/
	return 0;
}



#pragma once
#ifdef WIN32                            //����VC6��STL��һЩ����ȫ֧�����
#pragma warning (disable: 4514 4786)
#endif
#include <time.h>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <cv.h>
#include<io.h>             //�����5�����ڶ�ȡ�ļ����µ������ļ���
#include<vector>
#include <string.h>
#include<windows.h>        //���ڵ�����ʾ��,,,�мǣ�������<windows.h>ʱ����Ҫ����MFC����Afx.h)
#include<string.h>
using namespace std;

int*		binary(IplImage*  img,int bithro);				//��ֵ��ͼ��
int			outlinefeature(IplImage* imglk,int feature[ ][50]);  //����ͼ�����������ֵ            
int			read_scanf(const string &filename,const int &cols,vector<double *> &_vector);	//��ȡ�Ѿ���õ�����ֵ
IplImage*	Cjbsb(IplImage* img,IplImage* imgjbsb,int jbwhite,int jbblack);					//ͼ��Ǳ�ʶ��
IplImage*	outline(IplImage* imgbj);              //����ͼ���Ӧ������ͼ
IplImage*	singlefeature(char* path,int feature[ ][50]);	//�ó������ļ�������ֵ

char *fo = "H:\\logs_dll_check_only.txt";
char rec[2000] = "\n�������Ϊ��:";
FILE *fpzz3 = NULL;//��Ҫע��

extern "C" _declspec(dllexport) char * __stdcall  WINAPI TEST(char *fpname1){
	return fpname1;//���ļ��е�·��
}
extern "C" _declspec(dllexport) char * __stdcall  WINAPI HWCV(char *fpname1,char *dest)
{
	int		conti = 1;		
	int		size, i, ii, jj, feature[50][50][30] = { 0 }, featureall;					
	double	featurep[50][50][30] = { 0 },bzcu[50][50] = { 0 }, bzckesa[50][50] = { 0 }, wcd[30] = { 0 };	

	int		featx[50][50] = { 0 }, featdif[30] = { 0 }, maxi; float maxx = 0;			//�������ֵ�ı����ֵ
	int		xyimgnum = 0;					//����ͼƬ����Ŀ
	char	str[80];					//�洢��ַ


	/*��������*/
	vector<string> suspict;		//��¼����ͼƬ��ַ
	vector<float> suspict_wcd;
	vector<string> files;		//�洢�������п����ļ�·��
	vector<string> dateVec, subjectVec, stuNum2;
	vector<int> flagVec;//��¼�鵽��ѧ�������п�����Ϣ
	
	files.push_back("D:\\tupian\\201110\\0534\\010209400748.jpg");
	files.push_back("D:\\tupian\\201010\\0665\\010209400748.jpg");
	files.push_back("D:\\tupian\\201606\\0668\\010209400748.jpg");
	files.push_back("D:\\tupian\\201101\\0799\\010209400748.jpg");
	files.push_back("D:\\tupian\\201101\\0883\\010209400748.jpg");
	files.push_back("D:\\tupian\\201201\\0884\\010209400748.jpg");
	files.push_back("D:\\tupian\\201107\\0885\\010209400748.jpg");
	files.push_back("D:\\tupian\\201307\\0886\\010209400748.jpg");
	files.push_back("D:\\tupian\\201307\\0887\\010209400748.jpg");
	files.push_back("D:\\tupian\\201107\\0888\\010209400748.jpg");
	files.push_back("D:\\tupian\\201404\\4685\\010209400748.jpg");
	files.push_back("D:\\tupian\\201104\\1180\\010209400748.jpg");
	files.push_back("D:\\tupian\\201110\\1181\\010209400748.jpg");
	files.push_back("D:\\tupian\\201510\\0359\\080215203444.jpg");
	files.push_back("D:\\tupian\\201212\\0101\\010209400748.jpg");
	files.push_back("D:\\tupian\\201606\\4927\\010209400748.jpg");

	size = files.size();	//ͼ�����Ŀ

	//��ʼ��ÿһ��ͼƬ���д���
	for (i = 0; i < size; i++)
	{
		memset(str, 0, sizeof(str));
		memset(featx, 0, sizeof(featx));
		memset(bzcu, 0, sizeof(bzcu));

		strcpy(str, files[i].c_str());

		singlefeature(str, featx);				//featx[][50]
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
	//----------------------------------------------------------//
	for (ii = 0; ii < 48; ii++)//���׼���е�u
		for (jj = ii + 1; jj < 47; jj++)
			bzcu[ii][jj] = bzcu[ii][jj] / size;


	/*����׼���е�kesa���ؽ���*/
	string bzcfile = "D:/Xiangmu/Img/bzc/bzc.txt";
	//txt�ļ�����47��
	int bzccolumns = 47;
	vector<double *> output_bzc;
	if (!read_scanf(bzcfile, bzccolumns, output_bzc)) return 0;

	//output_vector����Ϊ��ά����;�������Ԫ�أ�
	//int rows=output_bzc.size();
	for (ii = 0; ii < 48; ii++)
		for (jj = ii + 1; jj < 47; jj++)
			bzckesa[ii][jj] = output_bzc[ii][jj];

	//�������Ծ��Ǵ�Ȩ����wcd
	for (i = 0; i < size; i++)
		for (ii = 0; ii < 48; ii++)
			for (jj = ii + 1; jj < 47; jj++)
				if (featurep[ii][jj][i] * featurep[ii][jj][conti] != 0 && bzckesa[ii][jj] != -1)
					wcd[i] += pow((featurep[ii][jj][i] - featurep[ii][jj][conti]), 2) / ((featurep[ii][jj][i] + featurep[ii][jj][conti])*bzckesa[ii][jj]);

	//�󿨷���������ֵ 
	for (i = 0; i < size; i++)
	{
		if (maxx < wcd[i]){ maxx = wcd[i]; maxi = i; }
		if (wcd[i] > 0.12)
		{
			xyimgnum++;
			suspict.push_back(files[i].c_str());
			suspict_wcd.push_back(wcd[i]);
			flagVec.push_back(1);//���ɱ��
		}else
		{
			flagVec.push_back(0);
		}
	}
	
	/*�洢�ļ���¼*/
	//char*	fpname = "C:/Users/��˧˧/Desktop/result2.txt";
	//char	record[2400] = { 0 };
	//FILE*	fpzz = NULL;//��Ҫע��

	fpzz3 = fopen(fo, "a");  //�����ļ� //a		
	if (NULL == fpzz3) return "ERR";//Ҫ���ش������
	fprintf(fpzz3, rec); //�ӿ���̨�ж��벢���ı����
	fclose(fpzz3);
	fpzz3 = NULL;//��Ҫָ��գ������ָ��ԭ���ļ���ַ  

	//���������txt	
	memset(rec, 0, sizeof(rec));
	strcpy(rec, "ͼƬ����Ϊ��");
	char pic_num[20];
	_itoa(size, pic_num, 10);
	strcat(rec, pic_num);
	if (xyimgnum > 0)
	{
		strcat(rec, "\n");
		for (i = 0; i < xyimgnum; i++)
		{
			strcat(rec, "\t");
			strcat(rec, suspict[i].c_str());
			strcat(rec, "\t");
			char a[20];
			sprintf(a, "%g", suspict_wcd[i]);
			strcat(rec, a);
			strcat(rec, "\n");
		}
	}
	else strcat(rec, "\tû������ͼ��\n");

	fpzz3 = fopen(fo, "a");  //�����ļ� //a
	if (NULL == fpzz3) return "ERR";//Ҫ���ش������
	fprintf(fpzz3, rec); //�ӿ���̨�ж��벢���ı����
	fclose(fpzz3);
	fpzz3 = NULL;//��Ҫָ��գ������ָ��ԭ���ļ���ַ  

	suspict.clear();
	suspict_wcd.clear();
	output_bzc.clear();

	//memset(record, 0, 2400);
	memset(feature, 0, sizeof(feature));
	memset(featurep, 0, sizeof(featurep));
	memset(bzckesa, 0, sizeof(bzckesa));
	memset(wcd, 0, sizeof(wcd));
	memset(featdif, 0, sizeof(featdif));




	char out[100]="�ɹ���\n";
	strcat(out, fpname1);
	sprintf(dest, out );

	return "return_OK";
}



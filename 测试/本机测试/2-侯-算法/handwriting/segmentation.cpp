/* 	��������segmentation.c
���ܣ��ܳ��򣺶���ͼ���ļ����������������Ч��
*/
//#include "stdafx.h"
#pragma once
#include <time.h> 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include "Point.h"
#include "Cword.h"
//#include "FreeImage.h"     //���ڶ�gif��ͼ��,����gifͼ��ת��Ϊpng��
#include<io.h>             //�����5�����ڶ�ȡ�ļ����µ������ļ���
#include<vector>
#include<iostream>
#include <string.h>
#include<windows.h>        //���ڵ�����ʾ��,,,�мǣ�������<windows.h>ʱ����Ҫ����MFC����Afx.h)
#include<string.h>
using namespace std;
#ifdef WIN32                            //����VC6��STL��һЩ����ȫ֧�����
#pragma warning (disable: 4514 4786)
#endif

void		getFiles(string	path, vector<string>& files );//9����ȡ�ļ����������ļ���  
void		on_mouse( int event, int x, int y, int flags, void* ustc);            
char*		getType(char fileName[], char type[]);  //2����ȡͼ������  
int*		binary(IplImage* img,int bithro); //3����ֵ��ͼ�� 
int			getFolders(string path, vector<string>& files );//11����ȡ�ļ����������ļ��е�����          
int			read_scanf(const string &filename,const int &cols,vector<double *> &_vector);//12����ȡ�Ѿ���õ�����ֵ
int			outlinefeature(IplImage* imglk,int feature[ ][50]);    //7������ͼ�����������ֵ
int			searchDir(char* path, vector<string> &dir);//��ȡĿ¼��һ��������ļ���
IplImage*	Cjbsb(IplImage*	img,IplImage* imgjbsb,int jbwhite,int jbblack);//4��ͼ��Ǳ�ʶ��        
IplImage*	worddivide(IplImage* imgbj,int hthro,int wthro,int *gridx,int *gridy,int *gxx,int *gyy); //5��Ϊ���������Ϸ���
IplImage*	outline(IplImage* imgbj); //6������ͼ���Ӧ������ͼ                  
IplImage*	gif2ipl(const char* filename);  //1����ȡgif���ⲿ����
IplImage*	wordrecognize(IplImage* imgbj,int *gridx,int *gridy,Cword *wordbox,int gx,int gy);//8���жϷ����е��Ƿ�Ϊ����       
IplImage*	singlefeature(char* path,int feature[ ][50]);//10���ó������ļ�������ֵ  

int pos_x=0,pos_y=0;
bool pos_flag=false;
IplImage* src;
int picAll = 0, picSus = 0;
int stuAll = 0, stuSus = 0;

int ComputeImage(vector<string> files, double bzckesa[50][50], double *wcd, int conti)
{	int i,ii,jj,k,size;
	double	bzcu[50][50]={0};			//��׼���е�u
	double	featurep[50][50][30]={0};	//����ͼ�����������������ʼ��//��ʲô	//30
	int		feature[50][50][30]={0};	//����ͼ�������ֵ��ʼ��	//����ͼ��ָ��ʲô��˼	//30�ҳ�30��λ�û���50��λ�����ơ�����������num_dir==49������������
	int		featx[50][50]={0};			//ѭ����ֵ��feature
	int		featureall;					//ͼ������ֵ��				//��ʲô��
	IplImage* imglk[30];				//����ͼ����				//30

	size=files.size();
	for (i = 0;i < size;i++)
	{  
		memset(featx,0,sizeof(featx));
//		strcpy(str,files[i].c_str());
		imglk[i]=singlefeature((char*)files[i].c_str(),featx);				//featx[][50]
		featureall=0;                                    //ͼ������ֵ�͵ĳ�ʼ��
		for(ii=0;ii<48;ii++)                             //��featx������,��ͷ���ܲ����ú�������
			for(jj=ii+1;jj<47;jj++)
			{
				feature[ii][jj][i]=featx[ii][jj];
				featureall=featureall+featx[ii][jj];
			}
		//��������������featurep��ʽ(5)  ���׼���е�u�ĺ�
		for(ii=0;ii<48;ii++)                               
			for(jj=ii+1;jj<47;jj++)
			{
				featurep[ii][jj][i]=(double)featx[ii][jj]/featureall;
				bzcu[ii][jj]+=(double)featx[ii][jj]/featureall*1000;     //��׼���ֵ��С,���зŴ�1��
			}
	}
	//������һ���˵�ÿһ��ͼƬ��
	for(ii=0;ii<48;ii++)//���׼���е�u
		for(jj=ii+1;jj<47;jj++)
			bzcu[ii][jj]=bzcu[ii][jj]/size;
	   //�������Ծ��Ǵ�Ȩ����wcd
	for (i = 0;i < size;i++)
		for(ii=0;ii<48;ii++)
			for(jj=ii+1;jj<47;jj++)	
				if(featurep[ii][jj][i]*featurep[ii][jj][conti]!=0 && bzckesa[ii][jj]!=-1)
					wcd[i]+=pow((featurep[ii][jj][i]-featurep[ii][jj][conti]),2)/((featurep[ii][jj][i]+featurep[ii][jj][conti])*bzckesa[ii][jj]);
	memset(imglk,0,sizeof(imglk));
	memset(feature,0,sizeof(feature));
	memset(featurep,0,sizeof(featurep));

	return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	// �������    
	vector<string> dir;				//�洢Ŀ¼
	int conti=1;     //�Ա�ͼ��ı��
	int size_dir,num_dir;
	char	record[2400]={0};

	// ׼������ļ�
	char*	fpname= "C:/Users/��˧˧/Desktop/result2.txt"; 
	FILE*	fpzz=NULL;//��Ҫע��
	//fpzz=fopen(fpname,"w+");  //�����ļ� //a		
	//if(NULL==fpzz) return -1;//Ҫ���ش������
	//fprintf(fpzz,record); //�ӿ���̨�ж��벢���ı����
	//fclose(fpzz);
	//fpzz=NULL;//��Ҫָ��գ������ָ��ԭ���ļ���ַ  
	
	// ��ȡ������ļ��е�size
	char path[100] =  "E:/xiangmu/Img/imgjiaobiao/";//D:/xiangmu/Img/imgjiaobiao/
	searchDir(path, dir);//��ȡfilePath�µ�����һ��Ŀ¼���洢��dir��
	
//	dir.push_back("E:/xiangmu/Img/imgjiaobiao/010211100518"); //�洢Ŀ¼
	size_dir=dir.size(); //dir�Ĵ�С����ѧ��������
	stuAll = size_dir;
	cout << "ѧ������Ϊ" << stuAll << endl;
	
	// ��ʼ���ÿ���ļ����µ�
	for(num_dir=0;num_dir<size_dir;num_dir++)//��ÿһ��ѧ��Ŀ¼����ѭ��
	{
		int		size,i,ii,jj;				//ͨ�ñ���
		double	bzckesa[50][50]={0};		//��׼��				
		double	wcd[30]={0};				//��¼��������				//30Ӧ��ָ�ľ���ÿ���˵�ͼƬ��Ŀ
		int		featdif[30]={0};			//ÿ��ͼ������ֵ��������ƽ��ֵ�Ĳ�	//30
		int		maxi;float maxx=0;			//�������ֵ�ı����ֵ
		int		xyimgnum=0;					//����ͼƬ����Ŀ

		vector<string> suspict;		//��¼����ͼƬ��ַ
		vector<float> suspict_wcd;
		vector<string> files;		//�洢�ļ�·��
		
		getFiles(dir[num_dir].c_str(), files );	//������ǰ�ļ����µ������ļ�
		//���
		printf("���ڽ��е�%d��Ŀ¼Ϊ��%s",num_dir,dir[num_dir].c_str());

		size = files.size();	//ͼ�����Ŀ
		//���
		printf("�ļ�����Ϊ��%d\t",size);

		//����׼���е�kesa���ؽ���
		string bzcfile="D:/Xiangmu/Img/bzc/bzc.txt";
		//txt�ļ�����47��
		int bzccolumns=47;
		vector<double *> output_bzc;
		if(!read_scanf(bzcfile,bzccolumns,output_bzc)) return 0;
		//output_vector����Ϊ��ά����;�������Ԫ�أ�
		//int rows=output_bzc.size();
		for(ii=0;ii<48;ii++)
			for(jj=ii+1;jj<47;jj++)
				bzckesa[ii][jj]=output_bzc[ii][jj];

		//��ʼ��ÿһ��ͼƬ���д���
		for(int r=0;r<size;r++)
		{
			memset(wcd, 0, sizeof(wcd));
			ComputeImage(files, bzckesa, wcd, r);
			xyimgnum=0;
			//�󿨷���������ֵ 
			for (i = 0;i < size;i++)
			{
//				cout << files[i].c_str()<< "  " << wcd[i] << endl;
//				if(maxx<wcd[i]){ maxx=wcd[i]; maxi=i;}
				if(wcd[i]>0.12)
				{ 
					xyimgnum++; 
					suspict.push_back(files[i].c_str());
					suspict_wcd.push_back(wcd[i]);
				}
			}
			if (xyimgnum<3) break;
		}

		//���������txt	
		//------------------------------------------------------//
		char record[8000];
		memset(record, 0, sizeof(record));
		char pic_num[20];
		memset(pic_num, 0, sizeof(pic_num));
		_itoa(size, pic_num, 10);
		strcat(record, dir[num_dir].substr(27, 22).c_str()); //ѧ��
		strcat(record, "\t");
		strcat(record,pic_num);
		if(xyimgnum>0)
		{
			stuSus++;
			char b[20];
			sprintf(b, "\t%d", xyimgnum);
			strcat(record, b);
			strcat(record, "\n");
//			cout << xyimgnum << endl;;
			for(int t=0;t<xyimgnum;t++)
			{
				strcat(record,"\t\t\t");
				strcat(record,suspict[t].c_str());
				strcat(record,"\t");
				char a[80];
				memset(a,0, sizeof(a));
				//cout << "  " << suspict_wcd[t]<<endl;
				//cout<< "adwada"<<endl;
				sprintf(a, "%f", suspict_wcd[t]);
				strcat(record,a);
				strcat(record,"\n");
			}
		}
		else
		{
			strcat(record, "\t0\n");
		}

		fpzz=fopen(fpname,"a");  //�����ļ� //a
		if(NULL==fpzz) return -1;//Ҫ���ش������
		fprintf(fpzz,record); //�ӿ���̨�ж��벢���ı����
		fclose(fpzz);
		fpzz=NULL;//��Ҫָ��գ������ָ��ԭ���ļ���ַ  

		suspict.clear();
		suspict_wcd.clear();
		output_bzc.clear();

		memset(record,0,2400);
		memset(bzckesa,0,sizeof(bzckesa));
		memset(wcd,0,sizeof(wcd));
		memset(featdif,0,sizeof(featdif));

		printf("����������%d\t",xyimgnum);
		
		picAll += size;
		picSus += xyimgnum;
		printf("ȫ��:%d���ɣ�%d����Ϊ��%g\n",picAll, picSus,((float)picSus)/((float)picAll));
		xyimgnum=0;

	}

	dir.clear();

	cout << "ѧ������:" << stuAll << " ����������" << stuSus << endl;
	printf("�Ѿ���ӡ��txt�У�");
	system("start C:/Users/��˧˧/Desktop/result2.txt");
	system("pause");

  	return 0; //(1-wcd[maxi])*100

}

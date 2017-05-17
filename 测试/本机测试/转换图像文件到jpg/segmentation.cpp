/* 	��������segmentation.c
���ܣ��ܳ��򣺶���ͼ���ļ����������������Ч��
*/
//#include "stdafx.h"
#include <time.h> 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include "Point.h"
#include "FreeImage.h"     //���ڶ�gif��ͼ��,����gifͼ��ת��Ϊpng��
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

/*-----------��������-----------------------*/

void		getFiles(string	path, vector<string>& files );//9����ȡ�ļ����������ļ���        
char*		getType(char fileName[], char type[]);  //2����ȡͼ������  
int*		binary(IplImage* img,int bithro); //3����ֵ��ͼ�� 
int			getFolders(string path, vector<string>& files );//11����ȡ�ļ����������ļ��е�����          
int			read_scanf(const string &filename,const int &cols,vector<double *> &_vector);//12����ȡ�Ѿ���õ�����ֵ
int			searchDir(char* path, vector<string> &dir);//��ȡĿ¼��һ��������ļ���
IplImage*	Cjbsb(IplImage*	img,IplImage* imgjbsb,int jbwhite,int jbblack);//4��ͼ��Ǳ�ʶ��                    
IplImage*	gif2ipl(const char* filename);  //1����ȡgif���ⲿ����     
IplImage*	singlefeature(char* path,int feature[ ][50],int flag);//10���ó������ļ�������ֵ  

int pos_x=0,pos_y=0;
bool pos_flag=false;
IplImage* src;
int picAll=0,picSus=0;

int main()
{
	time_t start ,end ;//��ʱ
	double cost;  time(&start); 

	//�������
	//------------------------------------------------------//
	char path[100] =  "D:\\xiangmu\\Img\\imgjiaobiao3\\";
	vector<string> dir;				//�洢Ŀ¼
	int conti=1;     //�Ա�ͼ��ı��
	int size_dir,num_dir;

	searchDir(path, dir);//��ȡfilePath�µ�����һ��Ŀ¼���洢��dir��
	size_dir=dir.size(); //dir�Ĵ�С����ѧ��������

	//��ʼת��
	//-------------------------------------------------------------//
	for(num_dir=0;num_dir<size_dir;num_dir++)//��ÿһ��ѧ��Ŀ¼����ѭ��  
	{
		int		size,i,j,ii,jj;				//ͨ�ñ���
		char	str[80];					//�洢��ַ
		int		featx[30][50];
		vector<string> files;		//�洢�ļ�·��
		
		getFiles(dir[num_dir].c_str(), files );	//������ǰ�ļ����µ������ļ�
		//���
		printf("\n��%d��Ŀ¼��%s",num_dir,dir[num_dir].c_str());

		size = files.size();	//ͼ�����Ŀ
		//���
		printf("\t������%d\t",size);

		//��ʼ��ÿһ��ͼƬ���д���
		//------------------------------------------------------//
		int flag=1;
		for (i = 0;i < size;i++)
		{  
			memset(str,0,sizeof(str));
			strcpy(str,files[i].c_str());
			try
			{
				singlefeature(str,featx,flag);//strͼƬ·�� featx��ͼƬ����ֵ�����ڱ�����featx��
			}catch(int x)
			{
				
			}
			flag=0;
		}


	}
	return 0;
}


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
#include<io.h>             //�����5�����ڶ�ȡ�ļ����µ������ļ���
#include<vector>
#include<iostream>
#include <string.h>
#include<windows.h>
#include<string.h>
using namespace std;
#ifdef WIN32                            //����VC6��STL��һЩ����ȫ֧�����
#pragma warning (disable: 4514 4786)
#endif

/*-----------��������-----------------------*/

void		getFiles(string	path, vector<string>& files );//9����ȡ�ļ����������ļ���  
int			getFolders(string path, vector<string>& files );//11����ȡ�ļ����������ļ��е�����          
int			searchDir(char* path, vector<string> &dir);//��ȡĿ¼��һ��������ļ���

int main()
{

	char path[100] =  "E:/xiangmu/Img/imgjiaobiao/";
    
	vector<string> dir; //�洢Ŀ¼
	int size_dir,num_dir;

	char*	fpname= "C:/Users/��˧˧/Desktop/result2.txt"; 
	char	record[2400]={0};
	FILE*	fpzz=NULL;//��Ҫע��

	searchDir(path, dir);//��ȡfilePath�µ�����һ��Ŀ¼���洢��dir��
	size_dir=dir.size(); //dir�Ĵ�С����ѧ��������
	
	
	//��ʼ���
	//-------------------------------------------------------------//
	for(num_dir=0;num_dir<size_dir;num_dir++)//��ÿһ��ѧ��Ŀ¼����ѭ��
	{
		int i=0;
		vector<string> files;		//�洢�ļ�·��
		
		getFiles(dir[num_dir].c_str(), files );	//������ǰ�ļ����µ������ļ�
		int size=files.size();
		cout<<"numdir: "<<num_dir<<" size: "<<size<<endl;

		//��ʼ��ÿһ��ͼƬ���д���
		//------------------------------------------------------//
		for (i = 0;i < size;i++)	 cout<<"\t"<<files[i].c_str()<<endl;
		cout<<endl;
		

	}

}
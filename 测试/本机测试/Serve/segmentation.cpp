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
    
int searchDir(char* path, vector<string> &dir);//��ȡĿ¼��һ��������ļ���

int main()
{

	char path[100] = "E:/xiangmu/Img/imgjiaobiao/";

	vector<string> dir; //�洢Ŀ¼
	

	char*	fpname = "C:/Users/��˧˧/Desktop/result2.txt";
	char	record[2400] = { 0 };
	FILE*	fpzz = NULL;//��Ҫע��

	searchDir(path, dir);//��ȡfilePath�µ�����һ��Ŀ¼���洢��dir��
	int size = dir.size(); //dir�Ĵ�С����ѧ��������


	//��ʼ���
	//-------------------------------------------------------------//
	for (int i = 0; i < size; i++)//��ÿһ��ѧ��Ŀ¼����ѭ��
	{
		cout << dir[i].c_str() << endl;
		ShellExecute(NULL, "open", 
			"D:\\CODE\\HWCV\\����\\HWCV-exe����\\Release\\HWCV.exe", 
			dir[i].c_str(), 
			NULL, 
			SW_SHOWNORMAL);	
	}
	return 0;
}
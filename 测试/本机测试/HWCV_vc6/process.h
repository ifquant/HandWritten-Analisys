/*
ͷ�ļ���process.h ͼ������ͷ�ļ�
*/
#pragma once
#include "StdAfx.h"
#include "Point.h"
#include "path.h"
#include "process.h"
#include <cv.h> 
#include <direct.h>
#include <io.h> 
#include <iostream>
#include <math.h>
#include <malloc.h>
#include <highgui.h> 
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

/*ȫ�ֱ���*/
extern IplImage* src;

/***************************************����ԭ��****************************************/

int ComputeImage(vector<string> files, double bzckesa[50][50], double *wcd, int conti);
/*
���ܣ�����ͼ���ļ������ж�ֵ��

@���� img iplimageͼ���ļ�
@���� bithro ��ֵ����ֵ
@����ֵ �����ص���Ŀ�����ã�
*/
int*  binary(IplImage*  img, int bithro);


/*
���ܣ�����ͼ���ļ�����ͼ����вü�

@���� img iplimageͼ���ļ�
@���� img �ü����iplimageͼ���ļ�
@jbwhite
@jbblack
@����ֵ ���زü����ͼ��
*/
IplImage* Cjbsb(IplImage* img, IplImage* imgjbsb, int jbwhite, int jbblack);


/*
���ܣ�����ͼ�������

@���� imgbj �ʼ����ֵ�ͼ��
@����ֵ ����õ�������ͼ��
*/
IplImage* outline(IplImage* imgbj);


/*
���ܣ�����ͼ�����������ͼ������ͼ�������ֵ
@���� imglk �����ͼ������ͼ
@���� feature �õ���ͼ������
@����ֵ �ɹ�1ʧ��0
*/
int outlinefeature(IplImage* imglk, int feature[][50]);


/*
���ܣ��Ե���ͼ��Ĵ������յõ�һ������ֵ�������������ͼ��֮��Ŀ�������

@���� path ͼ��������ַ
@���� feature ͼ�������ֵ
@����ֵ ������ͼ��
*/
IplImage* singlefeature(char* path, int feature[][50]);


/*
���ܣ�ϸ��֮ǰ��ͼ����ɫ��������ɫ��Χת����0-1

@���� ip ͼ��ľ��
@���� jp
@���� lx ͼ����
@���� ly ͼ��߶�
@����ֵ ��
*/
void beforethin(unsigned char *ip, unsigned char *jp, unsigned long lx, unsigned long ly);


/*���ܣ�ϸ���㷨 ��Rosenfeldϸ���㷨��������ɶԱʼ�ͼ��Ĺɼ���ȡ

@���� image ����ͼ���һά����
@���� lx ͼ����
@���� ly ͼ��߶�
@����ֵ �޷���ֵ
*/
void ThinnerRosenfeld(void *image, unsigned long lx, unsigned long ly);
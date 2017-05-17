/* 	��������singlefeature.c
���ܣ����ܳ��򣺶���ͼ���ļ����ó������ļ�������ֵ
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include "Point.h"
#include<io.h>
#include<vector>
#include<iostream>
#include <string.h>
#include <direct.h>
#include"Thinner.h"

using namespace std;
/*��������*/                            
int*		binary(IplImage*  img, int bithro);  //��ֵ��ͼ��      
int			outlinefeature(IplImage* imglk, int feature[][50]);//����ͼ�����������ֵ                         
IplImage*	Cjbsb(IplImage* img, IplImage* imgjbsb, int jbwhite, int jbblack);//ͼ��Ǳ�ʶ��

IplImage* singlefeature(char* path, int feature[][50]){
	//�������
	IplImage* img = 0;          //ԭͼ
	IplImage* imglk = 0;        //����ͼ
	IplImage* imggj = 0;        //�Ǽ�ͼ
	IplImage* imgjbsb = 0;      //�Ǳ�ʶ��ͼ
	IplImage* imgbj = 0;        //ֻ��ȡ�ʼǲ��ֵ�ͼ��
	IplImage* imgbjhf = 0;      //Ϊ���������Ϸ���
	IplImage* imgwzbj = 0;      //Ϊ�����������Ƿ�Ϊ���֣����ֱ�ǣ�

	int height, width, step, channels;
	uchar *data;

	int i, j;
	int *black;                 //���ڷ���ͼ��ÿ�к����صĸ���
	//int feature[50][50]={0};    //����ֵ��ʼ��

	img = cvLoadImage(path, 0);

	/* ��ȡͼ����Ϣ*/
	height = img->height;
	width = img->width;
	step = img->widthStep;
	channels = img->nChannels;
	data = (uchar *)img->imageData;

	/*��ʼ����*/

	/*ͼ��Ŵ�*/
	IplImage* imgbig = 0;          //ԭͼ�ķŴ�ͼ
	CvSize dst_cvsize;             //Ŀ��ͼ��Ĵ�С
	float scale = 1;
	if (width<840){
		scale = (float)840 / width;
		dst_cvsize.width = 840;
		dst_cvsize.height = (int)(height*scale);
	}
	else
	{
		dst_cvsize.width = width;
		dst_cvsize.height = height;
	}

	imgbig = cvCreateImage(dst_cvsize, img->depth, img->nChannels);
	cvResize(img, imgbig, CV_INTER_LINEAR);	// CV_INTER_NN - ����ڲ�ֵ,
	//CV_INTER_LINEAR - ˫���Բ�ֵ (ȱʡʹ��),
	//CV_INTER_AREA - ʹ�����ع�ϵ�ز�������ͼ����Сʱ�򣬸÷������Ա��Ⲩ�Ƴ��֡�
	//CV_INTER_CUBIC - ������ֵ.

	/*��ֵ��*/
	int bithro = 230;                              //�����ֵ������ֵ   (0--255)
	black = binary(imgbig, bithro);                    //��ֵ������ͳ�ƺ����صĸ���������ÿ�к����صĸ���(black)
	//cvNamedWindow("��ֵ�����ͼ",CV_WINDOW_AUTOSIZE);                   //��ʾͼ��
	//cvShowImage("��ֵ�����ͼ",img); 
	//printf("��ֵ�������ɣ���\n");



	/*�Ǳ�ʶ��*/
	int jbwhite = 5, jbblack = 4;
	imgjbsb = cvCreateImage(cvGetSize(imgbig), imgbig->depth, imgbig->nChannels);
	imgbj = Cjbsb(imgbig, imgjbsb, jbwhite, jbblack);                              //�������ֵıʼ�����


	/*����Ǽ�ͼ*/
	imggj = cvCreateImage(cvGetSize(imgbj), imgbj->depth, imgbj->nChannels);   //����
	cvCopy(imgbj, imggj, NULL);
	uchar *gjdata = (uchar *)imggj->imageData;

	beforethin(gjdata, gjdata, imggj->width, imggj->height);

	for (j = 0; j<imggj->height; j++)
	{ //ȡֵ��Χת��0--1  

		for (i = 0; i<imggj->width; i++)
		{
			if (gjdata[j*imggj->widthStep + i] == 255)
				gjdata[j*imggj->widthStep + i] = 1;
		}
	}
	ThinnerRosenfeld(imggj->imageData, imggj->height, imggj->width);

	for (j = 0; j<imggj->height; j++)
	{//ȡֵ��Χת��0--255,��ת����
		for (i = 0; i<imggj->width; i++)
		{
			if (gjdata[j*imggj->widthStep + i] == 1)
				gjdata[j*imggj->widthStep + i] = 0;
			else
				gjdata[j*imggj->widthStep + i] = 255;
		}
	}

	//����ͼ�� Ӧ������ͼ���ļ���
	/*
	char processPic[100]="E:/imggj/";
	char *namePic=new char[20];
	bool flag=false;
	string xuehao=path,kaoshihao=path;
	int num_iter=sizeof(path);
	for(int iter=0;iter<num_iter;iter++)
	{
	if(path[iter]=='x')
	{
	flag=true;
	break;
	}
	}
	if(flag)
	{
	xuehao=xuehao.substr(27,13);
	kaoshihao=kaoshihao.substr(40,5);
	}else
	{
	xuehao=xuehao.substr(27,12);
	kaoshihao=kaoshihao.substr(39,5);
	}
	strcat(processPic,xuehao.c_str());
	_mkdir(processPic);
	strcat(processPic,kaoshihao.c_str());
	strcat(processPic,".jpg");
	cvSaveImage(processPic,imggj);
	*/
	/*����Ǽ�������*/
	outlinefeature(imggj, feature);   //����ֵռ48*48�����������Σ�feature���÷���
	//cvWaitKey(0);

	/*�ͷ��ڴ�*/
	cvReleaseImage(&imgbig);
	cvReleaseImage(&img);
	cvReleaseImage(&imgbj);
	cvReleaseImage(&imglk);
	cvReleaseImage(&imgjbsb);
	cvReleaseImage(&imgbjhf);
	cvReleaseImage(&imgwzbj);
	cvDestroyAllWindows();

	return imggj;
}



/* 	��������singlefeature.c
���ܣ����ܳ��򣺶���ͼ���ļ����ó������ļ�������ֵ
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include "Point.h"
#include "FreeImage.h"     //���ڶ�gif��ͼ��
#include<io.h>             //�����5�����ڶ�ȡ�ļ����µ������ļ���
#include<vector>
#include<iostream>
using namespace std;
#include <string.h>
#include <direct.h>
#include"Thinner.h"

/*��������*/

void		getFiles(string path, vector<string>& files );//��ȡ�ļ����������ļ�                             
char*		getType(char fileName[], char type[]); //��ȡͼ������       
int*		binary(IplImage*  img,int bithro);  //��ֵ��ͼ��      
int			outlinefeature(IplImage* imglk,int feature[ ][50]);//����ͼ�����������ֵ                         
IplImage*	Cjbsb(IplImage* img,IplImage* imgjbsb,int jbwhite,int jbblack);//ͼ��Ǳ�ʶ��
IplImage*	gif2ipl(const char* filename);     //��ȡgif���ⲿ����

IplImage* singlefeature(char* path,int feature[ ][50],int flag){
	//�������
  	IplImage* img = 0;          //ԭͼ
    IplImage* imglk = 0;        //����ͼ
	IplImage* imggj = 0;        //�Ǽ�ͼ
	IplImage* imgjbsb = 0;      //�Ǳ�ʶ��ͼ
	IplImage* imgbj = 0;        //ֻ��ȡ�ʼǲ��ֵ�ͼ��

	char imgtype[10];           //�ж�ͼ������
  	int height,width,step,channels;
  	uchar *data;

	int *black;                 //���ڷ���ͼ��ÿ�к����صĸ���
	//int feature[50][50]={0};    //����ֵ��ʼ��

	getType(path, imgtype);
	if(strcmp(".gif", imgtype) == 0)
	{
		IplImage* Iplimg=gif2ipl(path);                   //gif ת rgb ��ά
	    img=cvCreateImage(cvGetSize(Iplimg),Iplimg->depth,1);

		cvCvtColor(Iplimg,img,CV_RGB2GRAY);                 //rgb ת�Ҷ�
		cvReleaseImage(&Iplimg);                            //�ͷ���ʱͼ����ڴ�
		cvFlip(img,NULL, 0);                                //���ڵõ��ĻҶ�ͼ�Ƿ�ת�ģ������ٷ�ת����
	}
	else if(strcmp(".jpg", imgtype) == 0 || strcmp(".png", imgtype) == 0)
		img=cvLoadImage(path,0);
	else 
		return NULL;

  	if(!img)
	{
   		printf("Could not load image file: %s\n",path);
    	exit(0);
  	}


  	// ��ȡͼ����Ϣ
  	height    = img->height;  
  	width     = img->width;	
  	step      = img->widthStep;	
  	channels  = img->nChannels;
  	data      = (uchar *)img->imageData;

	//��ʼ����

    //ͼ��Ŵ�
    IplImage* imgbig = 0;          //ԭͼ�ķŴ�ͼ
    CvSize dst_cvsize;             //Ŀ��ͼ��Ĵ�С
	float scale=1;
	if(width<850){
        scale=(float)850/width;
		dst_cvsize.width=850;
		dst_cvsize.height=(int)(height*scale);
	}
	else
	{
		dst_cvsize.width=width;
		dst_cvsize.height=height;
	}

	imgbig=cvCreateImage(dst_cvsize,img->depth,img->nChannels);
    cvResize(img,imgbig,CV_INTER_LINEAR);	// CV_INTER_NN - ����ڲ�ֵ,
											//CV_INTER_LINEAR - ˫���Բ�ֵ (ȱʡʹ��),
											//CV_INTER_AREA - ʹ�����ع�ϵ�ز�������ͼ����Сʱ�򣬸÷������Ա��Ⲩ�Ƴ��֡�
											//CV_INTER_CUBIC - ������ֵ.

	//��ֵ��
	int bithro=230;                              //�����ֵ������ֵ   (0--255)
    black=binary(imgbig,bithro);                    //��ֵ������ͳ�ƺ����صĸ���������ÿ�к����صĸ���(black)
    //cvNamedWindow("��ֵ�����ͼ",CV_WINDOW_AUTOSIZE);	//��ʾͼ��
    //cvShowImage("��ֵ�����ͼ",img); 
	//printf("��ֵ�������ɣ���\n");

    //�Ǳ�ʶ��,���г�ͼ��
	int jbwhite=5,jbblack=4;
	imgjbsb = cvCreateImage(cvGetSize(imgbig),imgbig->depth,imgbig->nChannels);
    imgbj=Cjbsb(imgbig,imgjbsb,jbwhite,jbblack);                              //�������ֵıʼ�����
 
	//�洢�ü����ͼ��
	//D:/xiangmu/Img/imgjiaobiao/010211100059x/0359.gif
	char isavePath[200]="E";

	//�˴���Ҫ�½�һ���½��ļ��е�ѡ��
	string name=path;
	strcat(isavePath, name.substr(1, 39).c_str());

	string md="mkdir ";
	md += isavePath;
	//��ϳ�������
	strcat(isavePath, name.substr(40, 5).c_str());
	strcat(isavePath, ".jpg");
	//�����ļ���
	if(flag) system(md.c_str());
	//����ͼ��
	cvSaveImage(isavePath,imgbj);



	cvReleaseImage(&imgbig);
  	cvReleaseImage(&img );  
	cvReleaseImage(&imgbj ); 
    cvDestroyAllWindows();  
	cout<<".";
  	return imggj;
}



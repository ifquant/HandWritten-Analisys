/* 	��������binary.c
���ܣ�����ͼ���ļ������ж�ֵ��
*/
#pragma once
#include <cv.h>  
#include <highgui.h> 
#include <stdlib.h>
#include <stdio.h>
int*  binary(IplImage*  img,int bithro)
{
	int height,width,step,channels;
	uchar *data;
	int i,j;
	static int black[1000];   //C���Բ��ᳫ����һ���ֲ������ĵ�ַ����Ĺ��ܣ���������붨��ľֲ��������羲̬������
	/* ��ȡͼ����Ϣ*/
  	height    = img->height;  
  	width     = img->width;	
  	step      = img->widthStep;	
  	channels  = img->nChannels;
  	data      = (uchar *)img->imageData;

	/*��ֵ������ͳ�ƺ����صĸ���*/
	for(i=0;i<height;i++)
	{
			for(j=0;j<width;j++)//��ͼ��ÿ������ж�ֵ��,ԭֵΪ128
				data[i*step+j*channels]=(data[i*step+j*channels]>bithro)?255:0;
	}

    /*����ÿһ�еĺ����ظ���*/
	int tempBlackPixel=0;
	
	memset(black,0,1000);            //##��ʼ���ڴ棬������������black����
	for(i=height-1;i>0;i--)
	{ 
		for(int j=0;j<width;j++)
		{
		   	if(data[i*step+j*channels]==0)        //�����ɫ��������
		   		tempBlackPixel+=1;
		}
		black[height-i]=tempBlackPixel;   //black��¼��ɫ������
		tempBlackPixel=0;
	}
	//��ֵ������ͳ�ƺ����صĸ���**********
	return black;
}



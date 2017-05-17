/* 	��������outline.c
���ܣ���������ͼ�񡣵õ���Ӧ������ͼ
*/
#pragma once
#include <cv.h>  
#include <highgui.h> 
#include <stdlib.h>
#include <stdio.h>

IplImage* outline(IplImage* imgbj)
{
	/*�������*/
    int i,j;
    int height,width,step,channels;
  	uchar *data;

    /*�����µ�ͼ��*/
	IplImage* imglk = cvCreateImage(cvGetSize(imgbj),imgbj->depth,imgbj->nChannels);

    /* ��ȡͼ����Ϣ*/
  	height    = imgbj->height;  
  	width     = imgbj->width;	
  	step      = imgbj->widthStep;	
  	channels  = imgbj->nChannels;
  	data      = (uchar *)imgbj->imageData;


	for(j=0;j<height;j++)
	{
		for(int i=0;i<width;i++)
			imglk->imageData[j*step+i*channels]=255;
		for( i=0;i<width-1;i++)
			if(data[j*step+(i+1)*channels]-data[j*step+i*channels]==255)             //�����Ҳ��
		   		imglk->imageData[j*step+i*channels]=0;
		    else if(data[j*step+i*channels]-data[j*step+(i+1)*channels]==255)        //��������
		   		imglk->imageData[j*step+(i+1)*channels]=0;
	}

	for(i=0;i<width;i++) 
		for(j=0;j<height-1;j++)
			if(data[j*step+i*channels]-data[(j+1)*step+i*channels]==255)             //�����²��
		   		imglk->imageData[(j+1)*step+i*channels]=0;
		    else if(data[(j+1)*step+i*channels]-data[j*step+i*channels]==255)        //�����ϲ��
		   		imglk->imageData[j*step+i*channels]=0;

	return imglk;
}
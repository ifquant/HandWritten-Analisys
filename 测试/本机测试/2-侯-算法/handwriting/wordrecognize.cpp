/* 	��������wordrecorgnize.c
���ܣ���������ͼ�񼰷���λ�á�ʶ������Ч�ַ��ķ���
*/

#include <cv.h>  
#include <highgui.h> 
#include <stdlib.h>
#include <stdio.h>
#include "Point.h"
#include "Cword.h"

IplImage* wordrecognize(IplImage* imgbj,int *gridx,int *gridy,Cword *wordbox,int gx,int gy){
	/*�������*/
    int i,j,ni,numw,nblack=0,wnum=0;
	//Cword wordbox[150];
	int sumnum=(gx-1)*(gy-1);

    int height,width,step,channels;
  	uchar *data;

	/*�����µ�ͼ��*/
	IplImage* imgwzbj = cvCreateImage(cvGetSize(imgbj),imgbj->depth,imgbj->nChannels);
	cvCopy(imgbj,imgwzbj,NULL);
	uchar *wzbjdata  = (uchar *)imgwzbj->imageData;

	/* ��ȡͼ����Ϣ*/
  	height    = imgbj->height;  
  	width     = imgbj->width;	
  	step      = imgbj->widthStep;	
  	channels  = imgbj->nChannels;
  	data      = (uchar *)imgbj->imageData;

	/*��ʼ����*/
	for(i=0;i<gx-1;i++)
		for(j=0;j<gy-1;j++){
			numw=i*(gy-1)+j+1;         
			wordbox[numw].wbegin.x=gridx[i];
			wordbox[numw].wbegin.y=gridy[j];
			wordbox[numw].wend.x=gridx[i+1];
			wordbox[numw].wend.y=gridy[j+1];
			//printf("The %dth word*** \n",numw);
		}
     //printf("The %dth word \n",numw);
     //printf("The sum of words: %d \n",sumnum);

	for(ni=1;ni<=sumnum;ni++){
		for(i=wordbox[ni].wbegin.x;i<wordbox[ni].wend.x;i++)                  
			for(j=wordbox[ni].wbegin.y;j<wordbox[ni].wend.y;j++){
				if(data[i*step+j*channels]==0)        //�����ɫ��������
		   		    nblack+=1;
			}
    	if(nblack>80){
			wordbox[ni].isword=true;
			wnum++;
			wordbox[ni].nn=wnum;

		    //printf("x= %d;;;y=%d \n",wordbox[ni].wbegin.x,wordbox[ni].wbegin.y);
            wzbjdata[(wordbox[ni].wbegin.x+2)*step+(wordbox[ni].wbegin.y+2)*channels]=0;        //����һ��ͼ�ϣ������֣���һ��+
            wzbjdata[(wordbox[ni].wbegin.x+1)*step+(wordbox[ni].wbegin.y+2)*channels]=0;
			wzbjdata[(wordbox[ni].wbegin.x+3)*step+(wordbox[ni].wbegin.y+2)*channels]=0;
			wzbjdata[(wordbox[ni].wbegin.x+2)*step+(wordbox[ni].wbegin.y+1)*channels]=0;
			wzbjdata[(wordbox[ni].wbegin.x+2)*step+(wordbox[ni].wbegin.y+3)*channels]=0;
			//wzbjdata[(wordbox[ni].wbegin.x)*step+(wordbox[ni].wbegin.y+2)*channels]=0;
			//wzbjdata[(wordbox[ni].wbegin.x+4)*step+(wordbox[ni].wbegin.y+2)*channels]=0;
			//wzbjdata[(wordbox[ni].wbegin.x+2)*step+(wordbox[ni].wbegin.y)*channels]=0;
			//wzbjdata[(wordbox[ni].wbegin.x+2)*step+(wordbox[ni].wbegin.y+4)*channels]=0;
		}
		else{
			wordbox[ni].isword=false;              
			
			wzbjdata[(wordbox[ni].wbegin.x+2)*step+(wordbox[ni].wbegin.y+2)*channels]=0;        //����һ��ͼ�ϣ��������֣���һ��-
            wzbjdata[(wordbox[ni].wbegin.x+2)*step+(wordbox[ni].wbegin.y+1)*channels]=0;
			wzbjdata[(wordbox[ni].wbegin.x+2)*step+(wordbox[ni].wbegin.y+3)*channels]=0;
			//wzbjdata[(wordbox[ni].wbegin.x+2)*step+(wordbox[ni].wbegin.y)*channels]=0;
			//wzbjdata[(wordbox[ni].wbegin.x+2)*step+(wordbox[ni].wbegin.y+4)*channels]=0;
		}
       wordbox[ni].blacknum=nblack;
	   nblack=0;
	}
    return imgwzbj;
}
/* 	��������Cjbsb.c
���ܣ�����ֻ�����������ͼ���ļ��������ֻ��ֿ���
���������ֻ�����������ͼ���ļ�������ֵ������ֵ���������б����б�
Ĭ�ϣ�hthro=10��wthro=6
*/
#include <cv.h>  
#include <highgui.h> 
#include <stdlib.h>
#include <stdio.h>

IplImage* worddivide(IplImage* imgbj,int hthro,int wthro,int *gridx,int *gridy,int *gxx,int *gyy){
	/*�������*/
    int height,width,step,channels;
  	uchar *data;

	int i,j,black[1000];
	int blackend=0;                      //��Ƿָ��߽��� 
    int mi=0,mx=500;                     //��Ƿָ����ں���ɫ���ٵ��ߺ���ֵ
	int gx=0,gy=0;                       //��¼�û��ߵ����ߵ��к����к�    gridx[10],gridy[30],
    memset(gridx,0,10);                  //��ʼ���ڴ棬������������
	memset(gridy,0,30);                  //��ʼ���ڴ棬������������

	/*�����µ�ͼ��*/
	IplImage* imgbjhf = cvCreateImage(cvGetSize(imgbj),imgbj->depth,imgbj->nChannels);   //�ʼ�����ͼ
	cvCopy(imgbj,imgbjhf,NULL);

    /* ��ȡͼ����Ϣ*/
  	height    = imgbjhf->height;  
  	width     = imgbjhf->width;	
  	step      = imgbjhf->widthStep;	
  	channels  = imgbjhf->nChannels;
  	data      = (uchar *)imgbjhf->imageData;
	

	/*����ı��*/
	/*����ÿһ�еĺ�ɫ���ص������˲�������ʹ�ö�ֵ���õ��ģ�*/
	int tempBlackPixelx=0;          //ѭ����¼ÿһ�еĺ�ɫ���ص���
	
	memset(black,0,1000);            //��ʼ���ڴ棬������������
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
		   	if(data[j*step+i*channels]==0)        //�����ɫ��������
		   		tempBlackPixelx+=1;		
		}
		black[j]=tempBlackPixelx;                 //black��¼��ɫ������
		tempBlackPixelx=0;
		//printf("The %dth black num is %d \n",j,black[j]); 
	}

    /*�������λ��*/
 	for(i=0;i<height;i++){
		if(black[i]<=hthro && blackend==0){
            blackend=1;             
            if(black[i]<=mx){                     //���º�ɫ���ٵĵ��߱�
				mx=black[i];
				mi=i;
			}
		}
		else if((blackend==1 && black[i]>hthro) || i==height-1){
			blackend=0;

			gridx[gx]=mi;
			//printf("<�б꣺%d>",gridx[gx]);
			gx++;             
			mx=500;
			mi=i;			
		}
	}

	 /*����ı��*/

    //����ÿһ�еĺ����ظ���
	int tempBlackPixely=0;	
	memset(black,0,1000);                         //��ʼ���ڴ棬������������
	for(i=0;i<width;i++) {
		for(j=0;j<height;j++){
		   	if(data[j*step+i*channels]==0)        //�����ɫ��������
		   		tempBlackPixely+=1;
		}
		black[i]=tempBlackPixely;                 //black��¼��ɫ������
		tempBlackPixely=0;
	}

    /*��������λ��*/
	for(i=0;i<width;i++){
		if(black[i]<=wthro){
			if(blackend==0){
				blackend=1;
			}
            if(black[i]<=mx){        //���º�ɫ���ٵĵ��߱�
				mx=black[i];
				mi=i;
			}
		}
		else if((blackend==1 && black[i]>wthro)){
			blackend=0;

			if(gy==0){
                gridy[gy]=mi;                         //���º�ɫ���ٵĵ���λ��
			    gy++;
			}
			else if(mi-gridy[gy-1]<=25){               //���Ƿ���̫С����������������һ��������
				gridy[gy-1]=mi;                        //
			}
			else{
				gridy[gy]=mi;                         //���º�ɫ���ٵĵ���λ��
				//printf("<�б꣺%d>",gridy[gy]);
			    gy++;
			}			
			mx=500; 
			mi=i;
		}
	}

	gridy[gy]=mi;                         //�����һ�н��д���
	gy++;
	//for(j=0;j<gy;j++)
    //    printf("The %dth row is %d \n",j,gridy[j]); 
	//for(i=0;i<gx;i++)
    //    printf("The %dth line is %d \n",i,gridx[i]); 
 
	/*�ʼ�����ͼ�ϻ��Ϸ���*/
    for(i=0;i<height;i++)
		for(j=0;j<gy;j++)
			 data[i*step+gridy[j]*channels]=0;

	for(i=0;i<width;i++)
		for(j=0;j<gx;j++)
			data[gridx[j]*step+i*channels]=0;

	*gxx=gx;
	*gyy=gy;
	//printf("�ָ����\n");

	return imgbjhf;
}
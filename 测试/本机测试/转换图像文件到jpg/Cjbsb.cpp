/* 	��������Cjbsb.c
���ܣ�����ͼ���ļ������ͼ��ĽǱ�
	�������ã�
		img ��ͼ
		imgjbsb �Ǳ�ͼ��ͷ
		jbwhite δ֪����1
		jbblack δ֪����2
	���������ֵıʼ����֡�

  ע�⣺����������У�����һ���ŵķ�����ȡһ�����飬�ƶ����飬ȷ�������е����ӣ�����к��߻������Ծ�ȷ��Ϊ�ű�
*/
#include <cv.h>  
#include <highgui.h> 
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

IplImage* Cjbsb(IplImage* img,IplImage* imgjbsb,int jbwhite,int jbblack){
/*�������*/
    int i,j,ii,jj,sumjb1,sumjb2,jbi=0,jbj=0;
    int height,width,step,channels;
	uchar *data;
	int brklab=0;
//1�� ��ȡͼ����Ϣ
  	height    = img->height;  
  	width     = img->width;	
  	step      = img->widthStep;	
  	channels  = img->nChannels;
  	data      = (uchar *)img->imageData;
	//IplImage* imgjbsb = cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
	cvCopy(img,imgjbsb,NULL);
	uchar *imgjbsbdata= (uchar *)imgjbsb->imageData;
//----------------------------------------//
//2���ҽű��λ��
//----------------------------------------//
	for(i=0;i<height/3;i++){ 
		for(j=0;j<width/5;j++){
			sumjb1=0;
			for(ii=0;ii<=14;ii++)  //������������²�14���Ҳ�14�İ׵���Ŀ(����Ϊ�ű����14�ĳ��Ȱɣ�)
		           sumjb1=sumjb1+imgjbsbdata[(i+ii)*step+j*channels];//�²�14�еĵ���İ׵���Ŀ
			for(jj=0;jj<=14;jj++)
		           sumjb1=sumjb1+imgjbsbdata[i*step+(j+jj)*channels];//�Ҳ�14�еĵ���İ׵���Ŀ
            if(sumjb1<=255*jbwhite){		//jbwhiteΪ����Ǳ��ϰ׵�������һ����ȡ                                                 
               sumjb2=0;
               for(ii=i+2;ii<i+12;ii++)            
	               for(jj=j+2;jj<j+12;jj++){
						if(imgjbsbdata[ii*step+jj*channels]>=200)
					       sumjb2=sumjb2+imgjbsbdata[ii*step+jj*channels];
				   }
			   if(sumjb2>=255*(100-jbblack)){                                 //����Ǳ��ںڵ������ڶ�����ȡ
				   jbi=i;//�ű�λ��
				   jbj=j;
				for(ii=i-2;ii<i+22;ii=ii+2)                                  //���λ��
	               for(jj=j-2;jj<j+22;jj=jj+2){
					   imgjbsbdata[ii*step+jj*channels]=0;
				   }
				   brklab=1;
				   break;
			   }
			}
		}

		if(1==brklab){
			brklab=0;break;//�˳����
		}
	}
	if(jbi==0 && jbj==0)
	{
	//	jbi=142;
	//	jbj=25;
		
		jbi=0;
		jbj=0;
		printf("\t\t\t���ͼ��ĽǱ�ʧ��,ʹ���趨ֵCjbsb���Ǳ�ʶ��\n");
	}

	cout<<"JB:"<<jbi<<" "<<jbj<<endl;
//----------------------------------------//
//3���ԽǱ�Ϊ�����вü��뻭��
//----------------------------------------//
//    CvSize jbcjsize=cvSize(835,165);           //�Ǳ�ü���Ĵ�С����Ϊ835���أ���Ϊ165����
	CvSize jbcjsize=cvSize(833, 476);
    IplImage* imgjbcj = cvCreateImage(jbcjsize,img->depth,img->nChannels);
    uchar *imgjbcjdata= (uchar *)imgjbcj->imageData;
	int jbcjstep      = imgjbcj->widthStep;	
  	int jbcjchannels  = imgjbcj->nChannels;
	for(i=0;i<476;i++){ 
		for(j=0;j<833;j++){
			imgjbcjdata[i*jbcjstep+j*jbcjchannels]=data[(i+jbi)*step+(j+jbj)*channels];
		}
	}
	//�˴���yss����ע�ͣ�û������ʲô�ô�
	for(i=0;i<476;i=i+2){
		imgjbsbdata[(i+jbi)*step+jbj*channels]=0;
        imgjbsbdata[(i+jbi)*step+(jbj+833)*channels]=0;
	}
	for(j=0;j<833;j=j+2){
        imgjbsbdata[jbi*step+(j+jbj)*channels]=0;
		imgjbsbdata[(jbi+476)*step+(j+jbj)*channels]=0;
	}
	
	return imgjbcj;

}
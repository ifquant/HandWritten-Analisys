/* 	��������outline.c
���ܣ���������������������ͼ�񡣷�����Ӧ����������ֵ
*/
#pragma once
#include <cv.h>  
#include <highgui.h> 
#include <stdlib.h>
#include <stdio.h>
#include "Point.h"

int outlinefeature(IplImage* imglk,int feature[ ][50]){
/*�������*/
    int i,j;
	int height,width,step,channels;
  	uchar *data;

    int feat[50][50]={0};             //����ֵ��ʼ��  
    Point featblk[32];                //�����ͬH�ĺڵ�����
    int featk;                        //�����ͬH�ĺڵ���Ŀ
    int m;                            //for ����ı���

/* ��ȡͼ����Ϣ*/
  	height    = imglk->height;  
  	width     = imglk->width;	
  	step      = imglk->widthStep;	
  	channels  = imglk->nChannels;
  	data      = (uchar *)imglk->imageData;

//��ʼ����������    ���ֵΪ47    ���ǿյ���������1081��
	int outllab[9][9]={\
	{3,37,10,36,2,35,9,34,1},{38,3,21,20,2,19,18,1,33},\
	{11,22,3,10,2,9,1,17,8},{39,23,11,3,2,1,8,16,32},\
	{4,4,4,4,0,0,0,0,0},{40,24,12,5,6,7,15,31,47},\
	{12,25,5,13,6,14,7,30,15},{41,5,26,27,6,28,29,7,46},\
	{5,42,13,43,6,44,14,45,7}};
//    for(i=0;i<9;i++)      //�������
//    {
//      	for(j=0;j<9;j++)
//	        	printf("%d*",outllab[i][j]);
//      	printf("\n");
//    }
for(i=4;i<=width-5;i++)
{                
	for(j=4;j<=height-5;j++)
	{
		if(data[j*step+i*channels]==0)
		{
			//**************H=1

			memset(featblk, 0, sizeof(Point)*32);              //����                
			featk=0;    
			if(data[j*step+(i+1)*channels]==0)                 //�Ҳ��
			{
				featblk[featk].x=i+1;
				featblk[featk].y=j;
                featk++;
			}
			for(m=i+1;m>=i-1;m--)                              //���ŵ�
			{
				if(data[(j-1)*step+m*channels]==0)     
				{
			    	featblk[featk].x=m;
			    	featblk[featk].y=j-1;
                    featk++;
				}
			}
			if(data[j*step+(i-1)*channels]==0)                 //����
			{
				featblk[featk].x=i-1;
				featblk[featk].y=j;
                featk++;
			}
			for(m=i-1;m<=i+1;m++)                              //���ŵ�
			{
				if(data[(j+1)*step+m*channels]==0)     
				{
			    	featblk[featk].x=m;
			    	featblk[featk].y=j+1;
                    featk++;
				}
			}
            //ͳ��������
			//****************************************************
            if(featk>=2)
			{
				for(m=1;m<=featk-1;m++)
				{
					feat[outllab[featblk[m-1].x-i+4][featblk[m-1].y-j+4]][outllab[featblk[m].x-i+4][featblk[m].y-j+4]]++;
				}
			}
            //H=1


			//H=2
	        memset(featblk, 0, sizeof(Point)*32);                 //����                
			featk=0;  
			
			for(m=j+1;m>=j-2;m--)
			{
			    if(data[m*step+(i+2)*channels]==0)                //���ŵ�
				{
		    		featblk[featk].x=i+2;
		      		featblk[featk].y=m;
                    featk++;
				}
			}
			for(m=i+1;m>=i-2;m--)                                  //���ŵ�
			{
				if(data[(j-2)*step+m*channels]==0)     
				{
			    	featblk[featk].x=m;
			    	featblk[featk].y=j-2;
                    featk++;
				}
			}
			for(m=j-1;m<=j+2;m++)                                  //����
			{
			    if(data[m*step+(i-2)*channels]==0)    
				{
	    			featblk[featk].x=i-2;
    				featblk[featk].y=m;
                    featk++;
				}
			}
			for(m=i-1;m<=i+2;m++)                                 //���ŵ�
			{
				if(data[(j+2)*step+m*channels]==0)     
				{
			    	featblk[featk].x=m;
			    	featblk[featk].y=j+2;
                    featk++;
				}
			}
            //ͳ��������
			//****************************************************
            if(featk>=2)
			{
				for(m=1;m<=featk-1;m++)
				{
					feat[outllab[featblk[m-1].x-i+4][featblk[m-1].y-j+4]][outllab[featblk[m].x-i+4][featblk[m].y-j+4]]++;
				}
			}
			//H=2

        	//H=3
	        memset(featblk, 0, sizeof(Point)*32);                 //����                
			featk=0;  
			
			for(m=j+2;m>=j-3;m--)
			{
			    if(data[m*step+(i+3)*channels]==0)                //���ŵ�
				{
		    		featblk[featk].x=i+3;
		      		featblk[featk].y=m;
                    featk++;
				}
			}
			for(m=i+2;m>=i-3;m--)                                  //���ŵ�
			{
				if(data[(j-3)*step+m*channels]==0)     
				{
			    	featblk[featk].x=m;
			    	featblk[featk].y=j-3;
                    featk++;
				}
			}
			for(m=j-2;m<=j+3;m++)                                  //����
			{
			    if(data[m*step+(i-3)*channels]==0)    
				{
	    			featblk[featk].x=i-3;
    				featblk[featk].y=m;
                    featk++;
				}
			}
			for(m=i-2;m<=i+3;m++)                                  //���ŵ�
			{
				if(data[(j+3)*step+m*channels]==0)     
				{
			    	featblk[featk].x=m;
			    	featblk[featk].y=j+3;
                    featk++;
				}
			}
            //ͳ��������
			//******************************************
            if(featk>=2)
			{
				for(m=1;m<=featk-1;m++)
				{
					feat[outllab[featblk[m-1].x-i+4][featblk[m-1].y-j+4]][outllab[featblk[m].x-i+4][featblk[m].y-j+4]]++;
				}
			}
			//H=3

        	//H=4  
	        memset(featblk, 0, sizeof(Point)*32);                 //����                
			featk=0;  
			
			for(m=j+3;m>=j-4;m--)
			{
			    if(data[m*step+(i+4)*channels]==0)                 //���ŵ�
				{
		    		featblk[featk].x=i+4;
		      		featblk[featk].y=m;
                    featk++;
				}
			}
			for(m=i+3;m>=i-4;m--)                                  //���ŵ�
			{
				if(data[(j-4)*step+m*channels]==0)     
				{
			    	featblk[featk].x=m;
			    	featblk[featk].y=j-4;
                    featk++;
				}
			}
			for(m=j-3;m<=j+4;m++)                                  //����
			{
			    if(data[m*step+(i-4)*channels]==0)    
				{
	    			featblk[featk].x=i-4;
    				featblk[featk].y=m;
                    featk++;
				}
			}
			for(m=i-3;m<=i+4;m++)                                 //���ŵ�
			{
				if(data[(j+4)*step+m*channels]==0)     
				{
			    	featblk[featk].x=m;
			    	featblk[featk].y=j+4;
                    featk++;
				}
			}
            //ͳ��������
            if(featk>=2)
			{
				for(m=1;m<=featk-1;m++)
				{
					feat[ outllab[featblk[m-1].x-i+4][featblk[m-1].y-j+4]] [outllab[featblk[m].x-i+4][featblk[m].y-j+4] ]++;
				}
			}
			//H=4***********************

		}
           		
	}
}

	//****ע����������ֵΪfeat(x,y)+feat(y,x)������feat(x,y)�У�x<y
	for(i=1;i<50;i++)
		for(j=0;j<i;j++)
		{
			feat[j][i]=feat[i][j]+feat[j][i];
            feat[i][j]=0;
		}

	memcpy(feature,feat,2500*4);        //int���ĸ��ֽ�

	return 0;


}
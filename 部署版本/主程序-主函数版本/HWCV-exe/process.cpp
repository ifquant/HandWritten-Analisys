/*
ʵ���ļ���process.cpp ͼ������̵�ʵ���ļ�
*/
#include "process.h"

/*
���ܣ�����ͼ���ļ������ж�ֵ��

@���� img iplimageͼ���ļ�
@���� bithro ��ֵ����ֵ
@����ֵ �����ص���Ŀ�����ã�
*/
int*  binary(IplImage*  img, int g_bi_threshold)
{
	int height, width, step, channels;
	uchar *data;
	int i, j;
	static int black[1000];   //C���Բ��ᳫ����һ���ֲ������ĵ�ַ����Ĺ��ܣ���������붨��ľֲ��������羲̬������
	/* ��ȡͼ����Ϣ*/
	height = img->height;
	width = img->width;
	step = img->widthStep;
	channels = img->nChannels;
	data = (uchar *)img->imageData;

	/*��ֵ������ͳ�ƺ����صĸ���*/
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)//��ͼ��ÿ������ж�ֵ��,ԭֵΪ128
			data[i*step + j*channels] = (data[i*step + j*channels]>g_bi_threshold) ? 255 : 0;
	}

	/*����ÿһ�еĺ����ظ���*/
	int tempBlackPixel = 0;

	memset(black, 0, 1000);            //##��ʼ���ڴ棬������������black����
	for (i = height - 1; i>0; i--)
	{
		for (int j = 0; j<width; j++)
		{
			if (data[i*step + j*channels] == 0)        //�����ɫ��������
				tempBlackPixel += 1;
		}
		black[height - i] = tempBlackPixel;   //black��¼��ɫ������
		tempBlackPixel = 0;
	}
	//��ֵ������ͳ�ƺ����صĸ���**********
	return black;
}



/* 	
���ܣ�����ͼ���ļ�����ͼ����вü�

@���� img iplimageͼ���ļ�
@���� img �ü����iplimageͼ���ļ�
@jbwhite
@jbblack
@����ֵ ���زü����ͼ��
*/
IplImage* Cjbsb(IplImage* img, IplImage* imgjbsb, int jbwhite, int jbblack)
{
	/*�������*/
	int i, j, jbi = 0, jbj = 0;
	int height, width, step, channels;
	uchar *data;
	int brklab = 0;
	/* ��ȡͼ����Ϣ*/
	height = img->height;
	width = img->width;
	step = img->widthStep;
	channels = img->nChannels;
	data = (uchar *)img->imageData;

	//    IplImage* imgjbsb = cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
	cvCopy(img, imgjbsb, NULL);
	uchar *imgjbsbdata = (uchar *)imgjbsb->imageData;

	//�ԽǱ�Ϊ�����вü��뻭��
	CvSize jbcjsize = cvSize(835, 165);           //�Ǳ�ü���Ĵ�С����Ϊ835���أ���Ϊ165����
	IplImage* imgjbcj = cvCreateImage(jbcjsize, img->depth, img->nChannels);
	uchar *imgjbcjdata = (uchar *)imgjbcj->imageData;
	int jbcjstep = imgjbcj->widthStep;
	int jbcjchannels = imgjbcj->nChannels;
	for (i = 0; i<165; i++)
		for (j = 0; j<835; j++)
			imgjbcjdata[i*jbcjstep + j*jbcjchannels] = data[(i + jbi)*step + (j + jbj)*channels];
	for (i = 0; i<165; i = i + 2)
	{
		imgjbsbdata[(i + jbi)*step + jbj*channels] = 0;
		imgjbsbdata[(i + jbi)*step + (jbj + 835)*channels] = 0;
	}
	for (j = 0; j<835; j = j + 2)
	{
		imgjbsbdata[jbi*step + (j + jbj)*channels] = 0;
		imgjbsbdata[(jbi + 165)*step + (j + jbj)*channels] = 0;
	}

	return imgjbcj;
}


/*
���ܣ�����ͼ�������

@���� imgbj �ʼ����ֵ�ͼ��
@����ֵ ����õ�������ͼ��
*/
IplImage* outline(IplImage* imgbj)
{
	/*�������*/
	int i, j;
	int height, width, step, channels;
	uchar *data;

	/*�����µ�ͼ��*/
	IplImage* imglk = cvCreateImage(cvGetSize(imgbj), imgbj->depth, imgbj->nChannels);

	/* ��ȡͼ����Ϣ*/
	height = imgbj->height;
	width = imgbj->width;
	step = imgbj->widthStep;
	channels = imgbj->nChannels;
	data = (uchar *)imgbj->imageData;

	//	printf("--outline--");
	for (j = 0; j<height; j++){
		for (i = 0; i<width; i++){
			imglk->imageData[j*step + i*channels] = 255;
		}
		for (i = 0; i<width - 1; i++){
			if (data[j*step + (i + 1)*channels] - data[j*step + i*channels] == 255)             //�����Ҳ��
				imglk->imageData[j*step + i*channels] = 0;
			else if (data[j*step + i*channels] - data[j*step + (i + 1)*channels] == 255)        //��������
				imglk->imageData[j*step + (i + 1)*channels] = 0;
		}
	}

	for (i = 0; i<width; i++){
		for (j = 0; j<height - 1; j++){
			if (data[j*step + i*channels] - data[(j + 1)*step + i*channels] == 255)             //�����²��
				imglk->imageData[(j + 1)*step + i*channels] = 0;
			else if (data[(j + 1)*step + i*channels] - data[j*step + i*channels] == 255)        //�����ϲ��
				imglk->imageData[j*step + i*channels] = 0;
		}
	}
	return imglk;
}


/*
���ܣ�����ͼ�����������ͼ������ͼ�������ֵ
@���� imglk �����ͼ������ͼ
@���� feature �õ���ͼ������
@����ֵ �ɹ�1ʧ��0
*/
int outlinefeature(IplImage* imglk, int feature[][50])
{
	//�������
	int i, j;
	int height, width, step, channels;
	uchar *data;

	int feat[50][50] = { 0 };             //����ֵ��ʼ��  
	Point featblk[32];                //�����ͬH�ĺڵ�����
	int featk;                        //�����ͬH�ĺڵ���Ŀ
	int m;                            //for ����ı���
	//	printf("--outlinefeature--");
	// ��ȡͼ����Ϣ
	height = imglk->height;
	width = imglk->width;
	step = imglk->widthStep;
	channels = imglk->nChannels;
	data = (uchar *)imglk->imageData;

	//��ʼ����������    ���ֵΪ47    ���ǿյ���������1081��
	int outllab[9][9] = { \
	{3, 37, 10, 36, 2, 35, 9, 34, 1}, { 38, 3, 21, 20, 2, 19, 18, 1, 33 }, \
	{11, 22, 3, 10, 2, 9, 1, 17, 8}, { 39, 23, 11, 3, 2, 1, 8, 16, 32 }, \
	{4, 4, 4, 4, 0, 0, 0, 0, 0}, { 40, 24, 12, 5, 6, 7, 15, 31, 47 }, \
	{12, 25, 5, 13, 6, 14, 7, 30, 15}, { 41, 5, 26, 27, 6, 28, 29, 7, 46 }, \
	{5, 42, 13, 43, 6, 44, 14, 45, 7} };


	for (i = 4; i <= width - 5; i++){
		for (j = 4; j <= height - 5; j++){
			if (data[j*step + i*channels] == 0){
				//**************H=1

				memset(featblk, 0, sizeof(Point) * 32);              //����                
				featk = 0;
				if (data[j*step + (i + 1)*channels] == 0){                 //�Ҳ��
					featblk[featk].x = i + 1;
					featblk[featk].y = j;
					featk++;
				}
				for (m = i + 1; m >= i - 1; m--){                              //���ŵ�
					if (data[(j - 1)*step + m*channels] == 0) {
						featblk[featk].x = m;
						featblk[featk].y = j - 1;
						featk++;
					}
				}
				if (data[j*step + (i - 1)*channels] == 0){                 //����
					featblk[featk].x = i - 1;
					featblk[featk].y = j;
					featk++;
				}
				for (m = i - 1; m <= i + 1; m++) {                             //���ŵ�
					if (data[(j + 1)*step + m*channels] == 0){
						featblk[featk].x = m;
						featblk[featk].y = j + 1;
						featk++;
					}
				}
				//ͳ��������
				if (featk >= 2){
					for (m = 1; m <= featk - 1; m++){
						feat[outllab[featblk[m - 1].x - i + 4][featblk[m - 1].y - j + 4]][outllab[featblk[m].x - i + 4][featblk[m].y - j + 4]]++;
					}
				}
				//H=1*******************


				//*********************H=2
				memset(featblk, 0, sizeof(Point) * 32);                 //����                
				featk = 0;

				for (m = j + 1; m >= j - 2; m--){
					if (data[m*step + (i + 2)*channels] == 0){                //���ŵ�
						featblk[featk].x = i + 2;
						featblk[featk].y = m;
						featk++;
					}
				}
				for (m = i + 1; m >= i - 2; m--){                                  //���ŵ�
					if (data[(j - 2)*step + m*channels] == 0){
						featblk[featk].x = m;
						featblk[featk].y = j - 2;
						featk++;
					}
				}
				for (m = j - 1; m <= j + 2; m++){                                  //����
					if (data[m*step + (i - 2)*channels] == 0){
						featblk[featk].x = i - 2;
						featblk[featk].y = m;
						featk++;
					}
				}
				for (m = i - 1; m <= i + 2; m++){                                 //���ŵ�
					if (data[(j + 2)*step + m*channels] == 0){
						featblk[featk].x = m;
						featblk[featk].y = j + 2;
						featk++;
					}
				}
				//ͳ��������
				if (featk >= 2){
					for (m = 1; m <= featk - 1; m++){
						feat[outllab[featblk[m - 1].x - i + 4][featblk[m - 1].y - j + 4]][outllab[featblk[m].x - i + 4][featblk[m].y - j + 4]]++;
					}
				}
				//H=2********************

				//*********************H=3
				memset(featblk, 0, sizeof(Point) * 32);                 //����                
				featk = 0;

				for (m = j + 2; m >= j - 3; m--){
					if (data[m*step + (i + 3)*channels] == 0){                //���ŵ�
						featblk[featk].x = i + 3;
						featblk[featk].y = m;
						featk++;
					}
				}
				for (m = i + 2; m >= i - 3; m--){                                  //���ŵ�
					if (data[(j - 3)*step + m*channels] == 0){
						featblk[featk].x = m;
						featblk[featk].y = j - 3;
						featk++;
					}
				}
				for (m = j - 2; m <= j + 3; m++){                                  //����
					if (data[m*step + (i - 3)*channels] == 0){
						featblk[featk].x = i - 3;
						featblk[featk].y = m;
						featk++;
					}
				}
				for (m = i - 2; m <= i + 3; m++){                                  //���ŵ�
					if (data[(j + 3)*step + m*channels] == 0){
						featblk[featk].x = m;
						featblk[featk].y = j + 3;
						featk++;
					}
				}
				//ͳ��������
				if (featk >= 2){
					for (m = 1; m <= featk - 1; m++){
						feat[outllab[featblk[m - 1].x - i + 4][featblk[m - 1].y - j + 4]][outllab[featblk[m].x - i + 4][featblk[m].y - j + 4]]++;
					}
				}
				//H=3********************

				//*********************H=4  
				memset(featblk, 0, sizeof(Point) * 32);                 //����                
				featk = 0;

				for (m = j + 3; m >= j - 4; m--){
					if (data[m*step + (i + 4)*channels] == 0){                 //���ŵ�
						featblk[featk].x = i + 4;
						featblk[featk].y = m;
						featk++;
					}
				}
				for (m = i + 3; m >= i - 4; m--) {                                 //���ŵ�
					if (data[(j - 4)*step + m*channels] == 0){
						featblk[featk].x = m;
						featblk[featk].y = j - 4;
						featk++;
					}
				}
				for (m = j - 3; m <= j + 4; m++){                                  //����
					if (data[m*step + (i - 4)*channels] == 0){
						featblk[featk].x = i - 4;
						featblk[featk].y = m;
						featk++;
					}
				}
				for (m = i - 3; m <= i + 4; m++){                                 //���ŵ�
					if (data[(j + 4)*step + m*channels] == 0){
						featblk[featk].x = m;
						featblk[featk].y = j + 4;
						featk++;
					}
				}
				//ͳ��������
				if (featk >= 2){
					for (m = 1; m <= featk - 1; m++){
						feat[outllab[featblk[m - 1].x - i + 4][featblk[m - 1].y - j + 4]][outllab[featblk[m].x - i + 4][featblk[m].y - j + 4]]++;
					}
				}
				//H=4***********************
			}// if    		
		}  //for j
	}  //for i

	//****ע����������ֵΪfeat(x,y)+feat(y,x)������feat(x,y)�У�x<y
	for (i = 1; i<50; i++)
		for (j = 0; j<i; j++){
		feat[j][i] = feat[i][j] + feat[j][i];
		feat[i][j] = 0;
		}
	memcpy(feature, feat, 2500 * 4);        //int���ĸ��ֽ�
	//	printf("��������ֵ�������\n");
	return 0;
}


/*
���ܣ��Ե���ͼ��Ĵ������յõ�һ������ֵ�������������ͼ��֮��Ŀ�������

@���� path ͼ��������ַ
@���� feature ͼ�������ֵ
@����ֵ ������ͼ��
*/
IplImage* singlefeature(char* path, int feature[][50])
{
	//�������
	        //ԭͼ
	IplImage* imglk = 0;        //����ͼ
	IplImage* imggj = 0;        //�Ǽ�ͼ
	IplImage* imgjbsb = 0;      //�Ǳ�ʶ��ͼ
	IplImage* imgbj = 0;        //ֻ��ȡ�ʼǲ��ֵ�ͼ��
	IplImage* imgbjhf = 0;      //Ϊ���������Ϸ���
	IplImage* imgwzbj = 0;      //Ϊ�����������Ƿ�Ϊ���֣����ֱ�ǣ�

	int height, width, step, channels;
	uchar *data;

	int i, j;                //���ڷ���ͼ��ÿ�к����صĸ���
	//int feature[50][50]={0};    //����ֵ��ʼ��

	IplImage* img  = cvLoadImage(path, 0);

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
	binary(imgbig, g_bi_threshold);
	//SaveLog("singlefeature_binary\n", "D:\\HWCV\\numtxt.txt", "a");



	/*�ü�ʶ��*/
	int jbwhite = 5, jbblack = 4;
	imgjbsb = cvCreateImage(cvGetSize(imgbig), imgbig->depth, imgbig->nChannels);
	imgbj = Cjbsb(imgbig, imgjbsb, jbwhite, jbblack);                              //�������ֵıʼ�����


	/*����Ǽ�ͼ*/
	imggj = cvCreateImage(cvGetSize(imgbj), imgbj->depth, imgbj->nChannels);   //����
	cvCopy(imgbj, imggj, NULL);
	uchar *gjdata = (uchar *)imggj->imageData;

	beforethin(gjdata, gjdata, imggj->width, imggj->height);

	/*�ʼ�ͼ����ɫ��Χת�����Խ���ϸ��*/
	for (j = 0; j<imggj->height; j++)//ȡֵ��Χת��0--1  
	{ 
		for (i = 0; i<imggj->width; i++)
		{
			if (gjdata[j*imggj->widthStep + i] == 255)
				gjdata[j*imggj->widthStep + i] = 1;
		}
	}

	/*ϸ��*/
	ThinnerRosenfeld(imggj->imageData, imggj->height, imggj->width);

	/*�ʼ�ͼ����ɫ��Χת��������ˮƽ*/
	for (j = 0; j<imggj->height; j++)//ȡֵ��Χת��0--255,��ת����
	{
		for (i = 0; i<imggj->width; i++)
		{
			if (gjdata[j*imggj->widthStep + i] == 1)
				gjdata[j*imggj->widthStep + i] = 0;
			else
				gjdata[j*imggj->widthStep + i] = 255;
		}
	}

	/*����Ǽ�������*/
	outlinefeature(imggj, feature);   //����ֵռ48*48�����������Σ�feature���÷���

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



/*
���ܣ�ϸ��֮ǰ��ͼ����ɫ��������ɫ��Χת����0-1

@���� ip ͼ��ľ��
@���� jp
@���� lx ͼ����
@���� ly ͼ��߶�
@����ֵ ��
*/
void beforethin(unsigned char *ip, unsigned char *jp, unsigned long lx, unsigned long ly)
{
	unsigned long i, j;

	for (i = 0; i<ly; i++){
		for (j = 0; j<lx; j++){
			//����Ҫ��ǰ���ǰ׵㻹�Ǻڵ���������ԸĶ�
			//���ǰ���ǰ׵㣬������������֮������
			//jp[i*lx+j]=ip[i*lx+j];
			/*  jp[i*lx+j]=255;*/
			if (ip[i*lx + j]>0)
				jp[i*lx + j] = 0;
			else
				jp[i*lx + j] = 255;
		}
	}
}


/*���ܣ�ϸ���㷨 ��Rosenfeldϸ���㷨��������ɶԱʼ�ͼ��Ĺɼ���ȡ

@���� image ����ͼ���һά����
@���� lx ͼ����
@���� ly ͼ��߶�
@����ֵ �޷���ֵ
*/
void ThinnerRosenfeld(void *image, unsigned long lx, unsigned long ly)
{
	char *f, *g;
	char n[10];
	char a[5] = { 0, -1, 1, 0, 0 };
	char b[5] = { 0, 0, 0, 1, -1 };
	char nrnd, cond, n48, n26, n24, n46, n68, n82, n123, n345, n567, n781;
	short k, shori;
	unsigned long i, j;
	long ii, jj, kk, kk1, kk2, kk3, size;

	//	printf("--Thinner_Rosenfeld--");
	size = (long)lx * (long)ly;

	g = (char *)malloc(size);
	if (g == NULL){
		printf("error in alocating mmeory!\n");
		return;
	}

	f = (char *)image;
	for (kk = 0l; kk<size; kk++){
		g[kk] = f[kk];
	}

	do{
		shori = 0;
		for (k = 1; k <= 4; k++){
			for (i = 1; i<lx - 1; i++){
				ii = i + a[k];

				for (j = 1; j<ly - 1; j++){
					kk = i*ly + j;

					if (!f[kk])
						continue;

					jj = j + b[k];
					kk1 = ii*ly + jj;

					if (f[kk1])
						continue;

					kk1 = kk - ly - 1;
					kk2 = kk1 + 1;
					kk3 = kk2 + 1;
					n[3] = f[kk1];
					n[2] = f[kk2];
					n[1] = f[kk3];
					kk1 = kk - 1;
					kk3 = kk + 1;
					n[4] = f[kk1];
					n[8] = f[kk3];
					kk1 = kk + ly - 1;
					kk2 = kk1 + 1;
					kk3 = kk2 + 1;
					n[5] = f[kk1];
					n[6] = f[kk2];
					n[7] = f[kk3];

					nrnd = n[1] + n[2] + n[3] + n[4]
						+ n[5] + n[6] + n[7] + n[8];
					if (nrnd <= 1)
						continue;

					cond = 0;
					n48 = n[4] + n[8];
					n26 = n[2] + n[6];
					n24 = n[2] + n[4];
					n46 = n[4] + n[6];
					n68 = n[6] + n[8];
					n82 = n[8] + n[2];
					n123 = n[1] + n[2] + n[3];
					n345 = n[3] + n[4] + n[5];
					n567 = n[5] + n[6] + n[7];
					n781 = n[7] + n[8] + n[1];

					if (n[2] == 1 && n48 == 0 && n567>0){
						if (!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}
					if (n[6] == 1 && n48 == 0 && n123>0)	{
						if (!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}
					if (n[8] == 1 && n26 == 0 && n345>0){
						if (!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}
					if (n[4] == 1 && n26 == 0 && n781>0)	{
						if (!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}
					if (n[5] == 1 && n46 == 0){
						if (!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}
					if (n[7] == 1 && n68 == 0){
						if (!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}
					if (n[1] == 1 && n82 == 0){
						if (!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}
					if (n[3] == 1 && n24 == 0){
						if (!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}
					cond = 1;
					if (!cond)
						continue;
					g[kk] = 0;
					shori = 1;
				}
			}

			for (i = 0; i<lx; i++){
				for (j = 0; j<ly; j++){
					kk = i*ly + j;
					f[kk] = g[kk];
				}
			}
		}
	} while (shori);
	free(g);
}

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

int read_scanf(const string &filename,const int &cols,vector<double *> &_vector){
// ���ܣ���filename �е����ݣ���cols�У���ȡ��_vector�У�_vector����Ϊ��ά����
	FILE *fp=fopen(filename.c_str(),"r");//�򿪲���ȡ�ļ�
	bool flag=true;
	int i=0;
	
//	printf("--read_scanf--");
	if(!fp){ cout<<"File open error!\n"; return 0; }
	while(flag){
		double *point=new double[cols];
		for(i=0;i<cols;i++){ //��ȡ���ݣ�����_vector[cols]��
			if(EOF==fscanf(fp,"%lf",&point[i])) { 
				flag=false;break; 
			}
			if(EOF==fgetc(fp)) { 
				flag=false;i++;break;
			}
		}
		if(cols==i) 
			_vector.push_back(point);
	}
	fclose(fp);
	return 1;
}
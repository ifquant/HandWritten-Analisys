/* 	��������getFiles.c
���ܣ�����һ���ļ����µ������ļ���
*/
#include<io.h>
#include <stdio.h>
#include<vector>
#include<iostream>
#include <string.h>
#include <string>
using namespace std;

int searchDir( char *path, vector<string> &dir)
{
	using namespace std;
	struct _finddata_t fa;//�����ҵ��Ľṹ��
    long handle;
    int flag=0;
	char temp[100]={0};
	string path_temp=path;
//	path_temp=path_temp.substr(0,path_temp.length()-1);

    if((handle = _findfirst(strcat(path,"*"),&fa)) == -1L)//�������Ŀ¼�Ļ�
		return 0;
       
    do//��Ŀ¼����ִ��ѭ��
    {
        if( fa.attrib == _A_SUBDIR && ~strcmp(fa.name,".")&& ~strcmp(fa.name,".."))
		{
			strcat( temp, path_temp.c_str());
			strcat( temp, fa.name);

			if(flag++) 
				dir.push_back(temp);
			else;

			memset(temp,0,100);
		}
    }while(_findnext(handle,&fa) == 0); /* �ɹ��ҵ�ʱ����0*/ 
    
    _findclose(handle);
	
    return 0;	

}
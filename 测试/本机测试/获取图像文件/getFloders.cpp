/* 	��������getFolders.c
���ܣ�����һ���ļ����µ������ļ��е�����
*/
#include<io.h>
#include <stdio.h>
#include<vector>
#include<iostream>
using namespace std;
#include <string.h>

int getFolders(string path, vector<string>& files )  
{   
	using namespace std;//�����������ռ�
    //�ļ����  
    long   hFile   =   0;  
    //�ļ���Ϣ  
    struct _finddata_t fileinfo;  
    string p; 
	
    int i=0;	 
    if((hFile = _findfirst(p.assign(path).append("/*").c_str(),&fileinfo)) !=  -1)  
    {  
        do  
        {  
			if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)		
			{
                files.push_back(p.assign(path).append("/").append(fileinfo.name) );  
				printf("�ļ��У�%s\n",files[i].c_str());
				i++;
			}

        }while(_findnext(hFile, &fileinfo)  == 0);  

        _findclose(hFile);  
    }  
    return 0;	
	
}  
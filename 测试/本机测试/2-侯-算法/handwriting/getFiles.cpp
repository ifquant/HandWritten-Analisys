/* 	��������getFiles.c
���ܣ�����һ���ļ����µ������ļ���
*/
#pragma once
#include<io.h>
#include <stdio.h>
#include<vector>
#include<iostream>
using namespace std;
#include <string.h>

void getFiles(string path, vector<string>& files ){  
	using namespace std;//�����������ռ�
    //�ļ����  
    long   hFile   =   0;  
    //�ļ���Ϣ  
    struct _finddata_t fileinfo;  
    string p;  
    if((hFile = _findfirst(p.assign(path).append("/*").c_str(),&fileinfo)) !=  -1)
	{  
        do
		{  
            //�����Ŀ¼,����֮  
             
            if((fileinfo.attrib &  _A_SUBDIR))
			{  
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)  
                    getFiles( p.assign(path).append("/").append(fileinfo.name), files );  
            } //�������,�����б�  
            else
			{  
                files.push_back(p.assign(path).append("/").append(fileinfo.name) );  
//				cout<<fileinfo.name<<endl;
            }  
        }while(_findnext(hFile, &fileinfo)  == 0);  

        _findclose(hFile);  
    }  
}  
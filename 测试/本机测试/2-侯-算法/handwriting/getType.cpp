/*��������getType.c
���ܣ�����ͼ���ļ������õ�ͼ������
*/
#pragma once
#include <stdio.h>
#include <string.h>
char * getType(char fileName[], char type[])
{
	int i=strlen(fileName)-1, j;
	char ch;

	for(type[0]='\0';i>=0;i--)
	{
		if(fileName[i] == '.')
		{// �����ļ����ͷָ��� 
			for(j=i; fileName[j]!='\0'; j++)
			{
				ch = fileName[j];
				type[j-i] = ('A'<=ch && ch<='Z') ? (ch+'a'-'A'): ch;
			} 

			type[j-i] = '\0'; 
			break;
		}
		else if(fileName[i] == '/' || fileName[i]=='\\') break;// ����Ŀ¼�ָ�����˳� 
	}
	return type;
}
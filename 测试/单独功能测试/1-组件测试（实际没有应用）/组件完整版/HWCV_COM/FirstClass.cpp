// FirstClass.cpp : CFirstClass ��ʵ��

#pragma once
#include "stdafx.h"
#include "FirstClass.h"
#include <windows.h>
#include <iostream>
#include <dos.h>
#include <stdio.h>
#include <comdef.h>


// CFirstClass


int _Check(char *fpname1, char *dest);

STDMETHODIMP CFirstClass::Check(BSTR stuNum, BSTR* result)
{
	// TODO:  �ڴ����ʵ�ִ���
	/*ת��num��ʽ*/
	_bstr_t num = stuNum;
	char* num_c = num;

	// TODO:  �ڴ����ʵ�ִ���
	//������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ����
	char *fo = "D:\\HWCV_COM_log.txt";
	char rec[200] = "���Ե���com�˿�!\n";
	strcat(rec, num_c);
	strcat(rec, "\n");
	FILE *fpzz3 = NULL;//��Ҫע��
	fpzz3 = fopen(fo, "a");  //�����ļ�
	if (NULL == fpzz3) return NULL;//Ҫ���ش������
	fprintf(fpzz3, rec);
	fclose(fpzz3);
	fpzz3 = NULL;//��Ҫָ��գ������ָ��ԭ���ļ���ַ
	//������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ

	/* ��ʼ����HWCV.dll */
	char* stu_p = num;
	char* out = new char[100];

	///*��Ҫ��HWCV.dll�ŵ�ͬͬһ��Ŀ¼����*/
	//HINSTANCE   hDllInst = LoadLibrary(L"HWCV.dll");
	//if (hDllInst)
	//{
	//	/*����ʵ�����Ľӿ�*/
	//	typedef char*(WINAPI *HWCV)(char*, char*);
	//	HWCV   hwcv = NULL;   //hwcv �������� 

	//	/*��ȡ�߳�*/
	//	hwcv = (HWCV)GetProcAddress(hDllInst, "HWCV");

	//	if (hwcv)
	//	{
	//		char* resu = hwcv(stu_p, out);
	//		*result = (_bstr_t)resu;
	//	}

	//	FreeLibrary(hDllInst);
	//}
	//

	_Check(stu_p, out);
	return S_OK;
}

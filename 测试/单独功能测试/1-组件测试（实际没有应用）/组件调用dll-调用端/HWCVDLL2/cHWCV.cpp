// cHWCV.cpp : CcHWCV ��ʵ��

#include "stdafx.h"
#include "cHWCV.h"


// CcHWCV



STDMETHODIMP CcHWCV::aspHWCV(BSTR filepath, BSTR* _arg2)
{
	// TODO:  �ڴ����ʵ�ִ���
	//������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ����
	char *fo = "H:\\HWCVDLL2.txt";
	char rec[200] = "���Ե���com�˿�!\n";
	//char* filepath_c = (_bstr_t)filepath;
	strcat(rec, (char*)filepath);
	strcat(rec, "\n");
	FILE *fpzz3 = NULL;//��Ҫע��
	fpzz3 = fopen(fo, "w");  //�����ļ�
	if (NULL == fpzz3) return NULL;//Ҫ���ش������
	fprintf(fpzz3, rec);
	fclose(fpzz3);
	fpzz3 = NULL;//��Ҫָ��գ������ָ��ԭ���ļ���ַ
	//������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ������Ϣ
	*_arg2 = L"success";
	return S_OK;
}

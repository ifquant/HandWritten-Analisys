#include <windows.h>
#include <iostream>
#include <dos.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <string.h>
#include <io.h>

using namespace std;


/*ʱ���ȡ����u*/
#define LOGFILE "D:\\HWCV\\memstatus.txt"	//��־�洢λ��

extern time_t ltime;
extern char *srcTime;
extern char timeNow[22];
extern char msg[100];

/*���ܣ�д����־
@���� str д������
@����ֵ �̶�
*/
int WriteToLog(char* str);


/**
����:��ȡ�����ص�ǰʱ��
 */
char* GetTime();


/*���ܣ���鵱ǰľ�������ļ������У���ȡ�ļ�������ɾ�����ļ�
@���� path ����ļ�λ��
@���� files ��ȡ�����ļ�����
@����ֵ ���ؼ�⵽�ı�������
*/
int CheckFile(char* path, vector<string>& files);



#include <string>
#include <windows.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <dos.h>
#include <time.h>
#pragma comment(lib, "Advapi32")

//#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )//û�н�������

using namespace std;
/*����ȫ�ֱ���*/
#define SLEEP_TIME	1000						//5000����ˢ��һ��


/*ʱ���ȡ����u*/
time_t ltime;
char *srcTime=NULL;
char timeNow[22]={0};
char msg[100]={0};
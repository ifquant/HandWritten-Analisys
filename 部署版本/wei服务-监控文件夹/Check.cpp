#include "Check.h"

char* GetTime();

/*���ܣ���鵱ǰľ�������ļ������У���ȡ�ļ�������ɾ�����ļ�
@���� path ����ļ�λ��
@����ֵ ���ؼ�⵽�ı�������
*/
int CheckFile(char* path, vector<string>& files)
{
	using namespace std;//�����������ռ�
	//�ļ����  
	long   hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,ֱ�ӷ���
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
			}
			else //�������,�����б� 
			{
				//files.push_back(p.assign(path).append("/").append(fileinfo.name));
				files.push_back(fileinfo.name);
				remove(p.assign(path).append("\\").append(fileinfo.name).c_str());
			}
		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}

	return 0;
}


/**
���ܣ�к���ļ���־
  */
int WriteToLog(char* str)
{
	FILE* log;
	log = fopen(LOGFILE, "a+");
	if (log == NULL) return -1;
	fprintf(log, "%s ", str);
	fclose(log);
	return 0;
}

/**
��ȡ�����ص�ǰʱ��
 */
char* GetTime()
{
	time( &ltime );
	srcTime = ctime( &ltime );
	strncpy(timeNow, srcTime, strlen(srcTime)-1);  //����������
	timeNow[strlen(srcTime)-1] = '\0';   //�ӽ�����'\0'

	return timeNow;
}
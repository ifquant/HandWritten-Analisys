#include <iostream>

using namespace std;
/**
����ѧ����Ϣ�����ļ�·���������ļ���ȡ

@���� date ��������
@���� subject ���Կ�Ŀ
@���� stuNum ����
@����ֵ �������ɵ��ļ�·��
*/
string CrPath(string date, string subject, string stuNum)
{
	string temp = "Z:/"; temp += date; temp += "/";
	temp += subject.substr(0, 4); temp += "/";
	temp += stuNum; temp += ".jpg";

	return temp;
}

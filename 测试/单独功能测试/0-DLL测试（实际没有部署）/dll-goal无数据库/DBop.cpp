#import "C:\Program Files\Common Files\System\ado\msado15.dll"\
no_namespace rename("EOF","EndOfFile")
#include <vector> 
#include <string> 
#include <iostream> 
#include <windows.h> 
#include <iomanip> 
#include <stdio.h> 

using namespace std;


string g_db_hostName = "192.168.200.97";		/*ȫ�ֱ��� ������ip������*/
string g_db_dBName = "purple";			/*ȫ�ֱ��� ������ODBC����Դ*/
string g_db_userName = "BJSH";		/*ȫ�ֱ��� �������û���*/
string g_db_password = "bjshadmin";		/*ȫ�ֱ��� ����������*/

/*��������*/
//string g_db_hostName = "localhost";		/*ȫ�ֱ��� ������ip������*/
//string g_db_dBName = "yanshuaishuai";			/*ȫ�ֱ��� ������ODBC����Դ*/
//string g_db_userName = "yannsy";		/*ȫ�ֱ��� �������û���*/
//string g_db_password = "123456";		/*ȫ�ֱ��� ����������*/

string g_db_qurry_start = "200906";		/*ȫ�ֱ��� ���ݿ��ѯ_��ʼ����*/
string g_db_qurry_end = "201610";		/*ȫ�ֱ��� ���ݿ��ѯ_��������*/
string g_db_qurry_zone = "0";		/*ȫ�ֱ��� ���ݿ��ѯ_�ض�����*/
string g_db_qurry_stu_num = "0";	/*ȫ�ֱ��� ���ݿ��ѯ_�ض�����*/
bool g_db_qurry_all = true;			/*ȫ�ֱ��� ���ݿ��ѯ_��ѯȫ�����*/

_ConnectionPtr p_conn;		/*ȫ�ֱ��� ���Ӷ���*/
_RecordsetPtr p_recordset;	/*ȫ�ֱ��� ��¼������*/
_CommandPtr p_cmd;			/*ȫ�ֱ��� ����������*/
string	str_conn;			/*ȫ�ֱ��� �����ַ�������*/


/**
�����ܣ�	����string���stu���洢ѧ�š������������д��˵Ŀ�����Ϣ,���ֱ�洢�ڲ�ͬ�ı�����

@���� stuNum ѧ��
@���� date<vector>	����ʱ��
@���� subject<vector> ���Կ�Ŀ
@���� stuNum<vector> ����
@����ֵ �ɹ�1 ʧ��0
*/
int DbImg(string stuNum, vector<string>& dateVec, vector<string>& subjectVec, vector<string>& stuNum2)//��ѰͼƬ
{
	/*�ַ�ת��������ʹ��*/
	string  userName(g_db_userName.c_str());
	string  password(g_db_password.c_str());
	string  hostName(g_db_hostName.c_str());
	string  dBName(g_db_dBName.c_str());

	//�����ѯ���				�¾�ע����sql��䣬��Ҫ�������������
	/*select KS_ZKZ, KSSJ, TJ_KC_DM from ZK.T_BYSQ_KS_KC WHERE KSSJ between '200907' and '201510' and KS_ZKZ = 010207203867*/
	/*string  sql = "select KS_ZKZ2, KSSJ, TJ_KC_DM from ZK.T_BYSQ_KS_KC WHERE KSSJ between '200907' and '201504' AND KS_ZKZ = ";*/
	string sql = "select KS_ZKZ2, KSSJ, TJ_KC_DM from ZK.T_BYSQ_KS_KC WHERE KSSJ between ";
	sql += g_db_qurry_start;
	sql += " and ";
	sql += g_db_qurry_end;
	sql += "AND KS_ZKZ =";
	sql += stuNum.c_str();

	_bstr_t _vstr_sql(sql.c_str());/* ת��stringΪ_variant_t */
	::CoInitialize(NULL);//��ʼ��com���

	/*������������*/
	try{
		p_conn.CreateInstance("ADODB.Connection");//��������
		p_recordset.CreateInstance("ADODB.Recordset");//���������,Ҳ����ʵ����
		p_cmd.CreateInstance("ADODB.Command");

		p_conn->CursorLocation = adUseClient; //�洢����ͬʱ���ؼ�¼���ͷ���ֵ
		p_conn->Open(_bstr_t(str_conn.c_str()), _bstr_t(userName.c_str()), _bstr_t(password.c_str()), adConnectUnspecified);
		p_cmd.CreateInstance("ADODB.Command");
		p_cmd->ActiveConnection = p_conn;

		HRESULT hr = p_recordset->Open(_bstr_t(_vstr_sql),//ִ��sq��䣬��ѯһ��ѧ�������п�����Ϣ
			p_conn.GetInterfacePtr(),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);

		//����������������vector������
		if (p_recordset->RecordCount < 1)//�����Ϊ��
		{
			return 1;//û����Ϣ��ֱ�����������
		}
		do{ //����������������vector������
			dateVec.push_back((string)(_bstr_t)(p_recordset->Fields->GetItem(_variant_t("KSSJ"))->GetValue()));
			subjectVec.push_back((string)(_bstr_t)(p_recordset->Fields->GetItem(_variant_t("TJ_KC_DM"))->GetValue()));
			stuNum2.push_back((string)(_bstr_t)(p_recordset->Fields->GetItem(_variant_t("KS_ZKZ2"))->GetValue()));
			p_recordset->MoveNext();
		} while (!p_recordset->EndOfFile);
	}
	catch (_com_error e){ return 0; }

	/*�رղ�ѯ*/
	try	{ ::CoUninitialize(); }
	catch (_com_error e){ /*cout << "qurry:" << e.ErrorInfo() << endl;*/ }

	return 1;
}



/**
�����ܣ�	����ѧ�����ݿ���Ϣ,����ѧ���ļ���������������������ݿ���

@���� stuNum��ѧ��
@���� subject�����Կ�Ŀ
@���� flagCheat�����ױ��
@����ֵ �ɹ�1ʧ��0
*/
int DbUpdate(string stuNum,	vector<string> dateVec,	
			 vector<string> subjectVec,	vector<string> stuNum2,	
			 vector<string> flagVec)
{
	/*�ַ�ת��������ʹ��*/
	string  userName(g_db_userName.c_str());
	string  password(g_db_password.c_str());
	string  hostName(g_db_hostName.c_str());
	string  dBName(g_db_dBName.c_str());

	/*�����ִ�����*/
	int count = subjectVec.size();
	vector<string > sqlKC; //�γ̱����׵�һ�ֶ�
	int ci = 0;	//ѭ��

	string flagSQL = "0";//���   ������˽����
	for (ci = 0; ci < count; ++ci)
	{
		if (flagVec[ci] == "1")
			flagSQL = "1";

		/*���׵�*/
		string  sqlKC1 = "UPDATE ZK.T_BYSQ_KS_KC SET BJSH_JG_JQ =";//���_�γ�_����	
		sqlKC1 += flagVec[ci].c_str();
		sqlKC1 += " WHERE KS_ZKZ2=";
		sqlKC1 += stuNum2[ci].c_str();
		sqlKC1 += " AND TJ_KC_DM=";
		sqlKC1 += subjectVec[ci].c_str();
		sqlKC1 += " AND KSSJ=";
		sqlKC1 += dateVec[ci].c_str();
		sqlKC1 += " AND  KS_ZKZ=";
		sqlKC1 += stuNum.c_str();

		sqlKC.push_back(sqlKC1);
	}

	::CoInitialize(NULL);//��ʼ��com���

	/*�������ݿ��*/
	try{
		p_conn.CreateInstance("ADODB.Connection");//��������
		p_recordset.CreateInstance("ADODB.Recordset");//���������,Ҳ����ʵ����
		p_cmd.CreateInstance("ADODB.Command");

		p_conn->CursorLocation = adUseClient; //�洢����ͬʱ���ؼ�¼���ͷ���ֵ
		p_conn->Open(_bstr_t(str_conn.c_str()), _bstr_t(userName.c_str()), _bstr_t(password.c_str()), adConnectUnspecified);
		p_cmd->ActiveConnection = p_conn;

		for (ci = 0; ci < count; ++ci)
		{
			p_recordset->Open(_bstr_t(sqlKC[ci].c_str()),//���µڶ���
				p_conn.GetInterfacePtr(),
				adOpenStatic,
				adLockOptimistic,
				adCmdText);
		}
	}
	catch (_com_error e){ return 0; }

	/*�رղ�ѯ*/
	try	{
		::CoUninitialize();
	}
	catch (_com_error e){ }
	return 1;
}
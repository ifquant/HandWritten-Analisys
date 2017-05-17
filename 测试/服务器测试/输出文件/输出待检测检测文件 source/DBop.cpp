/*
ʵ���ļ���DBop.cpp ���ݿ����ʵ���ļ�
*/
#include "DBop.h"

/*���ص�ȫ�ֱ���*/

_ConnectionPtr	p_conn;			/*ȫ�ֱ��� ���Ӷ���*/
_RecordsetPtr	p_recordset;	/*ȫ�ֱ��� ��¼������*/
_CommandPtr		p_cmd;			/*ȫ�ֱ��� ����������*/
string			str_conn;		/*ȫ�ֱ��� �����ַ�������*/


/**
���ܣ�	��ѯ����ѧ����ѧ�ţ������е�ָ��λ�õ����ݿ���Ϣ(ѧ��)ȫ���洢����Ϊstu��vector<string>�͵ı�����

@���� stu ѧ��ѧ�Ŵ洢
@����ֵ �ɹ�1 ʧ��0
*/
int DbStu(vector<string>& stu)
{
	/*�ַ�ת��������ʹ��*/
	string userName(g_db_userName.c_str());
	string password(g_db_password.c_str());
	string hostName(g_db_hostName.c_str());
	string dBName(g_db_dBName.c_str());

	//�����ִ�����	//��ΪstrConn��ȫ�ֱ�������˽�����ʼ��һ��
	str_conn = "Provider=OraOLEDB.Oracle";
	str_conn += ";Persist Security Info = true";
	str_conn += ";User ID = ";	//==================//	
	str_conn += userName;		//===����ʼ��һ��===//
	str_conn += ";Password=";	//==================//
	str_conn += password;
	str_conn += ";Data Source = (DESCRIPTION = (ADDRESS = (PROTOCOL = TCP)";
	str_conn += "(HOST=";
	str_conn += hostName;
	str_conn += ")(PORT=1521))(CONNECT_DATA=";
	str_conn += "(SERVICE_NAME=";
	str_conn += dBName;
	str_conn += ")))";

	::CoInitialize(NULL);//��ʼ��com���

	//�������ݿ⣬��ִ��sql��ѯ���	������Ҫ��try catch�����쳣��
	try{
		p_conn.CreateInstance("ADODB.Connection");//��������
		p_recordset.CreateInstance("ADODB.Recordset");//���������,Ҳ����ʵ����
		p_cmd.CreateInstance("ADODB.Command");

		p_conn->CursorLocation = adUseClient; //�洢����ͬʱ���ؼ�¼���ͷ���ֵ
		p_conn->Open(_bstr_t(str_conn.c_str()), _bstr_t(userName.c_str()), _bstr_t(password.c_str()), adConnectUnspecified);
		p_cmd->ActiveConnection = p_conn;

		//SELECT KS_ZKZ FROM ZK.V_BYSQ_BJSH_JQ_KS
		//SELECT DISTINCT(KS_ZKZ2) FROM ZK.T_BYSQ_KS_KC WHERE KSSJ BETWEEN '200907' AND '201510'
		//SELECT * FROM ZK.T_BYSQ_KS_KC WHERE (SUBSTR(KS_ZKZ2,1,2) = '02' OR SUBSTR(KS_ZKZ2,1,2) = '03')
		//SELECT KS_ZKZ2 FROM ZK.T_BYSQ_KS_KC WHERE KSSJ between '200907' and '201510' AND (SUBSTR(KS_ZKZ2,1,2) = '02') AND BJSH_JG_JQ IS NULL GROUP BY KS_ZKZ2 HAVING COUNT(KS_ZKZ2)>1
		/*HRESULT hr1 = pRecordset->Open("SELECT KS_ZKZ FROM ZK.T_BYSQ_KS_KC WHERE KSSJ between '200907' and '201510' AND (SUBSTR(KS_ZKZ2,1,2) = '02') AND BJSH_JG_JQ IS NULL GROUP BY KS_ZKZ HAVING COUNT(KS_ZKZ)>1",*/


		/*�����ѯ���*/
		int zong_flag = g_db_qurry_zone.length();
		int num_flag = g_db_qurry_stu_num.length();
		int date_flag = g_db_qurry_start.length();

		string str_qurry = "SELECT KS_ZKZ FROM YANNSY.T_BYSQ_KS_KC WHERE KSSJ between ";
		str_qurry += g_db_qurry_start;
		str_qurry += " and ";
		str_qurry += g_db_qurry_end;

//		cout<<str_qurry.c_str()<<endl;
		if (num_flag - 1)//���ȴ���1��������Ҫ��ѯѧ��
		{
			str_qurry += "AND KS_ZKZ = ";
			str_qurry += g_db_qurry_stu_num;
		}
		else//����Ҫ��ѯ����ѧ�ŲŻ�����������÷�Χ
		{
			if ((zong_flag - 1))//���ȴ���1,������Ҫ��ѯ����,�Ҳ�ѯʱ��
			{
				str_qurry += " AND(SUBSTR(KS_ZKZ2, 1, 2) = ";
				str_qurry += g_db_qurry_zone;
				str_qurry += ")";
			}
		}
		if (g_db_qurry_all)
		{
			str_qurry += " AND BJSH_JG_JQ IS NULL";
		}
		str_qurry += " GROUP BY KS_ZKZ HAVING COUNT(KS_ZKZ)>1";
		_variant_t _vstr_qurry(str_qurry.c_str());/* ת��stringΪ_variant_t */



		/*��ѯ*/
		HRESULT hr1 = p_recordset->Open(_vstr_qurry,
			p_conn.GetInterfacePtr(),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);
		if (!(SUCCEEDED(hr1))){ exit(-1); }//��ȡ���ɹ���ֱ���˳�����

		int count_exit = 10;
		do
		{//��ȡ�ɹ�����ÿһ�д浽vector��stuĩβ
			stu.push_back((string)(_bstr_t)(p_recordset->Fields->GetItem(_variant_t("KS_ZKZ"))->GetValue()));
			p_recordset->MoveNext();//�Ƶ���һ��
		} while (!p_recordset->EndOfFile && count_exit--);//������û�е����м�¼��ĩβ
	}
	catch (_com_error e){
		cout << "<��ȡѧ��(���ݿ�):>��ѯʧ��--" << endl;
		cout<<e.Error()<<" "<<e.ErrorMessage()<<" "<<e.ErrorInfo()<<endl;
	}
	/*=================================================================================================*/

	//3���رղ�ѯ====//ִ�ж�ȡ��Ϻ�Ҫ�ر�����
	try	{ ::CoUninitialize(); }
	catch (_com_error e){ /*cout << "<��ȡѧ��:�ر�ʧ��-->"  << e.ErrorInfo() << endl;*/ }

	cout<<"��ѯ���"<<endl;
	return 1;
}
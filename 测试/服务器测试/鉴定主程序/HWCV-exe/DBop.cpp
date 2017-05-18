/*
ʵ���ļ���DBop.cpp ���ݿ����ʵ���ļ�
*/
#include "DBop.h"
#include "path.h"

/*���ص�ȫ�ֱ���*/

_ConnectionPtr	p_conn;			/*ȫ�ֱ��� ���Ӷ���*/
_RecordsetPtr	p_recordset;	/*ȫ�ֱ��� ��¼������*/
_CommandPtr		p_cmd;			/*ȫ�ֱ��� ����������*/
string			str_conn;		/*ȫ�ֱ��� �����ַ�������*/


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

//	cout<<g_db_userName.c_str()<<endl;
//	cout<<g_db_password.c_str()<<endl;
//	cout<<g_db_hostName.c_str()<<endl;
//	cout<<g_db_dBName.c_str()<<endl;

	/*��������������*/
	//Provider=OraOLEDB.Oracle.1;Persist Security Info = true;User ID = BJSH;Password=bjshadmin;Data Source = (DESCRIPTION = (ADDRESS = (PROTOCOL = TCP)(HOST=192.168.200.97)(PORT=1521))
	//(CONNECT_DATA=(SERVICE_NAME=purple)))",
	str_conn = "Provider=OraOLEDB.Oracle.1;Persist Security Info = true;User ID = ";	
	str_conn += userName;		//===����ʼ��һ��===//
	str_conn += ";Password=";	//==================//
	str_conn += password;
	str_conn += ";Data Source = (DESCRIPTION = (ADDRESS = (PROTOCOL = TCP)(HOST=";
	str_conn += hostName;
	str_conn += ")(PORT=1521))(CONNECT_DATA=(SERVICE_NAME=";
	str_conn += dBName;
	str_conn += ")))";

	//�����ѯ���				�¾�ע����sql��䣬��Ҫ�������������
	/*select KS_ZKZ, KSSJ, TJ_KC_DM from ZK.T_BYSQ_KS_KC WHERE KSSJ between '200907' and '201510' and KS_ZKZ = 010207203867*/
	/*string  sql = "select KS_ZKZ2, KSSJ, TJ_KC_DM from ZK.T_BYSQ_KS_KC WHERE KSSJ between '200907' and '201504' AND KS_ZKZ = ";*/
	// select KS_ZKZ, KSSJ, TJ_KC_DM from ZK.T_BYSQ_KS_KC WHERE KSSJ between '200907' and '201510' and KS_ZKZ = 010214100225
	//"select KS_ZKZ, KSSJ, TJ_KC_DM from ZK.T_BYSQ_KS_KC WHERE KSSJ between '200907' and '201510' and KS_ZKZ = 010214100225",
	string sql = "select KS_ZKZ2, KSSJ, TJ_KC_DM from ";
	sql += g_db_hoster_zk;
	sql += ".T_BYSQ_KS_KC WHERE KSSJ between ";
	sql += g_db_qurry_start;
	sql += " and ";
	sql += g_db_qurry_end;
	sql += " AND KS_ZKZ =";
	sql += stuNum.c_str();

	_bstr_t _vstr_sql(sql.c_str());/* ת��stringΪ_variant_t */
	::CoInitialize(NULL);//��ʼ��com���

	/*������������*/
	try{
		p_conn.CreateInstance("ADODB.Connection");//��������
		p_recordset.CreateInstance("ADODB.Recordset");//���������,Ҳ����ʵ����


		p_conn->CursorLocation = adUseClient; //�洢����ͬʱ���ؼ�¼���ͷ���ֵ
		p_conn->Open(_bstr_t(str_conn.c_str()),
		//p_conn->Open("Provider=OraOLEDB.Oracle.1;Persist Security Info = true;User ID = BJSH;Password=bjshadmin;Data Source = (DESCRIPTION = (ADDRESS = (PROTOCOL = TCP)(HOST=192.168.200.97)(PORT=1521))(CONNECT_DATA=(SERVICE_NAME=purple)))",
			_bstr_t(userName.c_str()),
			_bstr_t(password.c_str()),
			adConnectUnspecified);
		


		cout << _vstr_sql << endl;
		SaveLog(_vstr_sql, "D:/HWCV/1/txt", "a");
	//	SaveLog((char*)str_conn.c_str(), g_log_adr, "a");
		HRESULT hr = p_recordset->Open(_bstr_t(_vstr_sql),//ִ��sq��䣬��ѯһ��ѧ�������п�����Ϣ
		//HRESULT hr = p_recordset->Open("select KS_ZKZ, KSSJ, TJ_KC_DM from ZK.T_BYSQ_KS_KC WHERE KSSJ between '200907' and '201510' and KS_ZKZ = 010214100225",
			p_conn.GetInterfacePtr(),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);
//		cout<<"count:"<<p_recordset->RecordCount <<endl;
		//����������������vector������
		if (p_recordset->RecordCount < 1)//�����Ϊ��
		{
			return 0;//û����Ϣ��ֱ�����������
		}
		do{ //����������������vector������
			string comp = (string)(_bstr_t)(p_recordset->Fields->GetItem(_variant_t("KS_ZKZ2"))->GetValue());
			if (!strcmp(comp.substr(0, 1).c_str(), "4") || !strcmp(comp.substr(0, 1).c_str(), "9")) //��4��9 ��ͷ�Ŀ��ţ���ͼ��ֱ�Ӵ����
				continue;
			dateVec.push_back((string)(_bstr_t)(p_recordset->Fields->GetItem(_variant_t("KSSJ"))->GetValue()));
			subjectVec.push_back((string)(_bstr_t)(p_recordset->Fields->GetItem(_variant_t("TJ_KC_DM"))->GetValue()));
			stuNum2.push_back((string)(_bstr_t)(p_recordset->Fields->GetItem(_variant_t("KS_ZKZ2"))->GetValue()));
			p_recordset->MoveNext();
		} while (!p_recordset->EndOfFile);
	}
	catch (_com_error e)
	{
		return 0;
//		printf("%x", e.Error());
		cout<<"Failed"<<endl;
	}

	/*�رղ�ѯ*/
	::CoUninitialize(); 

	return 1;
}



/**
�����ܣ�	����ѧ�����ݿ���Ϣ,����ѧ���ļ���������������������ݿ���

@���� stuNum��ѧ��
@���� subject�����Կ�Ŀ
@���� flagCheat�����ױ��
@����ֵ �ɹ�1ʧ��0
*/
int DbUpdate(string stuNum,	vector<string> dateVec,	vector<string> subjectVec,	vector<string> stuNum2,	vector<string> flagVec)
{
	/*�ַ�ת��������ʹ��*/
	string  userName(g_db_userName.c_str());
	string  password(g_db_password.c_str());
	string  hostName(g_db_hostName.c_str());
	string  dBName(g_db_dBName.c_str());

	/*�����ִ�����*/
	int count = subjectVec.size();

	vector<string> sqlKC; //�γ̱����׵�һ�ֶ�
	int ci = 0;	//ѭ��
	string flag = "0";
	/*����������--KC��ĸ��� */
	for (ci = 0; ci < count; ++ci)
	{
		if(flagVec[ci]=="1") // ���������������ɵ�ͼ�񣬾��϶�����Ϊ��������
			flag = "1";

		/*���׵�*/
		string  sqlKC1 = "UPDATE ";
		sqlKC1 += g_db_hoster_zk;
		sqlKC1 += ".T_BYSQ_KS_KC SET BJSH_JG_JQ =";//���_�γ�_����	
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
	/* �������--��ͼ���� */
	string sqlView = "UPDATE YANNSY.V_BYSQ_BJSH_JQ_KS SET BJSH_JG_JQ=";
	sqlView += flag;
	sqlView += "WHERE KS_ZKZ = ";
	sqlView += stuNum;
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
		p_recordset->Open(_bstr_t(sqlView.c_str()),//���µڶ���
			p_conn.GetInterfacePtr(),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);		
	}
	catch (_com_error e){ return 0; cerr << "Err:"; }

	/*�رղ�ѯ*/
	::CoUninitialize();
	
	return 1;
}
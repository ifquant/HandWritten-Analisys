// cHWCV.h : CcHWCV ������

#pragma once
#include "resource.h"       // ������



#include "HWCVDLL2_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

using namespace ATL;


// CcHWCV

class ATL_NO_VTABLE CcHWCV :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CcHWCV, &CLSID_cHWCV>,
	public IDispatchImpl<IcHWCV, &IID_IcHWCV, &LIBID_HWCVDLL2Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CcHWCV()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CHWCV)


BEGIN_COM_MAP(CcHWCV)
	COM_INTERFACE_ENTRY(IcHWCV)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(aspHWCV)(BSTR filepath, BSTR* _arg2);
};

OBJECT_ENTRY_AUTO(__uuidof(cHWCV), CcHWCV)

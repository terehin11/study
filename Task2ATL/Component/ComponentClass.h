// ComponentClass.h: объявление CComponentClass

#pragma once
#include "resource.h"       // основные символы



#include "Component_i.h"
#include <list>
#include <atlsafe.h>
using namespace std;

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Однопотоковые COM-объекты не поддерживаются должным образом платформой Windows CE, например платформами Windows Mobile, в которых не предусмотрена полная поддержка DCOM. Определите _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA, чтобы принудить ATL поддерживать создание однопотоковых COM-объектов и разрешить использование его реализаций однопотоковых COM-объектов. Для потоковой модели в вашем rgs-файле задано значение 'Free', поскольку это единственная потоковая модель, поддерживаемая не-DCOM платформами Windows CE."
#endif

using namespace ATL;


// CComponentClass

class ATL_NO_VTABLE CComponentClass :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CComponentClass, &CLSID_ComponentClass>,
	public IDispatchImpl<IComponentClass, &IID_IComponentClass, &LIBID_ComponentLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CComponentClass()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COMPONENTCLASS)


BEGIN_COM_MAP(CComponentClass)
	COM_INTERFACE_ENTRY(IComponentClass)
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



	STDMETHOD(Add)(DOUBLE value);
	STDMETHOD(Remove)(DOUBLE value);
	STDMETHOD(GetData)(SAFEARRAY** _array);
	STDMETHOD(get_Count)(ULONG* pVal);
	STDMETHOD(get_Mean)(DOUBLE* pVal);

	list<double> List;

	
};

OBJECT_ENTRY_AUTO(__uuidof(ComponentClass), CComponentClass)

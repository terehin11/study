#include <Shlwapi.h>
#include "Factory.h"

HINSTANCE hDll;

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,
	DWORD fdwReason,
	LPVOID lpvReserved
	)
{
	hDll = hinstDLL;
	return TRUE;
}


ULONG g_cServerLock; // счетчик блокировок
ULONG g_cComponents;
Factory::Factory()
{
	m_cRef = 0;
}

HRESULT __stdcall Factory::QueryInterface(REFIID iid, void** ppv)
{
	if (iid == IID_IUnknown)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}

	else if (iid == IID_IClassFactory)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}
ULONG __stdcall Factory::AddRef()
{
	return ++m_cRef;
	
}
ULONG __stdcall Factory::Release()
{
	if (--m_cRef == 0)
	{
		delete this;
		return 0;
	}
	return m_cRef;
}
HRESULT __stdcall Factory::CreateInstance(IUnknown* pUnknownOuter, REFIID iid, void** ppv)
{
	IUnknown *pA = (ICollection*)new CList;
	if (pA == NULL) return E_OUTOFMEMORY;

	HRESULT hr = pA->QueryInterface(iid, ppv);

	return hr;
}
HRESULT __stdcall Factory::LockServer(BOOL bLock)
{
	if (bLock) g_cServerLock++;
	else g_cServerLock--;
	return S_OK;
}

STDAPI DllCanUnloadNow()
{
	if ((g_cComponents == 0) && (g_cServerLock == 0)) return S_OK;
	else return S_FALSE;
}

STDAPI DllGetClassObject(REFCLSID clsid, REFIID iid, void** ppv)
{
	Factory* pFactory = new Factory;
	if (pFactory == NULL) return E_OUTOFMEMORY;
	pFactory->AddRef();
	HRESULT hr = pFactory->QueryInterface(iid, ppv);
	pFactory->Release();
	return hr;
}


STDAPI  DllRegisterServer()
{
	wstring fullStr(L"Software\\Classes\\CLSID\\");
	wchar_t *sz;
	if (SUCCEEDED(StringFromCLSID(CLSID_CList, &sz)))
	{
		
		fullStr.append(sz);
		fullStr.append(L"\\InProcServer32");
		CoTaskMemFree(sz);
		HKEY hk;
		if (RegCreateKey(HKEY_CURRENT_USER, fullStr.c_str(), &hk) == ERROR_SUCCESS)
		{
			WCHAR   DllPath[MAX_PATH] = { 0 };
			GetModuleFileName(hDll, DllPath, MAX_PATH);
			if (RegSetValue(hk, NULL , REG_SZ, DllPath, MAX_PATH) == ERROR_SUCCESS)
			{
				RegCloseKey(hk);
				return S_OK;
			}
				
		}

	}
	return E_FAIL;
}

STDAPI  DllUnregisterServer()
{
	wstring fullStr(L"Software\\Classes\\CLSID\\");
	wchar_t *sz;
	if (SUCCEEDED(StringFromCLSID(CLSID_CList, &sz)))//заполняем sz - ковнертируем в строку CLSID List-а
	{
		fullStr.append(sz);
		CoTaskMemFree(sz);
			if (SHDeleteKeyW(HKEY_CURRENT_USER, fullStr.c_str()) == ERROR_SUCCESS)//удаляем ключ
			{
				return S_OK;
			}		
	}
	return E_FAIL;
}

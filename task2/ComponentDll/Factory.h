#pragma once
#include "Component.h"
class Factory : public IClassFactory
{
public:
	HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter, REFIID iid, void** ppv);
	HRESULT __stdcall LockServer(BOOL bLock) ;

	////////////////////////////
	// Ìועמהû IUnknown
	HRESULT __stdcall QueryInterface(REFIID iid, void** ppv);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	ULONG m_cRef;
	HKEY hk;
	Factory();
	

};


// dllmain.cpp: ���������� DllMain.

#include "stdafx.h"
#include "resource.h"
#include "Component_i.h"
#include "dllmain.h"

CComponentModule _AtlModule;

// ����� ����� DLL
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;



	

	return _AtlModule.DllMain(dwReason, lpReserved); 
}

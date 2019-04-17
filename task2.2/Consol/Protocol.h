#pragma once
#include <iostream>
//#include "../ComponentDll/InterfaceDll_h.h"
#import "../ComponentDll/x64/Debug/ComponentDll.tlb"
using namespace std;
using namespace MyComLib;



class Protocol
{
public:
	//CREATEINSTANCEPROC createInst;
	IUnknown * iunkn;
	HMODULE hdll;
	HRESULT  hr;
	Protocol();
	~Protocol();

	void printObj(const Object &obj);

	//void LoadLibr();

	bool InterfaceIColl();
	bool InterfaceIEnum();
	void AddElemet(int a);
	void AddElemet(double a);
	void AddElemet(double a,double b);
	unsigned GetCount();
	int MoveNext();
	void Reset();
	Object GetCurrent();
	void Remove(int a);
	void Remove(double a);
	void Remove(double a, double b);
	ObjectArray* ToArray();
	ICollectionPtr pICol;
	IEnumeratorPtr pIEnu;
	

	void Release();
};


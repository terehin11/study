#include <iostream>
#include <objbase.h>
#include "Interfaces.h"
#include <list>
using namespace std;


void main()
{
	HRESULT  hr;

	setlocale(LC_ALL, "Russian");
	HMODULE hdll = LoadLibrary(L"ComponentDll.dll");
	if (hdll == NULL)
	{
		cout << "Error open dll!!";
		return;
	}
	else cout << "Library load successfully!!" << endl;
	CREATEINSTANCEPROC createInst;
	IUnknown * iunkn;
	createInst = (CREATEINSTANCEPROC)GetProcAddress(hdll, "CreateInstance");
	if (createInst == NULL)
	{
		cout << "Error getting address";
		return;
	}
	else cout << "Address successfuly received!!!" << endl;
	
	ICollection* pICol = 0;
	IEnumerator* pIEnu = 0;

	iunkn = createInst();


	int N = 0;
	unsigned int *size = 0;
	Object k;
	k.Value.Int = 0;
	list<Object> List;

	for (;;)
	{

		cout << "�������� ���������� ��������: " << endl;
		cout << "1 - �������� �������� � ����." << endl;
		cout << "2 - ������� ������� �� ������." << endl;
		cout << "3 - ������ ������ �����." << endl;
		cout << "4 - ��������� � ������." << endl;
		cout << "5 - �������� ����." << endl;
		cout << "6 - �������� ��������� �������." << endl;
		cout << "7 - GetCurrent" << endl;
		cin >> N;
		int* next = 0;

		switch (N)
		{
		case 1:
			cout << "������� �������, ������� ������ ��������: ";
			cin >> k.Value.Int;
			//�������� ���� � ������ �������� Object
			hr = iunkn->QueryInterface(IID_ICollection, (void**)&pICol);
			if (SUCCEEDED(hr))
			{
				pICol->Add(k);
			}
			break;
		case 2:

			cout << "�������� �������, ������� ������ �������: " << endl;
			break;
			//����� ������� ��� �������� �� List � ������� �� ��� ��� ������ 
		case 3:
			hr = iunkn->QueryInterface(IID_ICollection, (void**)&pICol);
			if (SUCCEEDED(hr))
			{
				pICol->GetCount(size);
			}
			cout << "������ �����: " << size << endl;
			break;
		case 4:
			//ObjectArray!!!
			hr = iunkn->QueryInterface(IID_ICollection, (void**)&pICol);
			if (SUCCEEDED(hr))
			{
				//pICol->ToArray();
			}
			break;
		case 5:
			hr = iunkn->QueryInterface(IID_IEnumerator, (void**)&pIEnu);
			if (SUCCEEDED(hr))
			{

				pIEnu->Reset();
			}
			break;
		case 6:

			hr = iunkn->QueryInterface(IID_IEnumerator, (void**)&pIEnu);
			if (SUCCEEDED(hr))
			{
				
				pIEnu->MoveNext(next);
			}
			cout << "��������� ������� ";
			break;
			//cin >> next;
		case 7:
			hr = iunkn->QueryInterface(IID_IEnumerator, (void**)&pIEnu);
			if (SUCCEEDED(hr))
			{

				//pIEnu->GetCurrent();
			}
			break;
		default:
			break;
		}

	}

	
}


#import "../Debug/Component.dll"
#include <iostream>
#include <atlsafe.h>
using namespace ComponentLib;
using namespace std;




void main()
{
	if (SUCCEEDED(CoInitialize(NULL)))
	{
		setlocale(LC_ALL, "RU");
		//pICol = ICollectionPtr(__uuidof(CList));
		IComponentClassPtr IComCl= IComponentClassPtr(__uuidof(ComponentClass));
		//HRESULT hr = IComCl.CreateInstance(__uuidof(ComponentClass));
		
		IComCl->Add(3.);
		cout << "Добавлено 3" << endl;

		IComCl->Add(6.);
		cout << "Добавлено 6" << endl;
		IComCl->Add(10.);
		cout << "Добавлено 10" << endl;
		IComCl->Add(15.2);
		cout << "Добавлено 15.2" << endl;

		int count_List = IComCl->Count;
		//IComCl->get_Count(count_List);
		cout << "Элементов в листе: " << count_List << endl;
		double mean_List = IComCl->Mean;
		//IComCl->get_Mean(mean_List);
		cout << "Среднее значение в листе: " << mean_List << endl;

		IComCl->Remove(3);
		IComCl->Remove(15.2);
		cout << "Удалены элементы 3 и 15,2" << endl;
		count_List = IComCl->Count;
		cout << "Элементов в листе после удаления: " << count_List << endl;

		SAFEARRAY* safAr = IComCl->GetData();
		CComSafeArray<double> csafeAr;
		csafeAr.Attach(safAr);

		for (int i = 0; i < csafeAr.GetCount(); i++)
		{
			cout << "Элемент: " << csafeAr[i] << endl;
		}



		IDispatchPtr IDis;
		IComCl->QueryInterface(&IDis);
	}
	
}

//
//void test()
//{
//	HRESULT hr = OleInitialize(NULL);
//	//wchar_t progid[] = L";
//	CLSID clsid;
//	hr = CLSIDFromProgID(progid, &clsid);
//	IDispatch* pIDispatch = NULL;
//}


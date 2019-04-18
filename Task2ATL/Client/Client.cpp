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
		HRESULT hr;
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

		cout << endl << "Список элементов" << endl;
		for (int i = 0; i < csafeAr.GetCount(); i++)
		{
			cout << "Элемент: " << csafeAr[i] << endl;
		}

		cout << endl << endl << endl << endl << "Используем IDispatch"  << endl << endl;


		DISPPARAMS disp = { 0 };
		IDispatchPtr IDis;
		DISPID dispid;
		OLECHAR* name = L"Add";
		hr = IComCl->QueryInterface(&IDis);
		hr = IDis->GetIDsOfNames(IID_NULL, &name, 1, GetUserDefaultLCID(), &dispid);
		_variant_t vart(3.);
		disp.rgvarg = &vart;
		disp.cArgs = 1;
		hr = IDis->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		cout << "Добавлен элемент 3" << endl;

		name = L"Remove";
		hr = IDis->GetIDsOfNames(IID_NULL, &name, 1, GetUserDefaultLCID(), &dispid);
		vart = 10.;
		disp.rgvarg = &vart;
		disp.cArgs = 1;
		hr = IDis->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		cout << "Удален элемент 10" << endl;

		name = L"Count";
		hr = IDis->GetIDsOfNames(IID_NULL, &name, 1, GetUserDefaultLCID(), &dispid);
		disp.rgvarg = 0;
		disp.cArgs = 0;
		_variant_t tmp;
		hr = IDis->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_PROPERTYGET, &disp, &tmp, NULL, NULL);	
		cout << "Элементов в списке: " << (unsigned long)tmp << endl;

		name = L"Mean";
		hr = IDis->GetIDsOfNames(IID_NULL, &name, 1, GetUserDefaultLCID(), &dispid);
		disp.rgvarg = 0;
		disp.cArgs = 0;
		tmp = 0;
		hr = IDis->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_PROPERTYGET, &disp, &tmp, NULL, NULL);
		cout << "Среднее значение: " << (double)tmp << endl;

		name = L"GetData";
		hr = IDis->GetIDsOfNames(IID_NULL, &name, 1, GetUserDefaultLCID(), &dispid);
		//vart = safAr;
		disp.rgvarg = 0;
		disp.cArgs = 0;
		hr = IDis->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &disp, &vart, NULL, NULL);
		csafeAr.Destroy();
		csafeAr.Attach(vart.parray);
		cout << endl << "Список элементов" << endl;
		for (int i = 0; i < csafeAr.GetCount(); i++)
		{
			cout << "Элемент: " << csafeAr[i] << endl;
		}

	}
	
}


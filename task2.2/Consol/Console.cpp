#include <iostream>
#include <objbase.h>
#include "Protocol.h"
#include <list>
using namespace std;


void main()
{
	setlocale(LC_ALL, "RU");
	Protocol pr;
	if (SUCCEEDED(CoInitialize(NULL)))
	{
		pr.InterfaceIColl();

		unsigned int res = 0;
		res = pr.GetCount();
		cout << endl << "Numbers of elements in list: " << res << endl;

		pr.AddElemet(3);
		cout << "Added element: 3";

		pr.AddElemet(3.1);
		cout << endl << "Added element: 3.1";

		pr.AddElemet(71.5, 36.6);
		cout << endl << "Added array: [71.5, 36.6]";

		pr.Remove(3);
		cout << endl << "Remove element: 3";

		res = 0;
		res = pr.GetCount();
		cout << endl << "Numbers of elements in list: " << res << endl;


		ObjectArray* mas;
		Object mas_obj;
		mas_obj.Type = otArray;
		mas = pr.ToArray();
		mas_obj.Value.Array = mas;

		cout << endl << "Перевед в массив ";
		pr.printObj(mas_obj);

		cout << endl << "IEnum" << endl;
		pr.InterfaceIEnum();
		pr.Reset();

		for (;;)
		{
			if (pr.MoveNext() == 0)
			{
				cout << "Empty" << endl;
				break;
			}
			else
			{
				pr.printObj(pr.GetCurrent());
			}
		}

	//	pr.Release();
	}
	//pr.LoadLibr();

	


}





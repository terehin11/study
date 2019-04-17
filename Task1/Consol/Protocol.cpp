#include "Protocol.h"



Protocol::Protocol()
{


}


Protocol::~Protocol()
{
}

ObjectArray* Protocol::ToArray()
{






	ObjectArray *object_Array ;

	pICol->ToArray(&object_Array);



	return object_Array;
}

void Protocol::AddElemet(int a)
{
	Object obj;
	obj.Value.Int = a;
	obj.Type = otInt;
	pICol->Add(obj);
}
void Protocol::AddElemet(double a)
{
	Object obj;
	obj.Value.Double = a;
	obj.Type = otDouble;
	pICol->Add(obj);
}

void Protocol::AddElemet(double a, double b)
{
	Object oa, ob;
	oa.Type = otDouble;
	ob.Type = otDouble;
	oa.Value.Double = a;
	ob.Value.Double = b;
	ObjectArray *obj = new ObjectArray;
	obj->Data = new Object[2];
	obj->Count = 2;
	obj->Data[0] = oa;
	obj->Data[1] = ob;
	Object buf;
	buf.Type = otArray;
	buf.Value.Array = obj;
	pICol->Add(buf);

}

unsigned Protocol::GetCount()
{
	unsigned int a = 0;
	pICol->GetCount(&a);
	return a;
}

Object Protocol::GetCurrent()
{
	Object el;
	pIEnu->GetCurrent(&el);
	return el;
}

void Protocol::Remove(int a)
{
	Object obj;
	obj.Value.Int = a;
	obj.Type = otInt;
	pICol->Remove(obj);
}

void Protocol::Remove(double a)
{
	Object obj;
	obj.Value.Double = a;
	obj.Type = otDouble;
	pICol->Remove(obj);
}


void Protocol::Remove(double a,double b)
{
	Object oa, ob;
	oa.Type = otDouble;
	ob.Type = otDouble;
	oa.Value.Double = a;
	ob.Value.Double = b;
	ObjectArray *obj = new ObjectArray;
	obj->Data = new Object[2];
	obj->Count = 2;
	obj->Data[0] = oa;
	obj->Data[1] = ob;
	Object buf;
	buf.Type = otArray;
	buf.Value.Array = obj;
	pICol->Remove(buf);
}

int Protocol::MoveNext()
{
	int a = 0;
	pIEnu->MoveNext(&a);
	return a;
}


void Protocol::Reset()
{
	pIEnu->Reset();
}
bool Protocol::InterfaceIColl()
{
	hr = iunkn->QueryInterface(IID_ICollection, (void**)&pICol);
	if (SUCCEEDED(hr))
	{
		return true;
	}
	else return false;
}

bool Protocol::InterfaceIEnum()
{
	hr = iunkn->QueryInterface(IID_IEnumerator, (void**)&pIEnu);
	if (SUCCEEDED(hr))
	{
		return true;
	}
	else return false;
}
void Protocol::LoadLibr()
{
	hdll = LoadLibrary(L"ComponentDll.dll");
	if (hdll == NULL)
	{
		cout << "Error open dll!!";
		return;
	}
	else cout << "Library load successfully!!" << endl;

	createInst = (CREATEINSTANCEPROC)GetProcAddress(hdll, "CreateInstance");
	if (createInst == NULL)
	{
		cout << "Error getting address";
		return;
	}
	else cout << "Address successfuly received!!!" << endl;


	iunkn = createInst();
}

void Protocol::printObj(const Object &obj)
{
	switch (obj.Type)
	{
	case otInt:
		cout << obj.Value.Int << endl;
		break;
	case otDouble:
		cout << obj.Value.Double << endl;
		break;
	case otArray:
		for (int i = 0; i < obj.Value.Array->Count; i++)
		{
			printObj(obj.Value.Array->Data[i]);
		}
		break;
	default:
		break;
	}
}

void Protocol::Release()
{
	iunkn->Release();
	pICol->Release();
	pIEnu->Release();
}
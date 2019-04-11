#include "Component.h"

const bool operator == (const Object &a, const Object &b)
{
	if (a.Type != b.Type)
	{
		cout << "Different type!!" << endl;
		return false;
	}
	else
	{
		switch (a.Type)
		{
		case otInt:
			if (a.Value.Array != b.Value.Array) break;
			else return true;
		case otArray:
			if (a.Value.Array->Count != b.Value.Array->Count) break;
			else if (a.Value.Array->Data != b.Value.Array->Data) break;
			else return true;
		case otDouble:
			if (sqrt((b.Value.Double - a.Value.Double)*(b.Value.Double - a.Value.Double)) >= 0.0001) break;
			else return true;
		default:
			break;
		}

	}
	return false;
}



	////////////////////////////
		// Методы IUnknown
	HRESULT __stdcall CList::QueryInterface(REFIID iid, void** ppv)
	{
		if (iid == IID_IUnknown)
		{
			*ppv = static_cast<ICollection*>(this);
		}
		else if (iid == IID_ICollection)
		{
			*ppv = static_cast<ICollection*>(this);
		}
		else if (iid == IID_IEnumerator)
		{
			*ppv = static_cast<IEnumerator*>(this);
		}
		else
		{
			*ppv = NULL;
			return E_NOINTERFACE;
		}
		AddRef();
		return S_OK;
	}

	ULONG __stdcall CList::AddRef()
	{
		return ++m_cRef;
	}

	ULONG __stdcall CList::Release()
	{
		if (--m_cRef == 0)
		{
			delete this;
			return 0;
		}
		return m_cRef;
	}

	////////////////////////////
	// Методы ICollection
	HRESULT __stdcall CList::Add(Object obj)
	{
		List.push_back(obj);
		
		return S_OK;
	}
	
	HRESULT __stdcall CList::Remove(Object obj)
	{
		List.remove(obj);
		return S_OK;
	}
	HRESULT __stdcall CList::GetCount(unsigned *count)
	{
		*count = List.size();


		return S_OK;
	}
	HRESULT __stdcall CList::ToArray(ObjectArray **arr)
	{
		*arr = new ObjectArray;
		(*arr)->Data = new Object[List.size()];
		(*arr)->Count = (unsigned)List.size();
		int i = 0;
		for (auto it : List)
		{
			(*arr)->Data[i] = it;
			i++;
		}
		//переписать !!! copy(List.begin(), List.end(), arr);
		return S_OK;
	}

	////////////////////////////
	// Методы IEnumerator
	HRESULT __stdcall CList::Reset()
	{
		List.clear();
		return S_OK;
	}
	HRESULT __stdcall CList::MoveNext(int *result)
	{
		if (iter == List.rbegin()) *result = 0;
		else
		{
			iter++;
			*result = 1;
		}
		return S_OK;
	}
	HRESULT __stdcall CList::GetCurrent(Object *obj)
	{
		if (iter != List.rend()) *obj = *iter;
		return S_OK;
	}

 IUnknown * CreateInstance()
	{
		IUnknown* pI = static_cast<ICollection*>(new CList);
		pI->AddRef();
		return pI;
	}

 
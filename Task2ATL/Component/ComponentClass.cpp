// ComponentClass.cpp: реализация CComponentClass

#include "stdafx.h"
#include "ComponentClass.h"


// CComponentClass



STDMETHODIMP CComponentClass::Add(DOUBLE value)
{

	List.push_back(value);
	return S_OK;
}


STDMETHODIMP CComponentClass::Remove(DOUBLE value)
{

	List.remove(value);
	return S_OK;
}


STDMETHODIMP CComponentClass::GetData(SAFEARRAY** _array)
{

	//c SAVEARRAY удобно работать в <atlsafe.h> и использовать класс CComSafeArray Метод dtouch
	CComSafeArray<double> arr;
	int i = 0;
	for (auto it : List)
	{
		arr.Add(it);

	}
	*_array = arr.Detach();
	return S_OK;
}


STDMETHODIMP CComponentClass::get_Count(ULONG* pVal)
{
	*pVal = List.size();
	return S_OK;
}


STDMETHODIMP CComponentClass::get_Mean(DOUBLE* pVal)
{

	int i = 0;
	double sum = 0;
	for (auto it : List)
	{
		sum += it;
	}
	*pVal = sum / List.size();
	return S_OK;
}

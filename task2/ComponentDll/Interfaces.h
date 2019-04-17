#pragma once
#include <objbase.h>

//////////////////////////////////////////////////////////////////////////
// Тип объекта

	enum ObjectType
	{
		// целый
		otInt,

		// вещественный
		otDouble,

		// массив
		otArray
	};

	//////////////////////////////////////////////////////////////////////////
	// Объект - значение произвольного типа (предварительное объявление)

	struct Object;

	//////////////////////////////////////////////////////////////////////////
	// ObjectArray - Массив значений Object

	struct ObjectArray
	{
		// элементы массива
		Object *Data;

		// количество элементов массива
		unsigned Count;
	};

	//////////////////////////////////////////////////////////////////////////
	// Объект - значение произвольного типа

	struct Object
	{
		// тип объекта
		ObjectType Type;

		union
		{
			// значение целого типа
			int Int;

			// значение вещественного типа
			double Double;

			// значение типа "массив"
			ObjectArray *Array;
		} Value;
	};

	//////////////////////////////////////////////////////////////////////////
	// Интерфейс коллекции
	// {19BA0FC9-BF47-4B9F-81A0-BB9AF682C803}
	static const GUID IID_ICollection =
	{ 0x19ba0fc9, 0xbf47, 0x4b9f, { 0x81, 0xa0, 0xbb, 0x9a, 0xf6, 0x82, 0xc8, 0x3 } };



	interface ICollection : public IUnknown
	{
		// добавить элемент в коллекцию
		virtual HRESULT __stdcall Add(Object obj) = 0;

		// удалить элемент из коллекции
		virtual HRESULT __stdcall Remove(Object obj) = 0;

		// получить количество элементов коллекции
		virtual HRESULT __stdcall GetCount(unsigned *count) = 0;

		// преобразовать коллекцию в массив
		virtual HRESULT __stdcall ToArray(ObjectArray **arr) = 0;
	};


	//////////////////////////////////////////////////////////////////////////
	// Интерфейс перечислителя
	// {F2A3F03A-E4F5-4F0A-810B-0EC5A4BD3010}
	static const GUID IID_IEnumerator =
	{ 0xf2a3f03a, 0xe4f5, 0x4f0a, { 0x81, 0xb, 0xe, 0xc5, 0xa4, 0xbd, 0x30, 0x10 } };

	interface IEnumerator : public IUnknown
	{
		// возврат в исходное состояние
		virtual HRESULT __stdcall Reset() = 0;

		// переход к следующему элементу
		virtual HRESULT __stdcall MoveNext(int *result) = 0;

		// получить текущий элемент
		virtual HRESULT __stdcall GetCurrent(Object *obj) = 0;
	};

	//////////////////////////////////////////////////////////////////////////
	// {9078CF16-5D0B-4D59-B601-39813B9E06D7}
	static const GUID CLSID_CList =
	{ 0x9078cf16, 0x5d0b, 0x4d59, { 0xb6, 0x1, 0x39, 0x81, 0x3b, 0x9e, 0x6, 0xd7 } };

	
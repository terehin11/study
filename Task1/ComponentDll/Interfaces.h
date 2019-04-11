#pragma once
#include <objbase.h>

//////////////////////////////////////////////////////////////////////////
// “ип объекта

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
	// ќбъект - значение произвольного типа (предварительное объ€вление)

	struct Object;

	//////////////////////////////////////////////////////////////////////////
	// ObjectArray - ћассив значений Object

	struct ObjectArray
	{
		// элементы массива
		Object *Data;

		// количество элементов массива
		unsigned Count;
	};

	//////////////////////////////////////////////////////////////////////////
	// ќбъект - значение произвольного типа

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
	// »нтерфейс коллекции
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
	// »нтерфейс перечислител€
	// {F2A3F03A-E4F5-4F0A-810B-0EC5A4BD3010}
	static const GUID IID_IEnumerator =
	{ 0xf2a3f03a, 0xe4f5, 0x4f0a, { 0x81, 0xb, 0xe, 0xc5, 0xa4, 0xbd, 0x30, 0x10 } };

	interface IEnumerator : public IUnknown
	{
		// возврат в исходное состо€ние
		virtual HRESULT __stdcall Reset() = 0;

		// переход к следующему элементу
		virtual HRESULT __stdcall MoveNext(int *result) = 0;

		// получить текущий элемент
		virtual HRESULT __stdcall GetCurrent(Object *obj) = 0;
	};


	//////////////////////////////////////////////////////////////////////////
	// “ип функции создани€ экземпл€ра компонента

	typedef IUnknown* (*CREATEINSTANCEPROC)();


	//////////////////////////////////////////////////////////////////////////
	// Ёкспортируема€ функци€ создани€ экземпл€ра компонента

	extern "C" __declspec(dllexport) IUnknown* CreateInstance();


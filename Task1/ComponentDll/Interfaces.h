#pragma once
#include <objbase.h>

//////////////////////////////////////////////////////////////////////////
// ��� �������

	enum ObjectType
	{
		// �����
		otInt,

		// ������������
		otDouble,

		// ������
		otArray
	};

	//////////////////////////////////////////////////////////////////////////
	// ������ - �������� ������������� ���� (��������������� ����������)

	struct Object;

	//////////////////////////////////////////////////////////////////////////
	// ObjectArray - ������ �������� Object

	struct ObjectArray
	{
		// �������� �������
		Object *Data;

		// ���������� ��������� �������
		unsigned Count;
	};

	//////////////////////////////////////////////////////////////////////////
	// ������ - �������� ������������� ����

	struct Object
	{
		// ��� �������
		ObjectType Type;

		union
		{
			// �������� ������ ����
			int Int;

			// �������� ������������� ����
			double Double;

			// �������� ���� "������"
			ObjectArray *Array;
		} Value;
	};

	//////////////////////////////////////////////////////////////////////////
	// ��������� ���������
	// {19BA0FC9-BF47-4B9F-81A0-BB9AF682C803}
	static const GUID IID_ICollection =
	{ 0x19ba0fc9, 0xbf47, 0x4b9f, { 0x81, 0xa0, 0xbb, 0x9a, 0xf6, 0x82, 0xc8, 0x3 } };



	interface ICollection : public IUnknown
	{
		// �������� ������� � ���������
		virtual HRESULT __stdcall Add(Object obj) = 0;

		// ������� ������� �� ���������
		virtual HRESULT __stdcall Remove(Object obj) = 0;

		// �������� ���������� ��������� ���������
		virtual HRESULT __stdcall GetCount(unsigned *count) = 0;

		// ������������� ��������� � ������
		virtual HRESULT __stdcall ToArray(ObjectArray **arr) = 0;
	};


	//////////////////////////////////////////////////////////////////////////
	// ��������� �������������
	// {F2A3F03A-E4F5-4F0A-810B-0EC5A4BD3010}
	static const GUID IID_IEnumerator =
	{ 0xf2a3f03a, 0xe4f5, 0x4f0a, { 0x81, 0xb, 0xe, 0xc5, 0xa4, 0xbd, 0x30, 0x10 } };

	interface IEnumerator : public IUnknown
	{
		// ������� � �������� ���������
		virtual HRESULT __stdcall Reset() = 0;

		// ������� � ���������� ��������
		virtual HRESULT __stdcall MoveNext(int *result) = 0;

		// �������� ������� �������
		virtual HRESULT __stdcall GetCurrent(Object *obj) = 0;
	};


	//////////////////////////////////////////////////////////////////////////
	// ��� ������� �������� ���������� ����������

	typedef IUnknown* (*CREATEINSTANCEPROC)();


	//////////////////////////////////////////////////////////////////////////
	// �������������� ������� �������� ���������� ����������

	extern "C" __declspec(dllexport) IUnknown* CreateInstance();



// DynamicWavePacket.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CDynamicWavePacketApp:
// � ���������� ������� ������ ��. DynamicWavePacket.cpp
//

class CDynamicWavePacketApp : public CWinApp
{
public:
	CDynamicWavePacketApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CDynamicWavePacketApp theApp;
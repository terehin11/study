
// DynamicWavePacket.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CDynamicWavePacketApp:
// О реализации данного класса см. DynamicWavePacket.cpp
//

class CDynamicWavePacketApp : public CWinApp
{
public:
	CDynamicWavePacketApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CDynamicWavePacketApp theApp;
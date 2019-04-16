
// ParticleDrift.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CParticleDriftApp:
// Сведения о реализации этого класса: ParticleDrift.cpp
//

class CParticleDriftApp : public CWinApp
{
public:
	CParticleDriftApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CParticleDriftApp theApp;


// MagneticRing.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CMagneticRingApp:
// Сведения о реализации этого класса: MagneticRing.cpp
//

class CMagneticRingApp : public CWinApp
{
public:
	CMagneticRingApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMagneticRingApp theApp;


// Shredinger.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CShredingerApp:
// Сведения о реализации этого класса: Shredinger.cpp
//

class CShredingerApp : public CWinApp
{
public:
	CShredingerApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CShredingerApp theApp;

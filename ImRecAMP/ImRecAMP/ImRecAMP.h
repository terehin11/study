
// ImRecAMP.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CImRecAMPApp:
// Сведения о реализации этого класса: ImRecAMP.cpp
//

class CImRecAMPApp : public CWinApp
{
public:
	CImRecAMPApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CImRecAMPApp theApp;

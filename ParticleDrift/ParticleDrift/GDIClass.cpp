#include "stdafx.h"
#include "GDIClass.h"
#include "ParticleDrift.h"
#include "ParticleDriftDlg.h"
using namespace Gdiplus;
IMPLEMENT_DYNAMIC(GDIClass, CStatic)
ULONG_PTR gdiPlusToken;
GDIClass::GDIClass()
{
	GdiplusStartupInput gdiPlusStartapInput;
	if (GdiplusStartup(&gdiPlusToken, &gdiPlusStartapInput, NULL) != Ok)
	{
		MessageBox(L"Init error", L"Error Message", MB_OK);
		exit(0);
	}
}
GDIClass::~GDIClass()
{
	GdiplusShutdown(gdiPlusToken);
}

BEGIN_MESSAGE_MAP(GDIClass, CStatic)
END_MESSAGE_MAP()

 void GDIClass::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	 Graphics g(lpDrawItemStruct->hDC);
	 Bitmap Map(lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left + 1,
		 lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top + 1,
		 &g);
	 Graphics g2(&Map);

	 g2.SetSmoothingMode(SmoothingModeAntiAlias);

	 g2.Clear(Color::Green);
	 g.DrawImage(&Map, 0, 0);
}



// обработчики сообщений KLASS
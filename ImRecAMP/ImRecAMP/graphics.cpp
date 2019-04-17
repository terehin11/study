#include "stdafx.h"
#include "graphics.h"
#include "vector"



ULONG_PTR token;

IMPLEMENT_DYNAMIC(graphics, CStatic);

graphics::graphics()
{
	GdiplusStartupInput input;
	Status s;
	s = GdiplusStartup(&token, &input, NULL);
	if (s != Ok)
	{
		MessageBox(L"Error", L"", MB_OK | MB_ICONERROR);
	}
	width = 0;
	height = 0;
}


graphics::~graphics()
{
	GdiplusShutdown(token);
}
BEGIN_MESSAGE_MAP(graphics, CStatic)
END_MESSAGE_MAP()

//Функция получения размера Picture Control
Rect graphics::GetRect(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Rect  wndRect(
		0,
		0,
		lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left + 1,
		lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top + 1);
	return wndRect;
}


void graphics::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	Graphics gr(lpDrawItemStruct->hDC);

	Rect wndRect = GetRect(lpDrawItemStruct);

	if (img)
	{
		gr.DrawImage(im, wndRect);
	}

	if (noiseDraw)
	{

		gr.DrawImage(noiseIm, wndRect);
	}
	if (noiseFiltr)
	{
		gr.DrawImage(filtrIm, wndRect);
	}

}






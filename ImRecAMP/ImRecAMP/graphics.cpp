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

	im = nullptr;
}

graphics::~graphics()
{
	delete im;
	GdiplusShutdown(token);
}

BEGIN_MESSAGE_MAP(graphics, CStatic)
END_MESSAGE_MAP()

void graphics::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Graphics gr(lpDrawItemStruct->hDC);
	Rect  wndRect(
		0,
		0,
		lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left + 1,
		lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top + 1);

	if (im != nullptr)
	{
		gr.DrawImage(im, wndRect);
	}
}

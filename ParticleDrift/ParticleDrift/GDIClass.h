#pragma once
#include <afxwin.h>
class GDIClass :
	public CStatic
{
	//////////////////////////////////////////
	DECLARE_DYNAMIC(GDIClass)
public:
	GDIClass();
	virtual ~GDIClass();
	virtual void DrawItem(LPDRAWITEMSTRUCT);
private:
protected:
	DECLARE_MESSAGE_MAP()
	//////////////////////////////////////////


};


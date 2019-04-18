#pragma once

using namespace std;
using namespace Gdiplus;

//��������� �����
struct MyRGB
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
};

class graphics: public CStatic
{
	//===========================================================================================
	/////////////////////////////////////�������/////////////////////////////////////////////////
	Bitmap *im;
	//============================================================================================

	DECLARE_DYNAMIC(graphics);

	void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);

public:
	graphics();
	~graphics();
	//===========================================================================================
	////////////////////////////////////������///////////////////////////////////////////////////

	void SetBitmap(Bitmap *bmp)
	{
		if (im != nullptr) delete im;
		im = bmp;
		Invalidate(FALSE);
	}

	//===========================================================================================

protected:
	DECLARE_MESSAGE_MAP();
};


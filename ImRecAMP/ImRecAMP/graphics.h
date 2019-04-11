#pragma once
using namespace std;


using namespace Gdiplus;
struct MyRGB
{
	unsigned R;//uchar потому что диапазон его от 0 до 255. –азмер 8 байт.
	unsigned G;
	unsigned B;
};
class graphics: public CStatic
{
	DECLARE_DYNAMIC(graphics);

public:
	graphics();
	~graphics();
	void Noise(unsigned *ptr);
	Rect GetRect(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	void GetWeightHeight(Bitmap image);
	void Med_Filtr(unsigned* ptr,  unsigned* prtFiltr);
	Rect copy_rect;
	bool noiseDraw;
	bool noiseFiltr;
	bool img;
	double noise;
	MyRGB randRGB();
	int width;
	int height;
	void mepaint()
	{
		Invalidate();
	}
	//int height;
	//int weight;
protected:
	DECLARE_MESSAGE_MAP();
};


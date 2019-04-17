#pragma once
using namespace std;


using namespace Gdiplus;

//структура цвета
struct MyRGB
{
	unsigned R;
	unsigned G;
	unsigned B;
};
class graphics: public CStatic
{
	DECLARE_DYNAMIC(graphics);

public:
	graphics();
	~graphics();
	//===========================================================================================
	////////////////////////////////////Методы///////////////////////////////////////////////////

	Rect GetRect(LPDRAWITEMSTRUCT lpDrawItemStruct);//Функция получения размера Picture Control
	void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);

	void mepaint()//функция для вызова DrawItems 
	{
		Invalidate();
	}
	//===========================================================================================

	//===========================================================================================
	/////////////////////////////////////Объекты/////////////////////////////////////////////////
	bool noiseDraw;//для рисования зашумленного изображения
	bool noiseFiltr;//для рисования восстановленного изображения 
	bool img;//для рисования исходного изображения

	Image *im;
	Bitmap* noiseIm;
	Bitmap* filtrIm;
	int width;
	int height;
	//============================================================================================

protected:
	DECLARE_MESSAGE_MAP();
};


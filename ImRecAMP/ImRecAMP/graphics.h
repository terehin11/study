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
	void Noise(unsigned *ptr);//Функция зашумления
	Rect GetRect(LPDRAWITEMSTRUCT lpDrawItemStruct);//Функция получения размера Picture Control
	void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	void GetWeightHeight(Bitmap image);
	void Med_Filtr(unsigned* ptr,  unsigned* prtFiltr);//Функция Медианного фильтра
	unsigned randRGB();//функция получения случайного значения цвета
	void mepaint()//функция для вызова DrawItems 
	{
		Invalidate();
	}
	//===========================================================================================

	//===========================================================================================
	/////////////////////////////////////Объекты/////////////////////////////////////////////////
	Rect copy_rect;//размер окна
	bool noiseDraw;//для рисования зашумленного изображения
	bool noiseFiltr;//для рисования восстановленного изображения 
	bool img;//для рисования исходного изображения
	double noise;//коэффициент шума
	Image *im;
	Bitmap* noiseIm;
	int width;
	int height;
	//============================================================================================

protected:
	DECLARE_MESSAGE_MAP();
};


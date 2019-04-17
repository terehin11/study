#pragma once
using namespace std;


using namespace Gdiplus;

//��������� �����
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
	////////////////////////////////////������///////////////////////////////////////////////////

	Rect GetRect(LPDRAWITEMSTRUCT lpDrawItemStruct);//������� ��������� ������� Picture Control
	void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);

	void mepaint()//������� ��� ������ DrawItems 
	{
		Invalidate();
	}
	//===========================================================================================

	//===========================================================================================
	/////////////////////////////////////�������/////////////////////////////////////////////////
	bool noiseDraw;//��� ��������� ������������ �����������
	bool noiseFiltr;//��� ��������� ���������������� ����������� 
	bool img;//��� ��������� ��������� �����������

	Image *im;
	Bitmap* noiseIm;
	Bitmap* filtrIm;
	int width;
	int height;
	//============================================================================================

protected:
	DECLARE_MESSAGE_MAP();
};


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
	void Noise(unsigned *ptr);//������� ����������
	Rect GetRect(LPDRAWITEMSTRUCT lpDrawItemStruct);//������� ��������� ������� Picture Control
	void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	void GetWeightHeight(Bitmap image);
	void Med_Filtr(unsigned* ptr,  unsigned* prtFiltr);//������� ���������� �������
	unsigned randRGB();//������� ��������� ���������� �������� �����
	void mepaint()//������� ��� ������ DrawItems 
	{
		Invalidate();
	}
	//===========================================================================================

	//===========================================================================================
	/////////////////////////////////////�������/////////////////////////////////////////////////
	Rect copy_rect;//������ ����
	bool noiseDraw;//��� ��������� ������������ �����������
	bool noiseFiltr;//��� ��������� ���������������� ����������� 
	bool img;//��� ��������� ��������� �����������
	double noise;//����������� ����
	Image *im;
	Bitmap* noiseIm;
	int width;
	int height;
	//============================================================================================

protected:
	DECLARE_MESSAGE_MAP();
};



// ImRecAMPDlg.h: файл заголовка
//

#pragma once

#include "graphics.h"
#include <vector>
using namespace std;
// Диалоговое окно CImRecAMPDlg

class CImRecAMPDlg : public CDialogEx
{
// Создание
public:
	CImRecAMPDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMRECAMP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	struct MyRGB
	{
		unsigned R;
		unsigned G;
		unsigned B;
	};
//////////////////////////////////////////////////////////
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	void DrawRealImage();
	void DrawNoiseImage();
	void Noise(unsigned* ptr);
	bool RandomBool(double ver);
	unsigned randRGB();
	Status Lock(BitmapData bd, Bitmap* bmp, Rect rect);
	Status Unlock(BitmapData bd, Bitmap* bmp);
//////////////////////////////////////////////////////////
	graphics drawItemsReal;
	graphics drawItemsNoise;
	graphics drawItemsFiltr;
	CStatic mainWindow;
	int noise;
	bool OnOff;
	int width;
	int height;
	Rect copy_rect;
	Bitmap* copy;
	Status st;
	Gdiplus::BitmapData noiseBitmapData;
	unsigned* ptrFirstPixelNoise;

};

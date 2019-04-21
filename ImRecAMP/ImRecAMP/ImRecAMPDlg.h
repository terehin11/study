
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
//////////////////////////////////////////////////////////
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	void DrawRealImage();
	void DrawNoiseImage();
	void DrawFiltrImage();
	void DrawFiltrAMPImage();
	void Noise(unsigned* ptr);
	unsigned randRGB();
	void Med_Filtr(unsigned* ptrNoise, unsigned* prtFiltr);
	void Med_FiltrAMP(unsigned* ptrNoise, unsigned* prtFiltr);
	Status Lock(BitmapData &bd, Bitmap* bmp, Rect rect);
	Status Unlock(BitmapData &bd, Bitmap* bmp);
	void SortSel(vector<MyRGB>& A);
//////////////////////////////////////////////////////////
	graphics drawItemsReal;
	graphics drawItemsNoise;
	graphics drawItemsFiltr;

	int noise;

	int width;
	int height;
	int width_window;
	int height_window;
	Rect copy_rect;
	
	Bitmap *original;
	Bitmap* copy;
	Bitmap* copy_filtr;
	
	Gdiplus::BitmapData noiseBitmapData;
	Gdiplus::BitmapData filtrBitmapData;
	unsigned* ptrFirstPixelNoise;
	unsigned* ptrFirstPixelFiltr;


	afx_msg void OnBnClickedButton4();
	double time_study_proc;
	double time_study_accel;
	int size_study;
	afx_msg void OnBnClickedButton5();
};

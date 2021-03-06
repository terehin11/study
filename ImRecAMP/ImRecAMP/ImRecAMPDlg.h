
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
	void Noise(unsigned* ptr);
	unsigned randRGB();
	void Med_Filtr(unsigned* ptrNoise, unsigned* prtFiltr);
	void Med_FiltrAMP(unsigned* ptrNoise, unsigned* prtFiltr, int width, int width_window,  int height_window, int height);
	Status Lock(BitmapData &bd, Bitmap* bmp, Rect rect);
	Status Unlock(BitmapData &bd, Bitmap* bmp);
	void SortSel(vector<MyRGB>& A); 
	//void SortSel(unsigned * R, unsigned* G, unsigned* B, int size) restrict(amp);
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

	bool Amp;
	afx_msg void OnBnClickedButton4();
	double time_study_proc;
	double time_study_accel;
	int size_study;
	afx_msg void OnBnClickedButton5();
	CProgressCtrl ready_study;
	BOOL GP;
	BOOL CP;
	CButton GP_B;
	CButton CP_B;
	afx_msg void OnBnClickedGp();
	afx_msg void OnBnClickedCp();
};

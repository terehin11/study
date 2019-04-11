
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
	CStatic mainWindow;
	//graphics graf;
	afx_msg void OnBnClickedButton1();
	//CStataic mainWind;
	graphics drawItemsReal;
	graphics drawItemsNoise;
	graphics drawItemsFiltr;

	int noise;
	afx_msg void OnBnClickedButton2();
	bool OnOff;
	void Median_filter();
	void quickSort(vector<unsigned> numbers, unsigned left, unsigned right);
	afx_msg void OnBnClickedButton3();
	LPDRAWITEMSTRUCT lpd1;
};


// DynamicWavePacketDlg.h : файл заголовка
//
#include "hFunctions.h"
#include <vector>
#include "afxcmn.h"
using namespace std;
#pragma once

//struct Complex
//{
//	double real;
//	double image;
//};

// диалоговое окно CDynamicWavePacketDlg
class CDynamicWavePacketDlg : public CDialogEx
{
// Создание
public:
	CDynamicWavePacketDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_DYNAMICWAVEPACKET_DIALOG };

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
	//Переменные рисования
	// объекты класса CWnd
	CWnd * PicWndMult;
	// объекты класса CDC
	CDC * PicDcMult;
	// объекты класса CRect
	CRect PicMult;
	
	CWnd * PicWndMult2;
	// объекты класса CDC
	CDC * PicDcMult2;
	// объекты класса CRect
	CRect PicMult2;

	CWnd * PicWndMult3;
	// объекты класса CDC
	CDC * PicDcMult3;
	// объекты класса CRect
	CRect PicMult3;
	//Переменные для работы с масштабом
	double xp1, yp1,        // коэфициенты пересчета
		xmin1, xmax1,	    // максисимальное и минимальное значение х1 
		ymin1, ymax1;       // максисимальное и минимальное значение y1


	double xp2, yp2,        // коэфициенты пересчета
		xmin2, xmax2,	    // максисимальное и минимальное значение х1 
		ymin2, ymax2;       // максисимальное и минимальное значение y1

	double xp3, yp3,        // коэфициенты пересчета
		xmin3, xmax3,	    // максисимальное и минимальное значение х2 
		ymin3, ymax3;       // максисимальное и минимальное значение y2
	//ручки
	CPen osi_pen;
	CPen setka_pen;
	CPen graf_pen;
	CPen graf_pen1;
	CPen graf_penred;
	CPen graf_pengreen;
	CPen graf_penblue;


	
	
	Complex calc_wave_function(double amplitude, double math_expec, double disp, double x);
	
	int dotscount_psi;
	double R;
	double amplitude;
	double math_expec;
	double disp;
	double step_psi;
	double step_time;
	int countOf_t;
	int infinite = 10000; 
	int timerTick;
	vector<double> uPot;
	vector<Complex> psiOneImg;
	vector<Complex> psi;
	vector<vector<Complex>> WEB;
	vector<vector <Complex>> WEB_FURIE;
	vector<Complex> wave_function;

	Complex a;
	Complex b;
	vector<Complex> c;
	vector<Complex> d;

	vector<Complex> alfa;
	vector<Complex> betta;
	vector<Complex> furie;

	void u_Pot(double alpha, double beta, int r);
	double u_Pot2(double x);

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl sliderCtrl1;
	CSliderCtrl sliderCtrl2;
	bool calc;
	
	afx_msg void OnBnClickedButton4();
	int positionSlider1;
	int positionSlider2;
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	double alfa1;
	double beta;
};

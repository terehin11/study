
// DynamicsWaveProcessDlg.h: файл заголовка
//
#include "HeaderFunctions.h"
#include <cmath>
#pragma once
using namespace std;

// Диалоговое окно CDynamicsWaveProcessDlg
class CDynamicsWaveProcessDlg : public CDialogEx
{
// Создание
public:
	CDynamicsWaveProcessDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DYNAMICSWAVEPROCESS_DIALOG };
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
	//ТАЙМЕР
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	UINT_PTR timer_ptr;      // объект таймера
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CSliderCtrl slid1;
	CSliderCtrl slid2;
	int positionSlider1;
	int positionSlider2;

	// объекты класса CWnd
	CWnd * PicWndMult1;
	// объекты класса CDC
	CDC * PicDcMult1;
	// объекты класса CRect
	CRect PicMult1;
	//Переменные для работы с масштабом
	double xp1, yp1,
		xmin1, xmax1,
		ymin1, ymax1;

	CWnd * PicWndMult2;
	// объекты класса CDC
	CDC * PicDcMult2;
	// объекты класса CRect
	CRect PicMult2;

	double xp2, yp2,
		xmin2, xmax2,
		ymin2, ymax2;

	CWnd * PicWndMult3;
	// объекты класса CDC
	CDC * PicDcMult3;
	// объекты класса CRect
	CRect PicMult3;

	double xp3, yp3,
		xmin3, xmax3,
		ymin3, ymax3;

	//ручки
	CPen osi_pen;
	CPen setka_pen;
	CPen graf_pen;
	CPen graf_pen1;
	CPen graf_penred;
	CPen graf_pengreen;
	CPen graf_penblue;


	double R;
	int dotscountR;
	double Step;
	double TimeStep;
	int dotscountTime;

	vector<vector <vector <Complex>>> ksi; //Сетка эволюции волнового пакета
	vector<vector <vector <Complex>>> ksi_second; //Сетка эволюции волнового пакета
	vector<vector <vector <Complex>>> data_fur; //Сетка Фурье эволюции волнового пакета

	vector <vector <Complex>> ksi_start; // Нулевой волновой пакет
	vector <vector <double>> wave_pakage; //Массив отрисовки волнового пакета
	vector <Complex> Furie;
	vector <vector <double>> u; //распределение потенциала
	vector <vector <double>> WaveFunc;
	double V0; //высота ям/ямы
	int num_wave_pak;//номер итерации эволюции волнового пакета по времени

	bool on1, on2;

	void UPot(int diametr, double V0); //функция распределения потенциала;
	void PsiPot(double a, double b);
	double Max(vector<double> Mass);
	double Max(vector<Complex> Mass);
	double Min(vector<double> Mass);
	double Min(vector<Complex> Mass);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl slid3;
	int positionSlider3;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void Risunok(CDC *PicDc, vector<vector <double>> Mass, int xmin, int xmax, int ymin, int ymax, double xp,double yp);
	int param1;
	int kupx0;
	int kupy0;
	afx_msg void OnBnClickedButton3();
};

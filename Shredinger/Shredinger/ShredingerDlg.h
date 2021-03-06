
// ShredingerDlg.h: файл заголовка
//

#pragma once
#include <vector>
#include <cmath>
using namespace std;
// Диалоговое окно CShredingerDlg
class CShredingerDlg : public CDialogEx
{
// Создание
public:
	CShredingerDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHREDINGER_DIALOG };
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
	//Переменные рисования
// объекты класса CWnd
	CWnd * PicWndMult;
	// объекты класса CDC
	CDC * PicDcMult;
	// объекты класса CRect
	CRect PicMult;
	//Переменные для работы с масштабом
	double xp1, yp1,        // коэфициенты пересчета
		xmin1, xmax1,	    // максисимальное и минимальное значение х1 
		ymin1, ymax1;       // максисимальное и минимальное значение y1

	CWnd * PicWndMult2;
	// объекты класса CDC
	CDC * PicDcMult2;
	// объекты класса CRect
	CRect PicMult2;

	double xp2, yp2,        // коэфициенты пересчета
		xmin2, xmax2,	    // максисимальное и минимальное значение х1 
		ymin2, ymax2;       // максисимальное и минимальное значение y1
		//ручки
	CPen osi_pen;
	CPen setka_pen;
	CPen graf_pen;
	CPen graf_pen1;
	CPen graf_penred;
	CPen graf_pengreen;
	CPen graf_penblue;
	///////////////////////////////////////////////
	double R; //бесконечность не предел
	vector <double> u; //распределение потенциала
	vector <double> fi; //Текущее значение распределения фазовой функции
	vector <double> fi_past;//предыдущее распределение фазовой функции
	vector <double> Fre;
	vector <double> MasEnergy;
	vector <double> r;
	vector <double> Wave_function;
	int dotscount; //количество точек
	int dotscountEnergy;
	double step; //шаг по длине 
	double BufE; //значение энергии для count_difference
	double error;
	double V0;// высота барьера
	double UPot(double x); //функция распределения потенциала
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	double Emin;
	double Emax;
	int kolvoHoles;
	int Kmax;
	afx_msg void OnBnClickedOk2();
	int k_value;
	bool WaveType;
	void Upot(double alpha, double beta, int r);
	double amplituda;
	double mat_expec;
	double dis;
	vector<vector<double>> wave_packet;
	double calc_wave_fuc(double amplituda, double mat_expec, double dis, int x);
	bool OnOff;
	int countOf_t;
	double alpha;
	double beta;
	afx_msg void OnBnClickedOk3();
};

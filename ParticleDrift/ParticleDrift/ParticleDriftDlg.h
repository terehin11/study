
// ParticleDriftDlg.h: файл заголовка
//

#pragma once
#include <time.h>
#include "math.h"
#include <ctime>
#include <string>
#include <cmath>
#include <vector>
#include "GDIClass.h" //GDICLASS
#define M_PI 3.1415926535897932384626433832795
using namespace std;
// Диалоговое окно CParticleDriftDlg
class CParticleDriftDlg : public CDialogEx
{
// Создание
public:
	CParticleDriftDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARTICLEDRIFT_DIALOG };
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
	int DotsCount;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	struct Dot //точка
	{
		double x1, y1, z1 = 0; //координаты
		bool lock = 1; // 1- точка сверхструктуры, 0 - точка сетки
		double Q = 0; //заряд в точке по начальным условиям
		int index; //индекс точки
		vector <int> neighbors;
	};
	struct Tringl //треугольник
	{
		Dot T1, T2, T3;//точки
		double RadiusO; //радиус описанной окружности
		Dot C;// центр описанной окружности 
	};
	struct Voronoi
	{
		vector <Dot> V;
	};


	double xp1, yp1,        // коэфициенты пересчета
		xmin1, xmax1,	    // максисимальное и минимальное значение первое окошко
		ymin1, ymax1;       // максисимальное и минимальное значение первое окошко

	// объекты класса CWnd
	CWnd * PicWndSignal1;

	// объекты класса CDC
	CDC * PicDcSignal1;

	// объекты класса CRect
	CRect PicSignal1;

	double xp2, yp2,        // коэфициенты пересчета
		xmin2, xmax2,	    // максисимальное и минимальное значение первое окошко
		ymin2, ymax2;       // максисимальное и минимальное значение первое окошко

	// объекты класса CWnd
	CWnd * PicWndSignal2;

	// объекты класса CDC
	CDC * PicDcSignal2;

	// объекты класса CRect
	CRect PicSignal2;
	//ручки
	CPen osi_pen;
	CPen setka_pen;
	CPen graf_pen;
	CPen graf_pen1;
	CPen graf_penred;
	CPen graf_pengreen;
	CPen graf_penblue;

	double Qmax, Qmin;
	//=====================================================================
//ФУНКЦИИ проверки принадлежности точки многоугольнику
	double getAzimuth(const Dot o, const Dot p) {
		return atan2(p.y1 - o.y1, p.x1 - o.x1);
	}

	double getAngle(const Dot o, const Dot a, const Dot b) {
		double result = getAzimuth(o, b) - getAzimuth(o, a);
		if (result > M_PI) result -= 2 * M_PI;
		if (result < -M_PI) result += 2 * M_PI;
		return result;
	}

	bool isInside(vector<Dot> P, const Dot p, unsigned n) {
		double sum = getAngle(p, P[n - 1], P[0]);
		while (--n) {
			sum += getAngle(p, P[n - 1], P[n]);
		}
		return fabs(sum) > 1e-10;
	}
	//========================================================================
	vector <Dot> GiperDot;
	vector <Dot> DeloneDot;
	vector <Tringl> Treug; //вектор треугольников(всех)
	vector < Voronoi> Polygons;
	void generator(vector <Dot> Koor, vector<Tringl> &Treg, bool lock);//функция построения треангуляции перебором
	void KoorCenter(Dot T1, Dot T2, Dot T3, Dot &TC);
	double RadiusOkr(Dot TC, Dot T);
	bool EquallyDots(Dot dot1, Dot dot2);//функция совпадения точек
	afx_msg void OnBnClickedButton1();
	void BubleSortAtan(vector<pair<Dot, double>> &A);
	CStatic mainwindow;
	//GDIClass drawItems; //GDICLASS
	double gran;
	double gransetka;
	vector <Dot> FullDots; //массив всех точек триангуляции
	vector <Dot> UnicFullDots;
	void FindUnicDots(vector<Dot> mas1, vector<Dot> &mas2);//функция поиска уникальных точек
	bool AddNewNeighbors(Dot &dot1, Dot dot2); // добавление соседа одной точке к другой
	void Coff_A(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double &AI, double &BI);
	void Coff_B(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double &AJ, double &BJ);
	double Coff_A_B(int i, int j, int h);
	void Galerkin(vector<double> &BJ, vector<double> &A, vector<Tringl>Treugol);
	void kazf(vector<double> a, vector<double> b, vector<double>  &x, int nn, int ny);
	double polygon_area(vector<Dot> poly);//Поиск площади многоугольника
	vector<double>A;
	vector<double>Bj;
	vector<double>c;//распределение Q (возвращается из kazf)
	//======================================================================== 
	//Генерация частиц
	//======================================================================== 
	//ТАЙМЕР
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	UINT_PTR timer_ptr;      // объект таймера
	struct bit
	{
		Dot koor;
		double Q = 0.5;
		double speedY=0;
		double speedX=0;
	};
	double TimeStep;
	vector <bit> bits;
	int bitscount;
	afx_msg void OnBnClickedButton2();
	//Генерация ВАХ
	void TimerFunc();
	vector<double>VAH;
	double bufferVAH;
	double ETimer;//текущее значение E внутри Таймера
	double Etest;//тестовое значение E поля
	double Emin;//минимальное значение E поля
	double Emax; //максимальное значение E поля
	double Edots; //кол-во эксперемнтов
	//int tics_count = 256;//максимальное время, до которого будет работать таймер
	BOOL paint_vor;
	int tics_count;
};

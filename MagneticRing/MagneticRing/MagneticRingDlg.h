
// MagneticRingDlg.h: файл заголовка
//

#pragma once
#include <vector>
#define M_PI 3.14159265359
using namespace std;
struct Dot
{
	double x;
	double y;
};

struct triang
{
	Dot center;
	double radius;
	Dot dot1;
	Dot dot2;
	Dot dot3;
	bool del = 1;
};

// Диалоговое окно CMagneticRingDlg
class CMagneticRingDlg : public CDialogEx
{
// Создание
public:
	CMagneticRingDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAGNETICRING_DIALOG };
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
	afx_msg void OnBnClickedButton1();


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
		//ручки
	CPen osi_pen;
	CPen setka_pen;
	CPen graf_pen;
	CPen graf_pen1;
	CPen graf_penred;
	CPen graf_pengreen;
	CPen graf_penblue;
	//Dot dot;
	vector<Dot> dot;
	vector<Dot> opora;
	vector<Dot> first;
	bool OnOff;
	bool OnOff1;
	bool OnOff2;
	int sizeDot;
	vector<Dot> cirDot;
	vector<Dot> cirDot1;
	vector<Dot> vnutr;
	vector<Dot> trianglDeleted;
	vector<Dot> newDots;
	double RandDots(double a, double b);
	void KoordCenter(Dot dot1, Dot dot2, Dot dot3, Dot &centrDots);
	double RadiusCircle(Dot centrDots, Dot dot);

	vector<triang> treugTriang;
	vector<triang> treugTriang1;
	vector<triang> buf;
	vector<triang> TrianglBust(vector<Dot> dots);
	vector<triang> TriangRecursive(vector<Dot> dots);
	void Search( Dot newDots, vector<triang> &treugTriang);

	afx_msg void OnBnClickedButton2();
	int L;
	int D;
	double R;
	vector<Dot> edges;
	afx_msg void OnBnClickedButton3();
	int alpha;
	double offsetX;
	double offsetY;
	//=====================================================================
//ФУНКЦИИ проверки принадлежности точки многоугольнику
	double getAzimuth(const Dot o, const Dot p) {
		return atan2(p.y - o.y, p.x - o.x);
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
};

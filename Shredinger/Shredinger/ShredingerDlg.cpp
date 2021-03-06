
// ShredingerDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "Shredinger.h"
#include "ShredingerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CShredingerDlg
#define KOORD(x,y) (xp1*((x)-xmin1)),(yp1*((y)-ymax1)) 
#define KOORD2(x,y) (xp2*((x)-xmin2)),(yp2*((y)-ymax2))
#define M_PI 3.1415926535
CShredingerDlg::CShredingerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHREDINGER_DIALOG, pParent)
	, R(4)
	, dotscount(500)
	, V0(10)
	, dotscountEnergy(100)
	, Emin(0)
	, Emax(10)
	, kolvoHoles(10)
	, Kmax(0)
	, k_value(0)
	, alpha(0.001)
	, beta(0.004)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShredingerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, R);
	DDX_Text(pDX, IDC_EDIT2, dotscount);
	//DDX_Text(pDX, IDC_EDIT4, V0);
	DDX_Text(pDX, IDC_EDIT5, dotscountEnergy);
	DDX_Text(pDX, IDC_EDIT7, Emin);
	DDX_Text(pDX, IDC_EDIT6, Emax);
	//DDX_Text(pDX, IDC_EDIT8, kolvoHoles);
	DDX_Text(pDX, IDC_EDIT9, Kmax);
	DDX_Text(pDX, IDC_EDIT10, k_value);
	DDX_Text(pDX, IDC_EDIT11, alpha);
	DDX_Text(pDX, IDC_EDIT12, beta);
}

BEGIN_MESSAGE_MAP(CShredingerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CShredingerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CShredingerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK2, &CShredingerDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDOK3, &CShredingerDlg::OnBnClickedOk3)
END_MESSAGE_MAP()


// Обработчики сообщений CShredingerDlg

BOOL CShredingerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	PicWndMult = GetDlgItem(IDC_STATIC);
	PicDcMult = PicWndMult->GetDC();
	PicWndMult->GetClientRect(&PicMult);

	PicWndMult2 = GetDlgItem(IDC_STATIC2);
	PicDcMult2 = PicWndMult2->GetDC();
	PicWndMult2->GetClientRect(&PicMult2);

	setka_pen.CreatePen(  //для сетки
		PS_DASH,    //сплошная линия
		//PS_DOT,     //пунктирная
		1,      //толщина 1 пиксель
		RGB(155, 155, 155));  //цвет серый

	osi_pen.CreatePen(   //координатные оси
		PS_SOLID,    //сплошная линия
		2,      //толщина 3 пикселя
		RGB(0, 150, 0));   //цвет черный

	graf_pen.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		2,      //толщина 2 пикселя
		RGB(200, 0, 0));   //цвет черный

	graf_pen1.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		2,      //толщина 2 пикселя
		RGB(0, 0, 0));   //цвет розовый

	graf_penred.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		2,      //толщина 2 пикселя
		RGB(255, 0, 0));   //цвет черный

	graf_pengreen.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		4,      //толщина 2 пикселя
		RGB(0, 150, 0));   //цвет черный

	graf_penblue.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		1,      //толщина 2 пикселя
		RGB(0, 0, 255));   //цвет черный

	u.resize(0);
	fi.resize(0);
	Fre.resize(0);
	WaveType = false;
	OnOff = false;

	xmax1 = dotscount;			//Максимальное значение х1
	ymax1 = 5;			//Максимальное значение y1
	xmin1 = 0;			//Минимальное значение х1
	ymin1 = -0.1*ymax1;			//Минимальное значение y1

	xmax2 = dotscount;			//Максимальное значение х1
	ymax2 = 5;			//Максимальное значение y1
	xmin2 = 0;			//Минимальное значение х1
	ymin2 = -0.1*ymax2;			//Минимальное значение y1


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CShredingerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		///////////////////////////////////////////////
		///////////////////////////////////////////////
		xp1 = ((double)(PicMult.Width()) / (xmax1 - xmin1));			// Коэффициенты пересчёта координат по x1
		yp1 = -((double)(PicMult.Height()) / (ymax1 - ymin1));       // Коэффициенты пересчёта координат по y1

		xp2 = ((double)(PicMult2.Width()) / (xmax2 - xmin2));			// Коэффициенты пересчёта координат по x2
		yp2 = -((double)(PicMult2.Height()) / (ymax2 - ymin2));       // Коэффициенты пересчёта координат по y2
		///////////////////////////////////////////////
		// для MULT
		PicDcMult->FillSolidRect(&PicMult, RGB(255, 255, 255));    // закрашиваем фон
		PicDcMult->SelectObject(&osi_pen);		// выбираем ручку

		//создаём Ось Y
		PicDcMult->MoveTo(KOORD(0, ymin1));
		PicDcMult->LineTo(KOORD(0, ymax1));
		//создаём Ось Х
		PicDcMult->MoveTo(KOORD(xmin1, 0));
		PicDcMult->LineTo(KOORD(xmax1, 0));

		PicDcMult->SelectObject(&graf_pen);		// выбираем ручку
		if (!OnOff)
		{
			if (!WaveType)
			{
				if (u.size() != 0)
				{
					PicDcMult->SelectObject(&graf_pen);		// выбираем ручку
					PicDcMult->MoveTo(KOORD(0, u[0]));

					for (int j = 0; j < u.size(); j++)
					{
						PicDcMult->LineTo(KOORD(j, u[j]));
					}
				}
			}
			else
			{
				if (Wave_function.size() != 0)
				{
					PicDcMult->SelectObject(&graf_pen1);		// выбираем ручку
					PicDcMult->MoveTo(KOORD(0, Wave_function[0]));

					for (int j = 1; j < Wave_function.size(); j++)
					{
						PicDcMult->LineTo(KOORD(j, Wave_function[j]));
					}
				}
			}
		}
		else
		{
			if (wave_packet.size() != 0)
			{
				PicDcMult->SelectObject(&graf_pen1);		// выбираем ручку
				PicDcMult->MoveTo(KOORD(0, wave_packet[0][0]));

				for (int j = 0; j < dotscount; j++)
				{
					PicDcMult->LineTo(KOORD(j, wave_packet[j][0]));
				}
			}
		}

		///////////////////
		PicDcMult2->FillSolidRect(&PicMult2, RGB(255, 255, 255));    // закрашиваем фон
		PicDcMult2->SelectObject(&osi_pen);		// выбираем ручку

		//создаём Ось Y
		PicDcMult2->MoveTo(KOORD2(0, ymin2));
		PicDcMult2->LineTo(KOORD2(0, ymax2));
		//создаём Ось Х			
		PicDcMult2->MoveTo(KOORD2(xmin2, 0));
		PicDcMult2->LineTo(KOORD2(xmax2, 0));




		if (Fre.size() != 0)
		{
			PicDcMult2->SelectObject(&graf_penred);		// выбираем ручку
			PicDcMult2->MoveTo(KOORD2(0, Fre[0]));

			for (int j = 1; j < Fre.size(); j++)
			{
				PicDcMult2->LineTo(KOORD2(j, Fre[j]));
			}
		}
		if (MasEnergy.size() != 0)
		{
			PicDcMult2->SelectObject(&setka_pen);		// выбираем ручку

			for (int j = 0; j < MasEnergy.size(); j++)
			{
				double FreK = -((2 * j + 1)*M_PI) / 2;
				PicDcMult2->MoveTo(KOORD2(xmin2, FreK));
				PicDcMult2->LineTo(KOORD2(xmax2, FreK));
			}

		}



	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CShredingerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




double CShredingerDlg::UPot(double x)
{
	return alpha * pow(x, 4) - beta * pow(x, 2);
}

void CShredingerDlg::Upot(double alpha, double beta, int r)
{
	vector<double> x;
	int dot = dotscount / 2;
	x.resize(dotscount);
	double j = r / dot;
	x[0] = 0;
	double step = 2 * R / dotscount;
	for (int i = 0; i < x.size(); i++)
	{
		u[i] = UPot(-R + i * step);
	}




}

void CShredingerDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	MasEnergy.resize(0);
	xmax1 = dotscount;
	xmax2 = dotscountEnergy;
	step = (2 * R) / dotscount;
	u.resize(dotscount);

	Upot(alpha, beta, R);
	ymax1 = u[0];

	fi.resize(dotscount);
	fi_past.resize(dotscount);
	for (int j = 0; j < dotscount; j++)
	{
		fi[j] = 0;
	}
	/*for по энерниям*/
	Fre.resize(dotscountEnergy);
	for (int t = 0; t < Fre.size(); t++)
	{
		BufE = ((Emax - Emin) / dotscountEnergy)*t + Emin;
		fi[0] = M_PI / 2;
		for (int i = 1; i < dotscount; i++)
		{
			fi[i] = fi[i - 1] + step * (-(BufE - u[i - 1])*pow(cos(fi[i - 1]), 2) - pow(sin(fi[i - 1]), 2));
		}

		Fre[t] = fi[dotscount - 1];
	}
	ymax2 = 0;
	ymin2 = 0;
	for (int j = 0; j < u.size(); j++)
	{
		if (u[j] > ymax1)ymax1 = u[j];
		if (u[j] < ymin1)ymin1 = u[j];
	}
	for (int j = 0; j < Fre.size(); j++)
	{
		if (Fre[j] > ymax2)ymax2 = Fre[j];
		if (Fre[j] < ymin2)ymin2 = Fre[j];
	}
	double StepEnergy = (Emax - Emin) / dotscountEnergy;
	for (int i = 0, k = 0; i < Fre.size(); i++)
	{
		double FreK = -((2 * k + 1)*M_PI) / 2;
		if (Fre[i] <= FreK)
		{
			MasEnergy.push_back(Emin + i * StepEnergy);
			k++;
		}
	}




	//for (int i = 0; i < func.size(); i++)
	//{
	
	//}




	Kmax = MasEnergy.size()-1 ;
	WaveType = false;
	OnOff = false;
	ymin1 = -0.1*ymax1;			//Минимальное значение y1
	UpdateData(FALSE);
	Invalidate();
}


void CShredingerDlg::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnCancel();
}


void CShredingerDlg::OnBnClickedOk2() //Волновая функция
{
	UpdateData(TRUE);
	r.resize(dotscount);
	fi.resize(dotscount);
	Wave_function.resize(dotscount);
	step = (2 * R) / dotscount;
	fi[0] = M_PI / 2;
	r[0] = M_PI / 2;
	Wave_function[0] = r[0] * cos(fi[0]);

	double StepEnergy = (Emax - Emin) / dotscountEnergy;
	vector<double> func;
	func.resize(dotscountEnergy);
	for (int i = 0; i < func.size(); i++)
	{
		int k = k_value;
		double FreK = -((2 * k + 1)*M_PI) / 2;
		func[i] = Fre[i] - FreK;

	}
	double a = 0;
	double b = dotscountEnergy;
	double c = 0;
	while ((b - a) > 1e-10)
	{
		c = (a + b) / 2;
		if (func[a] * func[c] > 0) a = c;
		else b = c;
	}
	for (int i = 0; i < MasEnergy.size(); i++)
	{
		MasEnergy[i] = 0;
	}
	MasEnergy[0] = Emin + c*StepEnergy;

	for (int i = 1; i < dotscount; i++)
	{
		fi[i] = fi[i - 1] + step * (-(MasEnergy[0] - u[i - 1])*pow(cos(fi[i - 1]), 2) - pow(sin(fi[i - 1]), 2));
		r[i] = r[i - 1] + step * (r[i - 1] * (1 + u[i - 1] - MasEnergy[0])*cos(fi[i - 1])*sin(fi[i - 1]));
		Wave_function[i] = r[i] * cos(fi[i]);
	}


	xmin1 = 0; xmax1 = dotscount;
	ymin1 = ymax1 = 0;
	for (int i = 0; i < dotscount; i++)
	{
		if (Wave_function[i] > ymax1)ymax1 = Wave_function[i];
		if (Wave_function[i] < ymin1)ymin1 = Wave_function[i];
	}
	ymax1 *= 1.1;
	ymin1 *= 1.1;
	WaveType = true;
	OnOff = false;
	UpdateData(FALSE);
	Invalidate();
}

double CShredingerDlg::calc_wave_fuc(double amplituda, double mat_expec, double dis, int x)
{
	return amplituda * exp(-(x - mat_expec)*(x - mat_expec)/dis/dis/4);
}

void CShredingerDlg::OnBnClickedOk3()
{
	UpdateData();
	amplituda = 3.;
	mat_expec = 15;
	dis = 0.1;
	OnOff = true;
	double step =  R / dotscount;
	wave_packet.resize(dotscount);
	countOf_t = 200;

	for (int i = 0; i < dotscount; i++)
	{
		for (int j = 0; j < countOf_t; j++)
		{
			wave_packet[i].resize(countOf_t);
			wave_packet[i][0] = calc_wave_fuc(3.,0.8,0.1,i);
		}
	}

	for (int i = 0; i < dotscount; i++)
	{
		if (wave_packet[i][0] > ymax1)ymax1 = wave_packet[i][0];
	}
	Invalidate();
	UpdateData(FALSE);
}

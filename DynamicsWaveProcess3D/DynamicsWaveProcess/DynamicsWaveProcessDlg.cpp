
// DynamicsWaveProcessDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "DynamicsWaveProcess.h"
#include "DynamicsWaveProcessDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CDynamicsWaveProcessDlg
#define KOORD1(x,y) (xp1*((x)-xmin1)),(yp1*((y)-ymax1)) 
#define KOORD2(x,y) (xp2*((x)-xmin2)),(yp2*((y)-ymax2))
#define KOORD3(x,y) (xp3*((x)-xmin3)),(yp3*((y)-ymax3))
#define M_PI 3.1415926535


CDynamicsWaveProcessDlg::CDynamicsWaveProcessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DYNAMICSWAVEPROCESS_DIALOG, pParent)
	, R(5)
	, dotscountR(50)
	, TimeStep(0.01)
	, dotscountTime(512)
	, V0(1)
	, num_wave_pak(0)
	, positionSlider3(0)
	, param1(1)
	, kupx0(0)
	, kupy0(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDynamicsWaveProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, slid1);
	DDX_Control(pDX, IDC_SLIDER2, slid2);
	DDX_Text(pDX, IDC_EDIT1, R);
	DDX_Text(pDX, IDC_EDIT2, dotscountR);
	DDX_Text(pDX, IDC_EDIT3, TimeStep);
	DDX_Text(pDX, IDC_EDIT4, dotscountTime);
	DDX_Text(pDX, IDC_EDIT5, V0);
	DDX_Text(pDX, IDC_EDIT6, num_wave_pak);
	DDX_Control(pDX, IDC_SLIDER3, slid3);
	DDX_Slider(pDX, IDC_SLIDER3, positionSlider3);
	DDX_Text(pDX, IDC_EDIT7, param1);
	DDX_Text(pDX, IDC_EDIT8, kupx0);
	DDX_Text(pDX, IDC_EDIT9, kupy0);
}

BEGIN_MESSAGE_MAP(CDynamicsWaveProcessDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDynamicsWaveProcessDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDynamicsWaveProcessDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CDynamicsWaveProcessDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CDynamicsWaveProcessDlg::OnBnClickedButton1)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BUTTON3, &CDynamicsWaveProcessDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Обработчики сообщений CDynamicsWaveProcessDlg

BOOL CDynamicsWaveProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок


	PicWndMult1 = GetDlgItem(IDC_STATIC1);
	PicDcMult1 = PicWndMult1->GetDC();
	PicWndMult1->GetClientRect(&PicMult1);

	PicWndMult2 = GetDlgItem(IDC_STATIC2);
	PicDcMult2 = PicWndMult2->GetDC();
	PicWndMult2->GetClientRect(&PicMult2);

	PicWndMult3 = GetDlgItem(IDC_STATIC3);
	PicDcMult3 = PicWndMult3->GetDC();
	PicWndMult3->GetClientRect(&PicMult3);

	setka_pen.CreatePen(  //для сетки
		PS_DASH,    //сплошная линия
		//PS_DOT,     //пунктирная
		1,      //толщина 1 пиксель
		RGB(155, 155, 155));  //цвет серый

	osi_pen.CreatePen(   //координатные оси
		PS_SOLID,    //сплошная линия
		3,      //толщина 3 пикселя
		RGB(0, 0, 0));   //цвет черный

	graf_pen.CreatePen(   //график
		PS_DASH,    //сплошная линия
		1,      //толщина 2 пикселя
		RGB(0, 0, 0));   //цвет черный

	graf_pen1.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		2,      //толщина 2 пикселя
		RGB(255, 0, 0));   //цвет розовый

	graf_penred.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		2,      //толщина 2 пикселя
		RGB(255, 0, 0));   //цвет черный

	graf_pengreen.CreatePen(   //график
		PS_DASH,    //сплошная линия
		2,      //толщина 2 пикселя
		RGB(0, 255, 0));   //цвет черный

	graf_penblue.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		1,      //толщина 2 пикселя
		RGB(0, 0, 255));   //цвет черный




	OnBnClickedOk();

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}
void CDynamicsWaveProcessDlg::OnPaint()
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
		xp1 = ((double)(PicMult1.Width()) / (xmax1 - xmin1));			// Коэффициенты пересчёта координат по x1
		yp1 = -((double)(PicMult1.Height()) / (ymax1 - ymin1));       // Коэффициенты пересчёта координат по y1

		xp2 = ((double)(PicMult2.Width()) / (xmax2 - xmin2));			// Коэффициенты пересчёта координат по x2
		yp2 = -((double)(PicMult2.Height()) / (ymax2 - ymin2));       // Коэффициенты пересчёта координат по y2

		xp3 = ((double)(PicMult3.Width()) / (xmax3 - xmin3));			// Коэффициенты пересчёта координат по x3
		yp3 = -((double)(PicMult3.Height()) / (ymax3 - ymin3));       // Коэффициенты пересчёта координат по y3
		///////////////////////////////////////////////
		///////////////////////////////////////////////


		PicDcMult1->FillSolidRect(&PicMult1, RGB(0, 0, 0));
		Risunok(PicDcMult1, wave_pakage, xmin1, xmax1, ymin1, ymax1, xp1, yp1);

		if (num_wave_pak == dotscountTime - 1)
		{
			UpdateData(1);
			num_wave_pak++;
			UpdateData(0);
			KillTimer(timer_ptr);

		}

		///////////////////////////////////////////////
		// для MULT2
		// для MULT2
		PicDcMult2->FillSolidRect(&PicMult2, RGB(0, 0, 0));    // закрашиваем фон
		PicDcMult2->SelectObject(&osi_pen);		// выбираем ручку

		//создаём Ось Y
		PicDcMult2->MoveTo(KOORD2(0, ymin2));
		PicDcMult2->LineTo(KOORD2(0, ymax2));
		//создаём Ось Х
		PicDcMult2->MoveTo(KOORD2(xmin2, 0));
		PicDcMult2->LineTo(KOORD2(xmax2, 0));

		if (Furie.size() != 0)
		{
			PicDcMult2->SelectObject(&graf_pengreen);		// выбираем ручку
			PicDcMult2->MoveTo(KOORD2(0, sqrt(Furie[0].real() * Furie[0].real())));
			for (int i = 0; i < Furie.size(); i++)
			{
				PicDcMult2->LineTo(KOORD2(i, sqrt(Furie[i].real() * Furie[i].real())));
			}
		}
		///////////////////////////////////////////////
		// для MULT3
		PicDcMult3->FillSolidRect(&PicMult3, RGB(0, 0, 0));    // закрашиваем фон
		Risunok(PicDcMult3, WaveFunc, xmin3, xmax3, ymin3, ymax3, xp3, yp3);
		//////////////////////////////////////////////
		//////////////////////////////////////////////
		PicDcMult1->SelectObject(&graf_pengreen);
		//создаём Ось Слайдера 1
		PicDcMult1->MoveTo(KOORD1(positionSlider1, ymin1));
		PicDcMult1->LineTo(KOORD1(positionSlider1, ymax1));

		PicDcMult1->SelectObject(&graf_pengreen);
		//создаём Ось Слайдера 1
		PicDcMult1->MoveTo(KOORD1(xmin1, positionSlider3));
		PicDcMult1->LineTo(KOORD1(xmax1, positionSlider3));

		PicDcMult2->SelectObject(&graf_pengreen);
		//создаём Ось Слайдера 2
		PicDcMult2->MoveTo(KOORD2(positionSlider2, ymin2));
		PicDcMult2->LineTo(KOORD2(positionSlider2, ymax2));
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CDynamicsWaveProcessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDynamicsWaveProcessDlg::OnBnClickedOk() //Reset
{
	UpdateData(1);
	if (timer_ptr != NULL) KillTimer(timer_ptr);
	num_wave_pak = 0;
	xmax1 = dotscountR;			//Максимальное значение х1
	ymax1 = dotscountR;			//Максимальное значение y1
	xmin1 = 0;			//Минимальное значение х1
	ymin1 = 0;			//Минимальное значение y1

	xmax2 = dotscountTime / param1;			//Максимальное значение х1
	ymax2 = 5;			//Максимальное значение y1
	xmin2 = 0;			//Минимальное значение х1
	ymin2 = -0.1*ymax2;			//Минимальное значение y1

	xmax3 = dotscountR;			//Максимальное значение х3
	ymax3 = dotscountR;			//Максимальное значение y3
	xmin3 = 0;			//Минимальное значение х3
	ymin3 = 0;			//Минимальное значение y3

	slid1.SetRangeMin(0);
	slid1.SetRangeMax(dotscountR - 1);
	slid3.SetRangeMin(0);
	slid3.SetRangeMax(dotscountR - 1);
	slid2.SetRangeMin(0);
	slid2.SetRangeMax(dotscountTime - 1);
	on1 = false;
	WaveFunc.resize(0);
	Furie.resize(0);
	ksi.resize(0);
	ksi_second.resize(0);
	data_fur.resize(0);
	ksi_start.resize(0);
	u.resize(0);
	ksi.resize(dotscountTime);
	data_fur.resize(dotscountTime);
	ksi_second.resize(dotscountTime/param1);
	for (int i = 0; i < dotscountTime; i++)
	{
		ksi[i].resize(dotscountR);
		data_fur[i].resize(dotscountR);
		for (int j = 0; j < dotscountR; j++)
		{
			ksi[i][j].resize(dotscountR);
			data_fur[i][j].resize(dotscountR);
		}
	}
	for (int i = 0; i < ksi_second.size(); i++)
	{
		ksi_second[i].resize(dotscountR);
		for (int j = 0; j < dotscountR; j++)
		{
			ksi_second[i][j].resize(dotscountR);
		}
	}
	ksi_start.resize(dotscountR);
	u.resize(dotscountR);
	wave_pakage.resize(dotscountR);
	for (int i = 0; i < dotscountR; i++)
	{
		ksi_start[i].resize(dotscountR);
		u[i].resize(dotscountR);
		wave_pakage[i].resize(dotscountR);
	}
	Step = 2 * R / dotscountR;
	UPot(5, V0);
	PsiPot(kupx0,kupy0);
	for (int i = 0; i < dotscountR; i++)
	{
		for (int j = 0; j < dotscountR; j++)
		{
			wave_pakage[i][j] = ksi_start[i][j].real();
		}
	}
	ksi[0] = ksi_start;
	ksi_second[0] = ksi_start;
	UpdateData(0);
	Invalidate();
}

void CDynamicsWaveProcessDlg::OnTimer(UINT_PTR nIDEvent)
{
	UpdateData(1);
	num_wave_pak++;
	Complex A = AK(TimeStep, Step);
	Complex B = BK(TimeStep, Step);
	vector<vector <Complex>> C; C.resize(dotscountR);
	vector<vector <Complex>> D; D.resize(dotscountR);
	vector<vector <Complex>> a; a.resize(dotscountR);
	vector<vector <Complex>> b; b.resize(dotscountR);
	vector<vector <Complex>> SETKA_BUFFER; SETKA_BUFFER.resize(dotscountR);
	for (int i = 0; i < dotscountR; i++)
	{
		C[i].resize(dotscountR);
		D[i].resize(dotscountR);
		a[i].resize(dotscountR);
		b[i].resize(dotscountR);
		SETKA_BUFFER[i].resize(dotscountR);
	}
	////Прогонка по X
	for (int i = 1; i < dotscountR - 1; i++)
	{
		for (int j = 1; j < dotscountR - 1; j++)
		{
			C[i][j] = CK(TimeStep, Step, u[i][j]);
			D[i][j] = DK(TimeStep, ksi[num_wave_pak - 1][i][j],
				delta2(Step, ksi[num_wave_pak - 1][i - 1][j], ksi[num_wave_pak - 1][i][j], ksi[num_wave_pak - 1][i + 1][j]),
				delta2(Step, ksi[num_wave_pak-1][i][j - 1], ksi[num_wave_pak-1][i][j], ksi[num_wave_pak-1][i][j + 1]),
				u[i][j]);
		}
	}
	for (int i = 1; i < dotscountR; i++)
	{
		for (int j = 0; j < dotscountR; j++)
		{
			a[i][j] = ak(a[i - 1][j], A, B, C[i - 1][j]);
			b[i][j] = bk(a[i - 1][j], b[i - 1][j], A, C[i - 1][j], D[i - 1][j]);
		}
	}
	for (int i = dotscountR - 2; i >= 0; i--)
	{
		for (int j = 0; j < dotscountR; j++)
		{
			SETKA_BUFFER[i][j] = a[i + 1][j] * ksi[num_wave_pak][i + 1][j] + b[i + 1][j];
		}
	}
	//Прогонка по Y
	for (int i = 1; i < dotscountR - 1; i++)
	{
		for (int j = 1; j < dotscountR - 1; j++)
		{
			D[i][j] = DK(TimeStep, ksi[num_wave_pak - 1][i][j],
				delta2(Step, SETKA_BUFFER[i - 1][j], SETKA_BUFFER[i][j], SETKA_BUFFER[i + 1][j]),
				delta2(Step, SETKA_BUFFER[i][j - 1], SETKA_BUFFER[i][j], SETKA_BUFFER[i][j + 1]),
				u[i][j]);
		}
	}
	a.resize(dotscountR);
	b.resize(dotscountR);
	for (int i = 0; i < dotscountR; i++)
	{
		a[i].resize(dotscountR);
		b[i].resize(dotscountR);
	}
	for (int i = 0; i < dotscountR; i++)
	{
		for (int j = 1; j < dotscountR; j++)
		{
			a[i][j] = ak(a[i][j-1], A, B, C[i][j-1]);
			b[i][j] = bk(a[i][j-1], b[i][j-1], A, C[i][j-1], D[i][j-1]);
		}
	}
	for (int i = 0; i <dotscountR; i++)
	{
		for (int j = dotscountR - 2; j >= 0; j--)
		{
			ksi[num_wave_pak][i][j] = a[i][j+1] * ksi[num_wave_pak][i][j+1] + b[i][j+1];
		}
	}
	//Заполнение массива отрисовки
	for (int i = 0; i < dotscountR; i++)
	{
		for (int j = 0; j < dotscountR; j++)
		{
			wave_pakage[i][j] = ksi[num_wave_pak][i][j].real();
			if (num_wave_pak%param1==0)
			{
				ksi_second[num_wave_pak / param1][i][j] = ksi[num_wave_pak][i][j];
			}

		}
	}
	UpdateData(0);
	InvalidateRect(&PicMult1);
}



void CDynamicsWaveProcessDlg::OnBnClickedButton1() //Эволюция
{
	OnBnClickedOk();
	timer_ptr = SetTimer(10, 50, NULL);
}

void CDynamicsWaveProcessDlg::OnBnClickedButton2() //Фурье
{
	for (int i = 0; i < dotscountR; i++)
	{
		for (int j = 0; j < dotscountR; j++)
		{
			Furie.resize(0);
			Furie.resize(ksi_second.size());
			for (int t = 0; t < ksi_second.size(); t++)
			{
				Furie[t] = ksi_second[t][i][j];
			}
			fur(Furie, 1);
			for (int t = 0; t < ksi_second.size(); t++)
			{
				data_fur[t][i][j] = Furie[t];
			}
		}
	}
	on1 = true;


}

void CDynamicsWaveProcessDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	positionSlider1 = slid1.GetPos();
	positionSlider2 = slid2.GetPos();
	positionSlider3 = slid3.GetPos();
	InvalidateRect(&PicMult1);
	if (on1)
	{
		for (int i = 0; i < ksi_second.size(); i++)
		{
			Furie[i] = data_fur[i][positionSlider1][positionSlider3];
		}
		ymax2 = Max(Furie);
		ymin2 = 0;
		InvalidateRect(&PicMult2);

		WaveFunc.resize(dotscountR);
		for (int i = 0; i < dotscountR; i++)
		{
			WaveFunc[i].resize(dotscountR);
			for (int j = 0; j < dotscountR; j++)
			{
				WaveFunc[i][j] = data_fur[positionSlider2][i][j].real();
			}
		}
		InvalidateRect(&PicMult3);
	}
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CDynamicsWaveProcessDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	positionSlider1 = slid1.GetPos();
	positionSlider2 = slid2.GetPos();
	positionSlider3 = slid3.GetPos();


	InvalidateRect(&PicMult1);

	if (on1)
	{

		for (int i = 0; i < ksi_second.size(); i++)
		{
			Furie[i] = data_fur[i][positionSlider1][positionSlider3];
		}
		ymax2 = Max(Furie);
		ymin2 = 0;
		InvalidateRect(&PicMult2);

		WaveFunc.resize(dotscountR);
		for (int i = 0; i < dotscountR; i++)
		{
			WaveFunc[i].resize(dotscountR);
			for (int j = 0; j < dotscountR; j++)
			{
				WaveFunc[i][j] = data_fur[positionSlider2][i][j].real();
			}
		}
		InvalidateRect(&PicMult3);
	}



	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDynamicsWaveProcessDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

void CDynamicsWaveProcessDlg::UPot(int diametr, double V0)
{

	for (int i = diametr; i < u.size() - diametr; i++)
	{
		for (int j = diametr; j < u.size() - diametr; j++)
		{
			u[i][j] = -V0;
		}
	}
}

void CDynamicsWaveProcessDlg::PsiPot(double a, double b)
{
	double Psi0 = 1.;

	double sigma = 0.3;
	for (int i = 0; i < dotscountR; i++)
	{

		for (int j = 0; j < dotscountR; j++)
		{
			double x = -R + Step * i;
			double y = -R + Step * j;
			ksi_start[i][j] = Psi0 * exp(-(pow((x - a), 2) / (2 * pow(sigma, 2))) - (pow((y - b), 2) / (2 * pow(sigma, 2))));
		}
	}
}
double CDynamicsWaveProcessDlg::Max(vector<double> Mass)
{
	double ymax = 0;
	for (int j = 0; j < Mass.size(); j++)
	{
		if (Mass[j] > ymax)ymax = Mass[j];
	}
	return ymax;
}
double CDynamicsWaveProcessDlg::Max(vector<Complex> Mass)
{
	double ymax = 0;
	for (int j = 0; j < Mass.size(); j++)
	{
		if (Mass[j].real() > ymax)
			ymax = Mass[j].real();
		if (Mass[j].imag() > ymax)
			ymax = Mass[j].imag();
	}
	return ymax;
}
double CDynamicsWaveProcessDlg::Min(vector<double> Mass)
{
	double ymax = 0;
	for (int j = 0; j < Mass.size(); j++)
	{
		if (Mass[j] < ymax)ymax = Mass[j];
	}
	return ymax;
}
double CDynamicsWaveProcessDlg::Min(vector<Complex> Mass)
{
	double ymax = 0;
	for (int j = 0; j < Mass.size(); j++)
	{
		if (Mass[j].real() < ymax)ymax = Mass[j].real();
		if (Mass[j].imag() < ymax)ymax = Mass[j].imag();
	}
	return ymax;
}

void CDynamicsWaveProcessDlg::Risunok(CDC *PicDc, vector<vector <double>> Mass, int xmin, int xmax, int ymin, int ymax, double xp, double yp)
{
	double size, min, max;
	min = max = 0;
	for (int i = 0; i < Mass.size(); i++)
	{
		for (int j = 0; j < Mass[i].size(); j++)
		{
			if (Mass[i][j] > max) max = Mass[i][j];
			if (Mass[i][j] < min) min = Mass[i][j];
		}
	}
	size = max - min;
	for (int i = 0; i < Mass.size(); i++)
	{
		for (int j = 0; j < Mass[i].size(); j++)
		{
			int color = (int)(((Mass[i][j] - min) / size) * 255);
			PicDc->FillSolidRect((xp*((i)-xmin)), (yp*((j)-ymax)), xp, yp, RGB(color, color, color));
		}
	}
}

void CDynamicsWaveProcessDlg::OnBnClickedButton3()
{
	KillTimer(timer_ptr);
}

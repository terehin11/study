
// DynamicWavePacketDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "DynamicWavePacket.h"
#include "DynamicWavePacketDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// диалоговое окно CDynamicWavePacketDlg

#define KOORD(x,y) (xp1*((x)-xmin1)),(yp1*((y)-ymax1)) 
#define KOORD2(x,y) (xp2*((x)-xmin2)),(yp2*((y)-ymax2))
#define KOORD3(x,y) (xp3*((x)-xmin3)),(yp3*((y)-ymax3))
#define sqrt_module_psi sqrt(pow(psiOneImg[i].real(), 2) + pow(psiOneImg[i].imag(), 2)) 
//#define sqrt_module_wave_func sqrt(pow(wave_function[i].real(), 2) + pow(wave_function[i].imag(), 2)) 
#define sqrt_module_fur sqrt(pow(furie[i].real(), 2) + pow(furie[i].imag(),2))

CDynamicWavePacketDlg::CDynamicWavePacketDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CDynamicWavePacketDlg::IDD, pParent)
, dotscount_psi(400)
, R(1)
, amplitude(3)
, math_expec(0)
, disp(0.1)
, countOf_t(512)
, timerTick(0)
, positionSlider1(0)
, positionSlider2(0)
, alfa1(1)
, beta(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDynamicWavePacketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, dotscount_psi);
	DDX_Text(pDX, IDC_EDIT2, R);
	DDX_Text(pDX, IDC_EDIT3, amplitude);
	DDX_Text(pDX, IDC_EDIT4, math_expec);
	DDX_Text(pDX, IDC_EDIT5, disp);
	DDX_Text(pDX, IDC_EDIT6, countOf_t);
	DDX_Text(pDX, IDC_EDIT7, timerTick);
	DDX_Control(pDX, IDC_SLIDER1, sliderCtrl1);
	DDX_Control(pDX, IDC_SLIDER2, sliderCtrl2);
	DDX_Text(pDX, IDC_EDIT8, positionSlider1);
	DDX_Text(pDX, IDC_EDIT9, positionSlider2);
	DDX_Text(pDX, IDC_EDIT10, alfa1);
	DDX_Text(pDX, IDC_EDIT11, beta);
}

BEGIN_MESSAGE_MAP(CDynamicWavePacketDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDynamicWavePacketDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDynamicWavePacketDlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CDynamicWavePacketDlg::OnBnClickedButton3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CDynamicWavePacketDlg::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_BUTTON4, &CDynamicWavePacketDlg::OnBnClickedButton4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CDynamicWavePacketDlg::OnNMCustomdrawSlider2)
END_MESSAGE_MAP()


// обработчики сообщений CDynamicWavePacketDlg

BOOL CDynamicWavePacketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	psi.resize(dotscount_psi);
	psiOneImg.resize(dotscount_psi);
	furie.resize(dotscount_psi);
	wave_function.resize(dotscount_psi);
	OnBnClickedButton3();
	timerTick = 0;

	ymax1 = amplitude;
	ymin1 = -0.2;
	xmax1 = dotscount_psi;
	xmin1 = -0.2;

	ymax2 = amplitude;
	ymin2 = -0.2;
	xmax2 = dotscount_psi;
	xmin2 = -0.2;

	ymax3 = amplitude;
	ymin3 = -0.2;
	xmax3 = dotscount_psi;
	xmin3 = -0.2;


	sliderCtrl1.SetRange(0, dotscount_psi - 1, true);
	sliderCtrl2.SetRange(0, dotscount_psi - 1, true);

	sliderCtrl1.SetPos(dotscount_psi / 2);
	sliderCtrl2.SetPos(dotscount_psi / 2);

	positionSlider1 = sliderCtrl1.GetPos();
	positionSlider2 = sliderCtrl2.GetPos();

	PicWndMult = GetDlgItem(IDC_STATIC);
	PicDcMult = PicWndMult->GetDC();
	PicWndMult->GetClientRect(&PicMult);

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
		RGB(0, 0, 0));  //цвет серый

	osi_pen.CreatePen(   //координатные оси
		PS_SOLID,    //сплошная линия
		3,      //толщина 3 пикселя
		RGB(0, 0, 0));   //цвет черный

	graf_pen.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		2,      //толщина 2 пикселя
		RGB(0, 0, 255));   //цвет черный

	graf_pen1.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		1,      //толщина 2 пикселя
		RGB(0, 0, 0));   //цвет розовый

	graf_penred.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		2.5,      //толщина 2 пикселя
		RGB(255, 0, 0));   //цвет черный

	graf_pengreen.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		1,      //толщина 2 пикселя
		RGB(0, 150, 0));   //цвет черный

	graf_penblue.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		2,      //толщина 2 пикселя
		RGB(0, 0, 255));   //цвет черный

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CDynamicWavePacketDlg::OnPaint()
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


		xp3 = ((double)(PicMult3.Width()) / (xmax3 - xmin3));			// Коэффициенты пересчёта координат по x3
		yp3 = -((double)(PicMult3.Height()) / (ymax3 - ymin3));       // Коэффициенты пересчёта координат по y3
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

		if (timerTick == countOf_t - 1)
		{
			UpdateData();
			timerTick++;
			KillTimer(10);
			UpdateData(FALSE);
		}
		if (psi.size() != 0)
		{
			PicDcMult->SelectObject(&graf_penred);
			PicDcMult->MoveTo(KOORD(0, psiOneImg[0].real()));
			for (int i = 0; i < psiOneImg.size(); i++)
				PicDcMult->LineTo(KOORD(i, sqrt_module_psi));
		}

		if (uPot.size() != 0)
		{
			PicDcMult->SelectObject(&graf_penblue);
			PicDcMult->MoveTo(KOORD(0, 0));
			for (int i = 0; i < uPot.size(); i++)
				PicDcMult->LineTo(KOORD(i, uPot[i]));
		}

		if (psi.size() != 0)
		{
			PicDcMult->SelectObject(&graf_pengreen);
			PicDcMult->MoveTo(KOORD(0, 0));
			for (int i = 0; i < psi.size(); i++)
				PicDcMult->LineTo(KOORD(i, psi[i].real()));
		}


		PicDcMult2->SelectObject(&osi_pen);		// выбираем ручку
		PicDcMult2->FillSolidRect(&PicMult2, RGB(255, 255, 255));
		//создаём Ось Y
		PicDcMult2->MoveTo(KOORD2(0, ymin2));
		PicDcMult2->LineTo(KOORD2(0, ymax2));
		//создаём Ось Х		   
		PicDcMult2->MoveTo(KOORD2(xmin2, 0));
		PicDcMult2->LineTo(KOORD2(xmax2, 0));


		if (furie.size() != 0)
		{
			PicDcMult2->SelectObject(&graf_penred);
			PicDcMult2->MoveTo(KOORD2(0, furie[0].real()));
			for (int i = 0; i < furie.size(); i++)
				PicDcMult2->LineTo(KOORD2(i, sqrt_module_fur));
		}




		PicDcMult->SelectObject(&graf_pengreen);
		PicDcMult->MoveTo(KOORD(positionSlider1, 0));
		PicDcMult->LineTo(KOORD(positionSlider1, infinite));



		PicDcMult2->SelectObject(&graf_pengreen);
		PicDcMult2->MoveTo(KOORD2(positionSlider2, 0));
		PicDcMult2->LineTo(KOORD2(positionSlider2, infinite));

		/////////////////////FOR PICMULT3///////////////////////
		PicDcMult3->FillSolidRect(&PicMult3, RGB(255, 255, 255));


		//создаём Ось Y
		PicDcMult3->SelectObject(&osi_pen);
		PicDcMult3->MoveTo(KOORD3(0, ymin3));
		PicDcMult3->LineTo(KOORD3(0, ymax3));

		PicDcMult3->MoveTo(KOORD3(xmin3, 0));
		PicDcMult3->LineTo(KOORD3(xmax3, 0));

		if (wave_function.size() != 0)
		{
			PicDcMult3->SelectObject(&graf_penred);
			PicDcMult3->MoveTo(KOORD3(0, wave_function[0].real()));
			for (int i = 0; i < wave_function.size(); i++)
				PicDcMult3->LineTo(KOORD3(i, wave_function[i].real()));
		}

	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CDynamicWavePacketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDynamicWavePacketDlg::u_Pot(double alpha, double beta, int r)
{
	vector<double> x;
	int dot = dotscount_psi / 2;
	x.resize(dotscount_psi);
	uPot.resize(dotscount_psi);
	double j = r / dot;
	x[0] = 0;
	double step = 2 * R / dotscount_psi;
	for (int i = 0; i < x.size(); i++)
	{
		uPot[i] = u_Pot2(-R + i * step);
	}
}

double CDynamicWavePacketDlg::u_Pot2(double x)
{
	return alfa1 * pow(x, 4) - beta * pow(x, 2);
}

void CDynamicWavePacketDlg::OnBnClickedButton1()
{
	UpdateData(1);
	calc = false;
	ymax1 = 0;
	psi.resize(dotscount_psi);
	//uPot.resize(dotscount_psi);
	step_psi = 2 * R / dotscount_psi;

	for (int i = 0; i < dotscount_psi; i++)
	{
		psi[i] = calc_wave_function(amplitude, math_expec, disp, -R + step_psi * i);
	}

	u_Pot(alfa1, beta, R);
	for (int i = 0; i < dotscount_psi; i++)
	{
		if (ymax1 < psi[i].real()) ymax1 = psi[i].real();
	}

	ymax1 *= 1.1;
	xmax1 = dotscount_psi;
	xmin1 = -0.05*xmax1;
	ymin1 = -0.2;

	InvalidateRect(&PicMult, false);
	UpdateData(FALSE);

}


Complex CDynamicWavePacketDlg::calc_wave_function(double amplitude, double math_expec, double disp, double x)
{
	return amplitude * exp(-(x - math_expec) * (x - math_expec) / disp / disp / 4);
}

//evolution
void CDynamicWavePacketDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	calc = false;
	timerTick = 0;
	step_time = 0.01;
	step_psi = 2 * R / dotscount_psi;

	c.resize(dotscount_psi);
	d.resize(dotscount_psi);
	psiOneImg.resize(dotscount_psi);

	WEB.resize(countOf_t);
	for (int i = 0; i < countOf_t; i++)
		WEB[i].resize(dotscount_psi);


	WEB[0] = psi;
	xmax1 = dotscount_psi;
	xmin1 *= -0.01*xmax1;
	SetTimer(10, 100, NULL);
	UpdateData(FALSE);
}




void CDynamicWavePacketDlg::OnTimer(UINT_PTR nIDEvent)
{
	UpdateData(1);

	timerTick++;
	psiOneImg.resize(dotscount_psi);
	alfa.resize(dotscount_psi);
	betta.resize(dotscount_psi);

	a = A(step_time, step_psi);
	b = B(step_time, step_psi);
	vector<Complex> c;
	c.resize(dotscount_psi);
	vector<Complex> d;
	d.resize(dotscount_psi);
	for (int k = 1; k < dotscount_psi - 1; k++)
	{
		double pot = uPot[k];
		c[k] = C(step_time, step_psi, pot);
		Complex proizv_value = proizv(step_psi, WEB[timerTick - 1][k - 1], WEB[timerTick - 1][k], WEB[timerTick - 1][k + 1]);
		d[k] = D(step_time, step_psi, WEB[timerTick - 1][k], proizv_value, pot);
	}

	//edge conditions
	alfa[0] = 0;
	betta[0] = 0;

	for (int k = 1; k < dotscount_psi; k++)
	{
		alfa[k] = ak(alfa[k - 1], a, b, c[k - 1]);
		betta[k] = bk(alfa[k - 1], betta[k - 1], a, c[k - 1], d[k - 1]);
	}
	WEB[timerTick][dotscount_psi - 1] = 0;

	for (int i = dotscount_psi - 2; i >= 0; i--)
	{
		WEB[timerTick][i] = alfa[i + 1] * WEB[timerTick][i + 1] + betta[i + 1];
	}

	psiOneImg = WEB[timerTick];

	xmin1 = -1;

	for (int i = 0; i < dotscount_psi; i++)
	{
		if (ymax1 < sqrt_module_psi) ymax1 = sqrt_module_psi;
	}

	ymin1 = -0.5;


	UpdateData(FALSE);
	InvalidateRect(&PicMult);
	CDialogEx::OnTimer(nIDEvent);
}

//reset
void CDynamicWavePacketDlg::OnBnClickedButton3()
{

	UpdateData();
	calc = false;
	KillTimer(10);
	timerTick = 0;
	positionSlider1 = 0;
	positionSlider2 = 0;
	ymax1 = amplitude;
	ymin1 = -0.1 * ymax1;
	xmax1 = dotscount_psi;
	xmin1 = -0.01*dotscount_psi;

	for (int i = 0; i < dotscount_psi; i++)
	{
		psi[i] = 0;
		psiOneImg[i] = 0;
	}

	InvalidateRect(&PicMult2);
	UpdateData(FALSE);
}

void CDynamicWavePacketDlg::OnBnClickedButton4()
{
	calc = false;
	sliderCtrl2.SetRange(0, countOf_t);
	sliderCtrl2.SetPos(0);

	furie.resize(0);
	furie.resize(countOf_t);

	WEB_FURIE.resize(countOf_t);
	for (int i = 0; i < countOf_t; i++)
		WEB_FURIE[i].resize(dotscount_psi);


	for (int i = 0; i < dotscount_psi; i++)
	{
		for (int j = 0; j < countOf_t; j++)
			furie[j] = WEB[j][i];

		fur(furie, 1, countOf_t);

		for (int j = 0; j < countOf_t; j++)
			WEB_FURIE[j][i] = furie[j];
	}

	calc = true;
	if (calc) MessageBox(L"Calculating process done!", L"ASSERT!", MB_OK);



	xmax2 = countOf_t;
	xmin2 = -0.2;
	ymin2 = -ymax2 * 0.05;
	//InvalidateRect(&PicMult2);





}


void CDynamicWavePacketDlg::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData();
	positionSlider2 = sliderCtrl2.GetPos();
	if (WEB_FURIE.size() != 0 && positionSlider2 < countOf_t) {
		wave_function.resize(dotscount_psi);
		for (int i = 0; i < dotscount_psi; i++)
			wave_function[i] = WEB_FURIE[positionSlider2][i];


		ymax3 = 0;
		ymin3 = 0;
		for (int i = 0; i < wave_function.size(); i++)
		{
			if (ymax3 < wave_function[i].real()) ymax3 = wave_function[i].real();
			if (ymin3 > wave_function[i].real()) ymin3 = wave_function[i].real();
		}
		
		xmax3 = dotscount_psi;
		xmin3 = -1;
		InvalidateRect(&PicMult2);
		InvalidateRect(&PicMult3);

	}
	else
	{
		InvalidateRect(&PicMult2);
		InvalidateRect(&PicMult3);
	}
	*pResult = 0;
	UpdateData(FALSE);
}

void CDynamicWavePacketDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData();
	positionSlider1 = sliderCtrl1.GetPos();
	if (calc)
	{
		for (int i = 0; i < countOf_t; i++)
			furie[i] = WEB_FURIE[i][positionSlider1];


		ymax2 = 0;
		for (int i = 0; i < countOf_t; i++)
		if (ymax2 < sqrt_module_fur) ymax2 = sqrt_module_fur;

		InvalidateRect(&PicMult);
		InvalidateRect(&PicMult2);
	}
	*pResult = 0;
	UpdateData(FALSE);
}
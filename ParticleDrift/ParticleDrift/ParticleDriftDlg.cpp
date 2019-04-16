
// ParticleDriftDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "ParticleDrift.h"
#include "ParticleDriftDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CParticleDriftDlg

#define KOORD_Signal1(x,y) (xp1*((x)-xmin1)),(yp1*((y)-ymax1))   // для пересчета координат
#define KOORD_Signal2(x,y) (xp2*((x)-xmin2)),(yp2*((y)-ymax2))   // для пересчета координат

#define KOORD_Signal1Ell(x,y) (xp1*((x)-xmin1)+1),(yp1*((y)-ymax1)+1),(xp1*((x)-xmin1)-1),(yp1*((y)-ymax1)-1)   // для пересчета координат
#define KOORD_Signal2Ell(x,y) (xp2*((x)-xmin2)+3),(yp2*((y)-ymax2)+3),(xp2*((x)-xmin2)-3),(yp2*((y)-ymax2)-3)   // для пересчета координат

#define RandPlus ((-1.+ 2.* rand()/RAND_MAX)*xmax1*0.0005)

CParticleDriftDlg::CParticleDriftDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PARTICLEDRIFT_DIALOG, pParent)
	, DotsCount(10)
	, bitscount(10)
	, Etest(5)
	, Emin(0)
	, Emax(10)
	, Edots(10)
	, paint_vor(FALSE)
	, tics_count(256)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CParticleDriftDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, DotsCount);
	//DDX_Control(pDX, IDC_Signal1, drawItems); //ОТРИСОВКА GDI+
	DDX_Text(pDX, IDC_EDIT2, bitscount);
	DDX_Text(pDX, IDC_EDIT3, Etest);
	DDX_Text(pDX, IDC_EDIT4, Emin);
	DDX_Text(pDX, IDC_EDIT5, Emax);
	DDX_Text(pDX, IDC_EDIT6, Edots);
	DDX_Check(pDX, IDC_CHECK1, paint_vor);
	DDX_Text(pDX, IDC_EDIT7, tics_count);
}

BEGIN_MESSAGE_MAP(CParticleDriftDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CParticleDriftDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CParticleDriftDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CParticleDriftDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CParticleDriftDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Обработчики сообщений CParticleDriftDlg

BOOL CParticleDriftDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок


	// определение функций для отрисовки Signal
	PicWndSignal1 = GetDlgItem(IDC_Signal1);
	PicDcSignal1 = PicWndSignal1->GetDC();
	PicWndSignal1->GetClientRect(&PicSignal1);

	PicWndSignal2 = GetDlgItem(IDC_Signal2);
	PicDcSignal2 = PicWndSignal2->GetDC();
	PicWndSignal2->GetClientRect(&PicSignal2);

	setka_pen.CreatePen(  //для сетки
		//PS_SOLID,    //сплошная линия
		PS_SOLID,     //пунктирная
		0.2,      //толщина 1 пиксель
		RGB(205, 155, 155));  //цвет серый

	osi_pen.CreatePen(   //координатные оси
		PS_SOLID,    //сплошная линия
		3,      //толщина 3 пикселя
		RGB(138, 138, 138));   //цвет черный

	graf_pen.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		1,      //толщина 2 пикселя
		RGB(163, 138, 184));   //цвет черный

	graf_pen1.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		1,      //толщина 2 пикселя
		RGB(205, 275, 205));   //цвет розовый

	graf_penred.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		2,      //толщина 2 пикселя
		RGB(255, 0, 0));   //цвет красный

	graf_pengreen.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		1,      //толщина 2 пикселя
		RGB(0, 0, 0));   //цвет зеленый

	graf_penblue.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		1,      //толщина 2 пикселя
		RGB(0, 0, 255));   //цвет голубой
	xmin1 = 0; xmax1 = 50;
	ymin1 = 0; ymax1 = 50;
	xmin2 = 0; xmax2 = 300;
	ymin2 = 0; ymax2 = 1;
	Qmax = 1; Qmin = 1;

	paint_vor = false;
	timer_ptr = NULL;
	TimeStep = 1;
	//	drawItems.Invalidate();
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CParticleDriftDlg::OnPaint()
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
		ymin2 = -0.1*ymax2;
		xp1 = ((double)(PicSignal1.Width()) / (xmax1 - xmin1));
		yp1 = -((double)(PicSignal1.Height()) / (ymax1 - ymin1));
		xp2 = ((double)(PicSignal2.Width()) / (xmax2 - xmin2));
		yp2 = -((double)(PicSignal2.Height()) / (ymax2 - ymin2));
		PicDcSignal1->FillSolidRect(&PicSignal1, RGB(255, 255, 255)); //Закрашиваем всё цветов
		/*if (Treug.size() != NULL)
		{
			PicDcSignal1->SelectObject(&graf_penred);

			for (int i = 0; i < Treug.size(); i++)
			{
				PicDcSignal1->MoveTo(KOORD_Signal1(Treug[i].T1.x1, Treug[i].T1.y1));
				PicDcSignal1->LineTo(KOORD_Signal1(Treug[i].T2.x1, Treug[i].T2.y1));
				PicDcSignal1->LineTo(KOORD_Signal1(Treug[i].T3.x1, Treug[i].T3.y1));
				PicDcSignal1->LineTo(KOORD_Signal1(Treug[i].T1.x1, Treug[i].T1.y1));
			}
		}*/
		/*if (GiperDot.size() != NULL)
		{
			PicDcSignal1->SelectObject(&graf_pengreen);

			for (int i = 0; i < GiperDot.size(); i++)
			{
				PicDcSignal1->Ellipse(KOORD_Signal1Ell(GiperDot[i].x1, GiperDot[i].y1));
			}
		}*/
		if (bits.size() != NULL)
		{
			PicDcSignal1->SelectObject(&graf_penred);

			for (int i = 0; i < bits.size(); i++)
			{
				PicDcSignal1->Ellipse(KOORD_Signal1Ell(bits[i].koor.x1, bits[i].koor.y1));
			}
		}
		if (paint_vor)
		{
			if (Polygons.size() != NULL)
			{
				PicDcSignal1->SelectObject(&graf_pen);

				for (int i = 0; i < Polygons.size(); i++)
				{
					if (Polygons[i].V.size() != 0)
					{
						PicDcSignal1->MoveTo(KOORD_Signal1(Polygons[i].V[0].x1, Polygons[i].V[0].y1));
						for (int j = 1; j < Polygons[i].V.size(); j++)
						{
							PicDcSignal1->LineTo(KOORD_Signal1(Polygons[i].V[j].x1, Polygons[i].V[j].y1));
						}
						PicDcSignal1->LineTo(KOORD_Signal1(Polygons[i].V[0].x1, Polygons[i].V[0].y1));
					}
				}
			}
		}
		///////////////////////////////////////////////////////////////////////////////////////////////
		//Окно СИГНАЛА
		PicDcSignal2->FillSolidRect(&PicSignal2, RGB(255, 255, 255)); //Закрашиваем всё цветом
		PicDcSignal2->SelectObject(&osi_pen);		     //выбираем ручку
		//создаём Ось Signal
		PicDcSignal2->MoveTo(KOORD_Signal2(xmin2, ymin2));
		PicDcSignal2->LineTo(KOORD_Signal2(xmin2, ymax2));
		//создаём Ось t
		PicDcSignal2->MoveTo(KOORD_Signal2(xmin2, 0));
		PicDcSignal2->LineTo(KOORD_Signal2(xmax2, 0));

		if (VAH.size() != 0)
		{
			PicDcSignal2->SelectObject(&graf_pengreen);
			for (int i = 0; i < VAH.size(); i++)
			{
				PicDcSignal2->Ellipse(KOORD_Signal2Ell(i, VAH[i]));
			}
			PicDcSignal2->SelectObject(&setka_pen);
			PicDcSignal2->MoveTo(KOORD_Signal2(0, VAH[0]));
			for (int i = 0; i < VAH.size(); i++)
			{
				PicDcSignal2->LineTo(KOORD_Signal2(i, VAH[i]));

			}

		}

		PicDcSignal2->SelectObject(&graf_pengreen);
		double step = xmax2 / Edots;
		double tt = (Emax - Emin) / Edots;
		CString str;
		for (int i = 0; i < Edots; i+=step)
		{
			//string bug = to_string(i * tt + Emin);
			str.Format(_T("%.0f"), i * tt + Emin);
			PicDcSignal2->TextOutW(KOORD_Signal2(xmin2 + i, -0.1),str);
		}
	}
}


// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CParticleDriftDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CParticleDriftDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	bits.clear();
	VAH.clear();
	Polygons.clear();
	Dot dotbuffer;
	//===================================================================
	//Генерация 4 узлов сверхструктуры.
	//===================================================================
	GiperDot.resize(0);
	dotbuffer.x1 = 0.; dotbuffer.y1 = 0;
	GiperDot.push_back(dotbuffer);
	dotbuffer.x1 = xmax1; dotbuffer.y1 = 0;
	GiperDot.push_back(dotbuffer);
	dotbuffer.x1 = 0; dotbuffer.y1 = xmax1;
	GiperDot.push_back(dotbuffer);
	dotbuffer.x1 = xmax1; dotbuffer.y1 = xmax1;
	GiperDot.push_back(dotbuffer);
	//===================================================================
	//Генерация границ - сверхструктуры
	//===================================================================
	gran = 0.1;
	gransetka = 0.25;
	double step = (1. - 2 * gran)*xmax1 / DotsCount;
	for (int i = 0; i <= DotsCount; i++)
	{
		dotbuffer.Q = Qmax;
		dotbuffer.x1 = gran * xmax1 + RandPlus;
		dotbuffer.y1 = gran * xmax1 + i * step + RandPlus;
		GiperDot.push_back(dotbuffer);
		dotbuffer.Q = Qmin;
		dotbuffer.x1 = (1 - gran)*xmax1 + RandPlus;
		GiperDot.push_back(dotbuffer);
	}
	for (int i = 1; i <= DotsCount - 1; i++)
	{
		dotbuffer.Q = 0;
		dotbuffer.y1 = gran * xmax1 + RandPlus;
		dotbuffer.x1 = gran * xmax1 + i * step + RandPlus;
		GiperDot.push_back(dotbuffer);
		dotbuffer.y1 = (1 - gran)*xmax1 + RandPlus;
		GiperDot.push_back(dotbuffer);
	}
	generator(GiperDot, Treug, 1); //генерация триангуляции сверхструктуры
	//===================================================================
	//Рекурсия. Делоне
	//===================================================================
	DeloneDot.clear();
	step = (1. - 2 * gransetka)*xmax1 / DotsCount;
	vector <Dot> BufferDot;// точки новой триангуляции
	vector <Dot> BufferDot2;//уникальные точки новой триангуляции
	vector <Tringl> BufferTreug;// новые треугольники
	for (int i = 0; i <= DotsCount; i++)
	{
		for (int j = 0; j <= DotsCount; j++)
		{
			BufferDot.clear();
			BufferDot2.clear();
			dotbuffer.x1 = gransetka * xmax1 + j * step + RandPlus;
			dotbuffer.y1 = gransetka * xmax1 + i * step + RandPlus;
			dotbuffer.lock = 0;
			DeloneDot.push_back(dotbuffer);
			//DotC.push_back(dotbuffer);//New Task
			for (int k = 0; k < Treug.size(); k++)
			{
				double D = RadiusOkr(Treug[k].C, dotbuffer);
				if (D <= Treug[k].RadiusO) // точки внутри круга!
				{
					BufferDot.push_back(Treug[k].T1);
					BufferDot.push_back(Treug[k].T2);
					BufferDot.push_back(Treug[k].T3);
					Treug.erase(Treug.begin() + k);
					k--;
				}

			}
			bool rrr;
			for (int k = 0; k < BufferDot.size(); k++)
			{
				rrr = false;
				for (int m = 0; m < BufferDot2.size(); m++)
				{
					if (BufferDot[k].x1 == BufferDot2[m].x1 && BufferDot[k].y1 == BufferDot2[m].y1)
					{
						rrr = true;
						break;
					}
				}
				if (!rrr)BufferDot2.push_back(BufferDot[k]);
			}
			BufferDot2.push_back(dotbuffer);
			generator(BufferDot2, BufferTreug, 0);
			for (int k = 0; k < BufferTreug.size(); k++)
			{
				if ((dotbuffer.x1 == BufferTreug[k].T1.x1 && dotbuffer.y1 == BufferTreug[k].T1.y1) || (dotbuffer.x1 == BufferTreug[k].T2.x1 && dotbuffer.y1 == BufferTreug[k].T2.y1) || (dotbuffer.x1 == BufferTreug[k].T3.x1 && dotbuffer.y1 == BufferTreug[k].T3.y1))
				{
					Treug.push_back(BufferTreug[k]);
				}
			}

		}
	}

	for (int i = 0; i < Treug.size(); i++)
	{
		if (Treug[i].T1.lock && Treug[i].T2.lock && Treug[i].T3.lock)
		{
			Treug.erase(Treug.begin() + i);
			i--;
		}
	}
	////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
	//Находим уникальные точки по триангуляции
	FullDots.resize(0);
	UnicFullDots.resize(0);
	for (int i = 0; i < Treug.size(); i++)
	{
		FullDots.push_back(Treug[i].T1); // запоминаем вершины всех треугольников	
		FullDots.push_back(Treug[i].T2);
		FullDots.push_back(Treug[i].T3);
	}
	FindUnicDots(FullDots, UnicFullDots); // запоминаем неповторяющиеся точки
	for (int i = 0; i < UnicFullDots.size(); i++) // присваем каждой точке свой индекс
	{
		UnicFullDots[i].index = i;
	}
	//======================================
	//Поиндексное заполнение треугольников уникальными точками
	for (int i = 0; i < Treug.size(); i++)
	{
		for (int j = 0; j < UnicFullDots.size(); j++) // заопоминаем индексы уникальных точек
		{
			if (EquallyDots(Treug[i].T1, UnicFullDots[j]))
			{
				Treug[i].T1.index = UnicFullDots[j].index;
				continue;
			}
			if (EquallyDots(Treug[i].T2, UnicFullDots[j]))
			{
				Treug[i].T2.index = UnicFullDots[j].index;
				continue;
			}
			if (EquallyDots(Treug[i].T3, UnicFullDots[j]))
			{
				Treug[i].T3.index = UnicFullDots[j].index;
				continue;
			}
		}
	}
	//======================================
	for (int i = 0; i < Treug.size(); i++)
	{
		AddNewNeighbors(UnicFullDots[Treug[i].T1.index], Treug[i].T2); // запоминаем индексы ближайших соседей ( + уникальные точки)
		AddNewNeighbors(UnicFullDots[Treug[i].T1.index], Treug[i].T3);

		AddNewNeighbors(UnicFullDots[Treug[i].T2.index], Treug[i].T1);
		AddNewNeighbors(UnicFullDots[Treug[i].T2.index], Treug[i].T3);

		AddNewNeighbors(UnicFullDots[Treug[i].T3.index], Treug[i].T1);
		AddNewNeighbors(UnicFullDots[Treug[i].T3.index], Treug[i].T2);
	}
	//=======================================
	//Polugons
////////////////////////////////////////////////////////
	Polygons.clear();
	for (int i = 0; i < UnicFullDots.size(); i++)
	{
		Voronoi buffer;
		for (int j = 0; j < Treug.size(); j++)
		{
			if (EquallyDots(UnicFullDots[i], Treug[j].T1)
				|| EquallyDots(UnicFullDots[i], Treug[j].T2)
				|| EquallyDots(UnicFullDots[i], Treug[j].T3))
			{
				buffer.V.push_back(Treug[j].C);
			}
		}
		////////////////////////////////////////////////////////
		//упорядочивание точек в полигоне
		///////////////////////////////////////////////////////
		Dot Cpolygon;// центр полигона
		Cpolygon.x1 = 0;
		Cpolygon.y1 = 0;
		for (int j = 0; j < buffer.V.size(); j++)
		{
			Cpolygon.x1 += buffer.V[j].x1;
			Cpolygon.y1 += buffer.V[j].y1;
		}
		Cpolygon.x1 /= buffer.V.size();
		Cpolygon.y1 /= buffer.V.size();
		vector<pair<Dot, double>> A;
		for (int j = 0; j < buffer.V.size(); j++)
		{
			double x0 = (buffer.V[j].x1 - Cpolygon.x1);
			double y0 = (buffer.V[j].y1 - Cpolygon.y1);
			double second = atan2(y0, x0);
			pair<Dot, double> buf; buf.first = buffer.V[j]; buf.second = second;
			A.push_back(buf);
		}
		BubleSortAtan(A);
		buffer.V.clear();
		for (int j = 0; j < A.size(); j++)
		{
			buffer.V.push_back(A[j].first);
		}
		Polygons.push_back(buffer);
	}

	////////////////////////////////////////////////////////
	//=======================================
	Invalidate();
}

void CParticleDriftDlg::OnBnClickedButton1() //Button2
{
	if (timer_ptr != NULL)
	{
		KillTimer(timer_ptr); timer_ptr = NULL;
	}
	else
	{
		ETimer = Etest;
		bits.clear();
		//tics = 0;
		timer_ptr = SetTimer(10, 50, NULL);
	}
	Invalidate();
}

void CParticleDriftDlg::OnBnClickedButton2()//VAH
{
	UpdateData(1);
	VAH.clear();
	VAH.resize(Edots);
	xmax2 = Edots;
	double EStep = (Emax - Emin) / Edots;
	for (int i = 0; i < Edots; i++)
	{
		bufferVAH = 0;
		bits.clear();
		ETimer = Emin + EStep * i;
		bits.clear();
		for (int j = 0; j < tics_count; j++)
		{
			TimerFunc();
		}
		VAH[i] = bufferVAH;
		ymax2 = 0;
		for (int j = 0; j < VAH.size(); j++)
		{
			if (VAH[j] > ymax2)ymax2 = VAH[j];
		}
		OnPaint();
	}
	UpdateData(0);
}


void CParticleDriftDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

void CParticleDriftDlg::OnTimer(UINT_PTR nIDEvent)
{
	UpdateData(1);
	TimerFunc();
	InvalidateRect(&PicSignal1);
}

void CParticleDriftDlg::TimerFunc()
{
	double gran_bits = 0.3;
	for (int i = 0; i < bitscount; i++)
	{
		bit bufdot;
		bufdot.koor.x1 = gran_bits * xmax1;
		bufdot.koor.y1 = gran_bits * ymax1 + (1 - 2 * gran_bits) * ymax1 * rand() * 1. / RAND_MAX;
		double speed = (double)xmax1 / 300.;
		double azimut = -M_PI / 4 + (M_PI / 2) * rand() * 1. / RAND_MAX;
		bufdot.speedX = speed * cos(azimut);
		bufdot.speedY = speed * sin(azimut);
		bits.push_back(bufdot);
	}
	//================================================
	for (int i = 0; i < Polygons.size(); i++)
	{
		double sum = 0;
		for (int j = 0; j < bits.size(); j++)
		{
			if (isInside(Polygons[i].V, bits[j].koor, Polygons[i].V.size()))
			{
				sum += bits[j].Q;
			}
		}
		sum /= polygon_area(Polygons[i].V);
		UnicFullDots[i].Q = sum;
	}
	//Копирование значений зараядов в точках из вектора "c" в вектор Treug
	for (int i = 0; i < Treug.size(); i++)
	{
		for (int j = 0; j < UnicFullDots.size(); j++)
		{
			if (EquallyDots(Treug[i].T1, UnicFullDots[j]))
				Treug[i].T1.Q = UnicFullDots[j].Q;
		}
		for (int j = 0; j < UnicFullDots.size(); j++)
		{
			if (EquallyDots(Treug[i].T2, UnicFullDots[j]))
				Treug[i].T2.Q = UnicFullDots[j].Q;
		}
		for (int j = 0; j < UnicFullDots.size(); j++)
		{
			if (EquallyDots(Treug[i].T3, UnicFullDots[j]))
				Treug[i].T3.Q = UnicFullDots[j].Q;
		}
	}
	////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
	Bj.clear();
	A.clear();
	c.clear(); //вектор неизвестных
	Galerkin(Bj, A, Treug);
	kazf(A, Bj, c, Bj.size(), Bj.size());// находим распределение зарядов (вектор с) методом Качмажа
	for (int i = 0; i < c.size(); i++)
		DeloneDot[i].Q = c[i];
	for (int i = 0; i < DeloneDot.size(); i++)
	{
		for (int j = 0; j < UnicFullDots.size(); j++)
		{
			if (EquallyDots(DeloneDot[i], UnicFullDots[j]))
			{
				UnicFullDots[j].Q = DeloneDot[i].Q;
				continue;
			}
		}
	}
	for (int i = 0; i < bits.size(); i++)
	{
		for (int j = 0; j < Polygons.size(); j++)
		{
			if (Polygons[j].V.size() > 2)
			{
				if (isInside(Polygons[j].V, bits[i].koor, Polygons[j].V.size()))
				{
					double speed = bits[i].Q * ETimer / xmax1;
					bits[i].speedX += speed - bits[i].Q * UnicFullDots[j].Q;
				}
			}
		}
		bits[i].koor.x1 = bits[i].koor.x1 + bits[i].speedX * TimeStep;
		bits[i].koor.y1 = bits[i].koor.y1 + bits[i].speedY * TimeStep;
		if (bits[i].koor.y1< gransetka * ymax1
			|| bits[i].koor.y1 >(1 - gransetka) * ymax1
			|| bits[i].koor.x1 < ((gransetka + gran_bits) / 2) * xmax1)
		{
			bits.erase(bits.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < bits.size(); i++)
	{
		if (bits[i].koor.x1 > (1 - gransetka) * xmax1)
		{
			bufferVAH += bits[i].Q;
			bits.erase(bits.begin() + i);
			i--;
		}
	}
	//tics++;
}
void CParticleDriftDlg::generator(vector <Dot> Koor, vector<Tringl> &Treg, bool lock)
{
	bool OnOff = 0;
	Treg.clear();
	for (int i = 0; i < Koor.size(); i++)
	{
		for (int j = i + 1; j < Koor.size(); j++)
		{
			for (int k = j + 1; k < Koor.size(); k++)
			{
				OnOff = 0;
				Dot Centr;
				KoorCenter(Koor[i], Koor[j], Koor[k], Centr);
				double Radius = RadiusOkr(Centr, Koor[i]);
				for (int p = 0; p < Koor.size(); p++)
				{
					if (p != i && p != j && p != k)
					{
						double D = RadiusOkr(Centr, Koor[p]);
						if (D <= Radius)
						{
							OnOff = 1;
							break;
						}
						else continue;
					}
					else continue;
				}
				if (!OnOff)
				{
					Tringl bufer;
					//	bufer.lock = lock;
					bufer.C = Centr;
					bufer.RadiusO = Radius;
					bufer.T1 = Koor[i];
					bufer.T2 = Koor[j];
					bufer.T3 = Koor[k];
					Treg.push_back(bufer);
				}
			}
		}
	}
}
void CParticleDriftDlg::KoorCenter(Dot T1, Dot T2, Dot T3, Dot &TC)
{
	TC.x1 = 0.5*((T2.x1* T2.x1 - T1.x1* T1.x1 + T2.y1* T2.y1 - T1.y1* T1.y1)*(T3.y1 - T1.y1) - (T3.x1* T3.x1 - T1.x1* T1.x1 + T3.y1* T3.y1 - T1.y1* T1.y1)*(T2.y1 - T1.y1));
	TC.x1 /= ((T2.x1 - T1.x1)*(T3.y1 - T1.y1) - (T3.x1 - T1.x1)*(T2.y1 - T1.y1));

	TC.y1 = 0.5*((T3.x1* T3.x1 - T1.x1* T1.x1 + T3.y1* T3.y1 - T1.y1* T1.y1)*(T2.x1 - T1.x1) - (T2.x1* T2.x1 - T1.x1* T1.x1 + T2.y1* T2.y1 - T1.y1* T1.y1)*(T3.x1 - T1.x1));
	TC.y1 /= ((T2.x1 - T1.x1)*(T3.y1 - T1.y1) - (T3.x1 - T1.x1)*(T2.y1 - T1.y1));
}
double CParticleDriftDlg::RadiusOkr(Dot TC, Dot T)
{
	return sqrt((TC.x1 - T.x1)*(TC.x1 - T.x1) + (TC.y1 - T.y1)*(TC.y1 - T.y1));
}
bool CParticleDriftDlg::EquallyDots(Dot dot1, Dot dot2)
{
	return (dot1.x1 == dot2.x1 && dot1.y1 == dot2.y1);
}
void CParticleDriftDlg::FindUnicDots(vector<Dot> mas1, vector<Dot> &mas2)
{
	mas2.resize(0);
	bool unictrue;//действительно уникальная
	for (int k = 0; k < mas1.size(); k++)
	{
		unictrue = false;
		for (int m = 0; m < mas2.size(); m++)
		{
			if (mas1[k].x1 == mas2[m].x1 && mas1[k].y1 == mas2[m].y1)
			{
				unictrue = true;
				break;
			}
		}
		if (!unictrue)mas2.push_back(mas1[k]);
	}
}
void CParticleDriftDlg::BubleSortAtan(vector<pair<Dot, double>> &A)
{
	pair<Dot, double> temp; // временная переменная для обмена элементов местами
	// Сортировка массива пузырьком
	for (int i = 0; i < A.size() - 1; i++)
	{
		for (int j = 0; j < A.size() - i - 1; j++)
		{
			if (A[j].second > A[j + 1].second)
			{
				// меняем элементы местами
				temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp;
			}
		}
	}
}
double CParticleDriftDlg::polygon_area(vector <Dot> poly)
{
	double sq = 0;
	for (unsigned int n = 0; n < poly.size() - 1; ++n)
	{
		sq += (poly[n].x1 * poly[n + 1].y1) - (poly[n + 1].x1 * poly[n].y1);
	}
	return abs(sq);
}
bool CParticleDriftDlg::AddNewNeighbors(Dot &dot1, Dot dot2)
{
	bool unictrue = true;//действительно уникальная
	for (int i = 0; i < dot1.neighbors.size(); i++)
	{
		if (dot1.neighbors[i] == dot2.index)
		{
			unictrue = false;
			break;
		}
	}
	if (unictrue) dot1.neighbors.push_back(dot2.index);
	return unictrue;
}
void CParticleDriftDlg::Coff_A(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double &AI, double &BI)
{
	AI = y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2);
	BI = z1 * (x2 - x3) + z2 * (x3 - x1) + z3 * (x1 - x2);
}
void CParticleDriftDlg::Coff_B(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double &AJ, double &BJ)
{
	AJ = y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2);
	BJ = z1 * (x2 - x3) + z2 * (x3 - x1) + z3 * (x1 - x2);
}
double CParticleDriftDlg::Coff_A_B(int i, int j, int h)
{
	double Ai = 0;
	double Bi = 0;
	double Aj = 0;
	double Bj = 0;
	double S = 0;
	UnicFullDots[i].z1 = 1.0;
	Coff_A(UnicFullDots[Treug[h].T1.index].x1, UnicFullDots[Treug[h].T1.index].y1, UnicFullDots[Treug[h].T1.index].z1, UnicFullDots[Treug[h].T2.index].x1, UnicFullDots[Treug[h].T2.index].y1, UnicFullDots[Treug[h].T2.index].z1, UnicFullDots[Treug[h].T3.index].x1,
		UnicFullDots[Treug[h].T3.index].y1, UnicFullDots[Treug[h].T3.index].z1, Ai, Bi);
	UnicFullDots[i].z1 = 0;
	UnicFullDots[j].z1 = 1;
	Coff_B(UnicFullDots[Treug[h].T1.index].x1, UnicFullDots[Treug[h].T1.index].y1, UnicFullDots[Treug[h].T1.index].z1, UnicFullDots[Treug[h].T2.index].x1, UnicFullDots[Treug[h].T2.index].y1, UnicFullDots[Treug[h].T2.index].z1, UnicFullDots[Treug[h].T3.index].x1,
		UnicFullDots[Treug[h].T3.index].y1, UnicFullDots[Treug[h].T3.index].z1, Aj, Bj);
	UnicFullDots[j].z1 = 0;
	S = 1.0;
	return S * S + Ai * Aj + S * S*Bi*Bj;
}
void CParticleDriftDlg::Galerkin(vector<double> &BJ, vector<double> &A, vector<Tringl>Treugol)
{
	int countA = 0;
	int countB = 0;
	//index.clear();
	for (int i = 0; i < UnicFullDots.size(); i++)
	{
		UnicFullDots[i].z1 = 0;
	}
	int ggg = 0;
	for (int i = 0; i < UnicFullDots.size(); i++) 
	{
		if (UnicFullDots[i].lock == false)
		{
			for (int j = 0; j < UnicFullDots.size(); j++)
			{
				if (UnicFullDots[j].lock == false)
				{
					countA++;
					A.resize(countA);
					A[countA - 1] = 0;
					if (i == j)
					{
						for (int h = 0; h < Treug.size(); h++)
						{
							if (Treug[h].T1.index == i || Treug[h].T2.index == i || Treug[h].T3.index == i)
							{
								double area =polygon_area(Polygons[i].V);
								A[countA - 1] += Coff_A_B(i, j, h) - (4 / 3)*M_PI*UnicFullDots[i].Q*polygon_area(Polygons[i].V);
							}
						}
					}
					else
					{

						int tmp = 0;
						for (int p = 0; p < UnicFullDots[i].neighbors.size(); p++)
						{
							if (UnicFullDots[i].neighbors[p] == j)
							{
								tmp++;
								for (int h = 0; h < Treug.size(); h++)
								{
									if ((Treug[h].T1.index == i || Treug[h].T2.index == i || Treug[h].T3.index == i) && (Treug[h].T1.index == j || Treug[h].T2.index == j || Treug[h].T3.index == j))
									{
										A[countA - 1] += Coff_A_B(i, j, h);
									}
								}
							}
						}
						if (tmp == 0)
						{
							A[countA - 1] = 0;
						}
					}
				}
			}
			countB++;
			BJ.resize(countB);
			BJ[countB - 1] = 0;
			int tmp = 0;
			
			for (int p = 0; p < UnicFullDots[i].neighbors.size(); p++)
			{
				if (UnicFullDots[UnicFullDots[i].neighbors[p]].lock == true || UnicFullDots[UnicFullDots[i].neighbors[p]].Q!=0)
				{
					tmp++;
					int j = UnicFullDots[i].neighbors[p];
					for (int h = 0; h < Treug.size(); h++) 
					{
						if ((Treug[h].T1.index == i || Treug[h].T2.index == i || Treug[h].T3.index == i) && (Treug[h].T1.index == j || Treug[h].T2.index == j || Treug[h].T3.index == j)) 
						{
							double aaa = UnicFullDots[UnicFullDots[i].neighbors[p]].Q;
							double bbb = Coff_A_B(i, j, h);
							BJ[countB - 1] += aaa*bbb;
						}
					}
				}
			}
			if (tmp == 0) 
			{
				BJ[countB - 1] = 0;
			}
		}
	}
}
void CParticleDriftDlg::kazf(vector<double> a, vector<double> b, vector<double>  &x, int nn, int ny)
{
	x.clear();
	x.resize(nn);
	// nn - количество неизвестных;  ny - количество уравнений
	double eps = 1.e-4f;
	//double s;
	int i, j, k;
	double s1, s2, fa1, t;
	double *x1;

	x1 = new double[nn];

	x[0] = 0.5f;
	for (i = 1; i < nn; i++)  x[i] = 0.f;

	s1 = s2 = 1.f;
	while (s1 > eps*s2)
	{
		for (i = 0; i < nn; i++) x1[i] = x[i];
		for (i = 0; i < ny; i++)
		{
			s1 = 0.0;
			s2 = 0.0;
			for (j = 0; j < nn; j++)
			{
				fa1 = a[i*nn + j];
				s1 += fa1 * x[j];
				s2 += fa1 * fa1;
			}
			t = (b[i] - s1) / s2;
			for (k = 0; k < nn; k++)    x[k] += a[i*nn + k] * t;
		}

		s1 = 0.0;
		s2 = 0.0;
		for (i = 0; i < nn; i++)
		{
			s1 += (x[i] - x1[i]) * (x[i] - x1[i]);
			s2 += x[i] * x[i];
		}
		s1 = (double)sqrt(s1);
		s2 = (double)sqrt(s2);
	}
	delete[] x1;
}


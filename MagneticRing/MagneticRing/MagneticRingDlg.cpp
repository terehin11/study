
// MagneticRingDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "MagneticRing.h"
#include "MagneticRingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CMagneticRingDlg
#define KOORD(x,y) (xp1*((x)-xmin1)),(yp1*((y)-ymax1)) 
#define KOORD_Signal1Ell(x,y) (xp1*((x)-xmin1)+3),(yp1*((y)-ymax1)+3),(xp1*((x)-xmin1)-3),(yp1*((y)-ymax1)-3)   // для пересчета координат


CMagneticRingDlg::CMagneticRingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAGNETICRING_DIALOG, pParent)
	, sizeDot(50)
	, L(20)
	, D(5)
	, R(10)
	, alpha(45)
	, offsetX(0)
	, offsetY(15)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMagneticRingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, sizeDot);
	DDX_Text(pDX, IDC_EDIT2, L);
	DDX_Text(pDX, IDC_EDIT3, D);
	DDX_Text(pDX, IDC_EDIT4, R);
	DDX_Text(pDX, IDC_EDIT5, alpha);
	DDX_Text(pDX, IDC_EDIT7, offsetX);
	DDX_Text(pDX, IDC_EDIT6, offsetY);
}

BEGIN_MESSAGE_MAP(CMagneticRingDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMagneticRingDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMagneticRingDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMagneticRingDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Обработчики сообщений CMagneticRingDlg

BOOL CMagneticRingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	srand(time(NULL));
	PicWndMult = GetDlgItem(IDC_STATIC);
	PicDcMult = PicWndMult->GetDC();
	PicWndMult->GetClientRect(&PicMult);
	setka_pen.CreatePen(  //для сетки
		PS_DASH,    //сплошная линия
		//PS_DOT,     //пунктирная
		1,      //толщина 1 пиксель
		RGB(0, 0, 0));  //цвет серый

	osi_pen.CreatePen(   //координатные оси
		PS_SOLID,    //сплошная линия
		3,      //толщина 3 пикселя
		RGB(138, 138, 138));   //цвет черный

	graf_pen.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		1,      //толщина 2 пикселя
		RGB(0, 0, 0));   //цвет черный

	graf_pen1.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		1,      //толщина 2 пикселя
		RGB(0, 0, 0));   //цвет розовый


	graf_penred.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		1,      //толщина 2 пикселя
		RGB(255, 0, 0));   //цвет черный

	graf_pengreen.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		4,      //толщина 2 пикселя
		RGB(0, 150, 0));   //цвет черный

	graf_penblue.CreatePen(   //график
		PS_SOLID,    //сплошная линия
		6,      //толщина 2 пикселя
		RGB(0, 0, 255));   //цвет черный

	xmax1 = 100;			//Максимальное значение х1
	ymax1 = 100;			//Максимальное значение y1
	xmin1 = 0;			//Минимальное значение х1
	ymin1 = 0;			//Минимальное значение y1
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMagneticRingDlg::OnPaint()
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

		xp1 = ((double)(PicMult.Width()) / (xmax1 - xmin1));			// Коэффициенты пересчёта координат по x1
		yp1 = -((double)(PicMult.Height()) / (ymax1 - ymin1));


		// для MULT
		PicDcMult->FillSolidRect(&PicMult, RGB(200, 200, 200));    // закрашиваем фон
		PicDcMult->SelectObject(&osi_pen);		// выбираем ручку

		if (OnOff)
		{
			PicDcMult->SelectObject(&graf_penblue);
			for (int i = 0; i < dot.size(); i++)
			{
				PicDcMult->MoveTo(KOORD(dot[i].x, dot[i].y));
				PicDcMult->LineTo(KOORD(dot[i].x + 0.05, dot[i].y + 0.05));
			}

			PicDcMult->SelectObject(&graf_pen);
			for (int i = 0; i < treugTriang.size(); i++)
			{
				PicDcMult->MoveTo(KOORD(treugTriang[i].dot1.x, treugTriang[i].dot1.y));
				PicDcMult->LineTo(KOORD(treugTriang[i].dot2.x, treugTriang[i].dot2.y));

				PicDcMult->MoveTo(KOORD(treugTriang[i].dot2.x, treugTriang[i].dot2.y));
				PicDcMult->LineTo(KOORD(treugTriang[i].dot3.x, treugTriang[i].dot3.y));

				PicDcMult->MoveTo(KOORD(treugTriang[i].dot3.x, treugTriang[i].dot3.y));
				PicDcMult->LineTo(KOORD(treugTriang[i].dot1.x, treugTriang[i].dot1.y));
			}
		}
		if (OnOff1)
		{
			PicDcMult->SelectObject(&graf_penblue);
			for (int i = 0; i < cirDot.size(); i++)
			{
				PicDcMult->MoveTo(KOORD(cirDot[i].x, cirDot[i].y));
				PicDcMult->LineTo(KOORD(cirDot[i].x + 0.05, cirDot[i].y + 0.05));
			}
			PicDcMult->SelectObject(&graf_pen);
			for (int i = 0; i < treugTriang.size(); i++)
			{
				PicDcMult->MoveTo(KOORD(treugTriang[i].dot1.x, treugTriang[i].dot1.y));
				PicDcMult->LineTo(KOORD(treugTriang[i].dot2.x, treugTriang[i].dot2.y));

				PicDcMult->MoveTo(KOORD(treugTriang[i].dot2.x, treugTriang[i].dot2.y));
				PicDcMult->LineTo(KOORD(treugTriang[i].dot3.x, treugTriang[i].dot3.y));

				PicDcMult->MoveTo(KOORD(treugTriang[i].dot3.x, treugTriang[i].dot3.y));
				PicDcMult->LineTo(KOORD(treugTriang[i].dot1.x, treugTriang[i].dot1.y));
			}
		}
		if (OnOff2)
		{
			PicDcMult->SelectObject(&graf_penblue);
			//for (int i = 0; i < edges.size(); i++)
			//{
			//	PicDcMult->MoveTo(KOORD(edges[i].x, edges[i].y));
			//	PicDcMult->LineTo(KOORD(edges[i].x + 0.05, edges[i].y + 0.05));
			//}


			//for (int i = 0; i < first.size(); i++)
			//{
			//	PicDcMult->MoveTo(KOORD(first[i].x, first[i].y));
			//	PicDcMult->LineTo(KOORD(first[i].x + 0.05, first[i].y + 0.05));
			//}
			for (int i = 0; i < newDots.size(); i++)
			{
				PicDcMult->MoveTo(KOORD(newDots[i].x, newDots[i].y));
				PicDcMult->LineTo(KOORD(newDots[i].x + 0.05, newDots[i].y + 0.05));
			}

			PicDcMult->SelectObject(&graf_pen);
			for (int i = 0; i < treugTriang.size(); i++)
			{
				PicDcMult->MoveTo(KOORD(treugTriang[i].dot1.x, treugTriang[i].dot1.y));
				PicDcMult->LineTo(KOORD(treugTriang[i].dot2.x, treugTriang[i].dot2.y));

				PicDcMult->MoveTo(KOORD(treugTriang[i].dot2.x, treugTriang[i].dot2.y));
				PicDcMult->LineTo(KOORD(treugTriang[i].dot3.x, treugTriang[i].dot3.y));

				PicDcMult->MoveTo(KOORD(treugTriang[i].dot3.x, treugTriang[i].dot3.y));
				PicDcMult->LineTo(KOORD(treugTriang[i].dot1.x, treugTriang[i].dot1.y));
			}
		}
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMagneticRingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMagneticRingDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);

	dot.resize(sizeDot);
	// TODO: добавьте свой код обработчика уведомлений
	for (int i = 0; i < dot.size(); i++)
	{

		dot[i].x = RandDots(xmin1 + 0.1, xmax1 - 0.1);
		dot[i].y = RandDots(ymin1 + 0.1, ymax1 - 0.1);
	}
	OnOff = TRUE;
	OnOff1 = FALSE;
	OnOff2 = FALSE;
	TrianglBust(dot);
	Invalidate();
	UpdateData(FALSE);
}















double CMagneticRingDlg::RandDots(double a, double b)
{
	return (double)rand() / RAND_MAX * (b - a) + a;
}

void CMagneticRingDlg::KoordCenter(Dot dot1, Dot dot2, Dot dot3, Dot &centrDots)
{
	centrDots.x = 0.5*((dot2.x* dot2.x - dot1.x* dot1.x + dot2.y* dot2.y - dot1.y* dot1.y)*(dot3.y - dot1.y) - (dot3.x* dot3.x - dot1.x* dot1.x + dot3.y* dot3.y - dot1.y* dot1.y)*(dot2.y - dot1.y));
	centrDots.x /= ((dot2.x - dot1.x)*(dot3.y - dot1.y) - (dot3.x - dot1.x)*(dot2.y - dot1.y));

	centrDots.y = 0.5*((dot3.x* dot3.x - dot1.x* dot1.x + dot3.y* dot3.y - dot1.y* dot1.y)*(dot2.x - dot1.x) - (dot2.x* dot2.x - dot1.x* dot1.x + dot2.y* dot2.y - dot1.y* dot1.y)*(dot3.x - dot1.x));
	centrDots.y /= ((dot2.x - dot1.x)*(dot3.y - dot1.y) - (dot3.x - dot1.x)*(dot2.y - dot1.y));
}

double CMagneticRingDlg::RadiusCircle(Dot centrDots, Dot dot)
{
	return sqrt((centrDots.x - dot.x)*(centrDots.x - dot.x) + (centrDots.y - dot.y)*(centrDots.y - dot.y));
}

vector<triang> CMagneticRingDlg::TrianglBust(vector<Dot> dot)
{
	//treugTriang.clear();
	vector<triang> tre;
	for (int i = 0; i < dot.size(); i++)
	{
		for (int j = i + 1; j < dot.size(); j++)
		{
			for (int k = j + 1; k < dot.size(); k++)
			{
				if (i == j || j == k || i == k) continue;
				bool odaaa = 1;
				Dot centrRadius;
				KoordCenter(dot[i], dot[j], dot[k], centrRadius);
				double radCircle = RadiusCircle(centrRadius, dot[i]);

				for (int b = 0; b < dot.size(); b++)
				{
					if (b != i && b != j && b != k)
					{
						double extra = RadiusCircle(centrRadius, dot[b]);
						if (extra <= radCircle)
						{
							odaaa = 0;
							break;
						}
					}
				}
				if (odaaa)
				{
					triang buf;
					buf.dot1 = dot[i];
					buf.dot2 = dot[j];
					buf.dot3 = dot[k];
					buf.center = centrRadius;
					buf.radius = radCircle;

					tre.push_back(buf);
				}


			}
		}
	}
	return tre;
}

//Главная функция
vector<triang> CMagneticRingDlg::TriangRecursive(vector<Dot> dots)
{
	vector<triang> triang;


	Dot mtp;
	newDots.clear();
	OnOff2 = TRUE;
	double x = xmax1 * 0.1;
	double y = ymax1 * 0.1;
	int l = 0;

	for (int j = ymin1 + 15; j < ymax1 - y; j += 5)
	{
		for (int i = xmin1 + 15; i < xmax1 - x; i += 5)
		{
			Dot tmp;
			tmp.x = i;
			tmp.y = j;
			if (!(isInside(cirDot, tmp, cirDot.size()) || isInside(cirDot1, tmp, cirDot.size())))
			{
				mtp.x = i;
				mtp.y = j;
				newDots.push_back(mtp);
				l++;
			}
		}
	}

	for (int i = 0; i < newDots.size(); i++)
	{
		newDots[i].x += RandDots(-0.1, 0.1);
		newDots[i].y += RandDots(-0.1, 0.1);
	}
	treugTriang = TrianglBust(dots);
	//OnPaint();

	for (int j = 0; j < newDots.size(); j++)
	{
		treugTriang1.clear();
		Search(newDots[j], treugTriang);
		OnPaint();
		//Sleep(500);
	}

	for (int i = 0; i < treugTriang.size(); i++)
	{
		if (treugTriang[i].del)
		{
			treugTriang.erase(treugTriang.begin() + i);
			i--;
		}
	}


	return treugTriang;
}



//Поиск и удаление ненужных треугольников 
void CMagneticRingDlg::Search(Dot newDots, vector<triang> &treugTriang)
{
	vector<Dot> ddd;
	vector<Dot> unicddd;
	vector<triang>tringlBufer;
	for (int i = 0; i < treugTriang.size(); i++)
	{
		double rast = RadiusCircle(newDots, treugTriang[i].center);
		if (rast <= treugTriang[i].radius)
		{
			ddd.push_back(treugTriang[i].dot1);
			ddd.push_back(treugTriang[i].dot2);
			ddd.push_back(treugTriang[i].dot3);
			treugTriang.erase(treugTriang.begin() + i);
			i--;
		}
	}
	bool unic;
	for (int i = 0; i < ddd.size(); i++)
	{
		unic = false;
		for (int j = 0; j < unicddd.size(); j++)
		{
			if (unicddd[j].x == ddd[i].x && unicddd[j].y == ddd[i].y)
			{
				unic = true;
				break;
			}
		}
		if (!unic)unicddd.push_back(ddd[i]);
	}
	unicddd.push_back(newDots);
	tringlBufer = TrianglBust(unicddd);

	for (int i = 0; i < tringlBufer.size(); i++)
	{
		if ((newDots.x == tringlBufer[i].dot1.x && newDots.y == tringlBufer[i].dot1.y) || (newDots.x == tringlBufer[i].dot2.x && newDots.y == tringlBufer[i].dot2.y) || (newDots.x == tringlBufer[i].dot3.x && newDots.y == tringlBufer[i].dot3.y))
		{
			if (!(isInside(cirDot, tringlBufer[i].center, cirDot.size()) || isInside(cirDot1, tringlBufer[i].center, cirDot1.size())))
			{
				tringlBufer[i].del = 0;
				treugTriang.push_back(tringlBufer[i]);
			}
		}
	}


}



void CMagneticRingDlg::OnBnClickedButton2()
{
	// TODO: добавьте свой код обработчика уведомлений

	UpdateData(TRUE);

	double xc = 50;
	double yc = 50;


	double phi;
	int i = 0;

	Dot tmp;
	double koef = (2 * R + D) / 2;

	for (phi = M_PI / 2; phi <= 3 * M_PI / 2; phi += 10 * (M_PI / 180))
	{
		tmp.x = xc - L / 2 + R * cos(phi);
		tmp.y = yc + R * sin(phi);
		cirDot.push_back(tmp);
		i++;
	}

	for (phi = 3 * M_PI / 2; phi >= M_PI / 2; phi -= 10 * (M_PI / 180))
	{
		tmp.x = xc - L / 2 + (R + D) * cos(phi);
		tmp.y = yc + (R + D) * sin(phi);
		cirDot.push_back(tmp);
		i++;
	}

	int j = 0;

	for (phi = M_PI / 2; phi < 3 * M_PI / 2; phi += 36 * (M_PI / 180))
	{
		tmp.x = xc - L / 2 + ((2 * R + D) / 2) * cos(phi);
		tmp.y = yc + ((2 * R + D) / 2)* sin(phi);
		vnutr.push_back(tmp);
		j++;
	}

	i = 0;
	for (phi = 3 * M_PI / 2; phi <= 5 * M_PI / 2; phi += 10 * (M_PI / 180))
	{
		tmp.x = xc + L / 2 + offsetX + R * cos(phi + alpha * M_PI / 180);
		tmp.y = yc + offsetY + R * sin(phi + alpha * M_PI / 180);
		cirDot1.push_back(tmp);
		i++;
	}

	for (phi = 5 * M_PI / 2; phi >= 3 * M_PI / 2; phi -= 10 * (M_PI / 180))
	{
		tmp.x = xc + offsetX + L / 2 + (R + D) * cos(phi + alpha * M_PI / 180);
		tmp.y = yc + offsetY + (R + D) * sin(phi + alpha * M_PI / 180);
		cirDot1.push_back(tmp);
		i++;
	}



	for (phi = 3 * M_PI / 2; phi < 5 * M_PI / 2; phi += 36 * (M_PI / 180))
	{
		tmp.x = xc + offsetX + L / 2 + (2 * R + D) / 2 * cos(phi + alpha * M_PI / 180);
		tmp.y = yc + offsetY + (2 * R + D) / 2 * sin(phi + alpha * M_PI / 180);
		vnutr.push_back(tmp);
		j++;
	}



	for (i = 0; i < cirDot.size(); i++)
	{
		cirDot[i].x += RandDots(-0.05, 0.05);
		cirDot[i].y += RandDots(-0.05, 0.05);
	}

	for (i = 0; i < cirDot1.size(); i++)
	{
		cirDot1[i].x += RandDots(-0.05, 0.05);
		cirDot1[i].y += RandDots(-0.05, 0.05);
	}
	for (i = 0; i < vnutr.size(); i++)
	{
		vnutr[i].x += RandDots(-0.05, 0.05);
		vnutr[i].y += RandDots(-0.05, 0.05);
	}

	OnOff1 = TRUE;
	OnOff = FALSE;
	OnOff2 = FALSE;
	//Invalidate();
	UpdateData(FALSE);
}


void CMagneticRingDlg::OnBnClickedButton3()
{
	UpdateData(TRUE);
	edges.clear();
	opora.clear();
	first.clear();
	dot.clear();

	//dot.resize(sizeDot);
	double x = xmax1 * 0.1;
	double y = ymax1 * 0.1;
	double j = 0;
	Dot tmp;


	//////////////////////////////////////////////////////
	////////////////////// Границы ///////////////////////
	for (double i = (xmin1 + x); i < (xmax1 - x); i += 5)
	{

		tmp.x = i;
		tmp.y = ymin1 + y;
		edges.push_back(tmp);
		j++;
	}
	for (double i = (ymin1 + y); i <= (ymax1 - y); i += 5)
	{

		tmp.x = xmax1 - x;
		tmp.y = i;
		edges.push_back(tmp);
		j++;
	}

	for (double i = (xmin1 + x); i < (xmax1 - x); i += 5)
	{

		tmp.x = i;
		tmp.y = ymax1 - y;
		edges.push_back(tmp);
		j++;
	}

	for (double i = (ymin1 + y); i < (ymax1 - y); i += 5)
	{

		tmp.x = xmin1 + x;
		tmp.y = i;
		edges.push_back(tmp);
		j++;
	}
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////

	for (int i = 0; i < edges.size(); i++)
	{
		edges[i].x += RandDots(-0.05, 0.05);
		edges[i].y += RandDots(-0.05, 0.05);
	}



	Dot up, down, left, right;
	up.x = xmax1 / 2;
	up.y = ymax1 - y / 4;

	down.x = xmax1 / 2;
	down.y = ymin1 + y / 4;

	left.x = xmin1 + x / 4;
	left.y = ymax1 / 2;

	right.x = xmax1 - x / 4;
	right.y = ymax1 / 2;

	opora.push_back(up);
	opora.push_back(down);
	opora.push_back(left);
	opora.push_back(right);
	j = 0;
	double a = 0.1;
	double step = 5;
	Dot xyilo;
	//for (int i = xmin1 + x + a; i < xmax1 - x - a; i += step)
	//{
	//	for (int j = ymin1 + y + a; j < ymax1 - y - a; j += step)
	//	{
	//		xyilo.x = i;
	//		xyilo.y = j;
	//		dot.push_back(xyilo);
	//	}
	//}

	//for (int i = 0; i < dot.size(); i++)
	//{
	//	dot[i].x += RandDots(-0.05, 0.05);
	//	dot[i].y += RandDots(-0.05, 0.05);
	//}
	OnBnClickedButton2();
	//first.insert(first.begin(), dot.begin(), dot.end());
	first.insert(first.end(), vnutr.begin(), vnutr.end());
	first.insert(first.end(), cirDot1.begin(), cirDot1.end());
	first.insert(first.end(), cirDot.begin(), cirDot.end());
	first.insert(first.end(), edges.begin(), edges.end());
	first.insert(first.end(), opora.begin(), opora.end());

	TriangRecursive(first);
	//TrianglBust(first);

	OnOff1 = FALSE;
	OnOff = FALSE;
	OnOff2 = TRUE;
	Invalidate();
	UpdateData(FALSE);
}

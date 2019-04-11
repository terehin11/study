
// ImRecAMPDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "ImRecAMP.h"
#include "ImRecAMPDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CImRecAMPDlg



CImRecAMPDlg::CImRecAMPDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMRECAMP_DIALOG, pParent)
	, noise(50)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImRecAMPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_picture_control, drawItemsReal);
	DDX_Control(pDX, IDC_picture_control2, drawItemsFiltr);
	DDX_Control(pDX, IDC_picture_control2, drawItemsNoise);
	DDX_Text(pDX, IDC_EDIT1, noise);
//	DDX_Control(pDX, IDC_picture_control, lpd1);
}

BEGIN_MESSAGE_MAP(CImRecAMPDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CImRecAMPDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CImRecAMPDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CImRecAMPDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Обработчики сообщений CImRecAMPDlg

BOOL CImRecAMPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	OnOff = false;
	drawItemsNoise.noise = noise;
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CImRecAMPDlg::OnPaint()
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
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CImRecAMPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CImRecAMPDlg::OnBnClickedButton1()
{
	drawItemsReal.noiseDraw = false;
	
	//drawItemsReal.Invalidate();
	//drawItemsNoise.Invalidate();
	graphics a;
	a.img = true;
	drawItemsReal.img = true;
	//a.DrawItem(lpd1);

	drawItemsReal.mepaint();
}


void CImRecAMPDlg::OnBnClickedButton2()
{
	// TODO: добавьте свой код обработчика уведомлений
	drawItemsNoise.noiseDraw = true;
	//drawItemsReal.img = false;
	drawItemsNoise.mepaint();
	//a.noiseDraw = true;
	//a.Invalidate();
}

void CImRecAMPDlg::OnBnClickedButton3()
{
	//graphics a;
	drawItemsFiltr.noiseFiltr = true;
	drawItemsFiltr.mepaint();
	//a.noiseFiltr = true;

}


void CImRecAMPDlg::Median_filter()
{
	vector<unsigned> picture;
	int stride = 2;
	vector<vector<unsigned>> window;
	//window.resize(9);
	int x,y;
	int wid = 0, hei = 0;
	for (int i = 0; i < wid -2 ; i++)
	{
		for (int j = 0; j < hei -2 ; j++)
		{
			vector<unsigned> buf;
			for (int m = i; m < 3 + i; m++)
			{
				for (int n = 0; n < 3 + j; n++)
				{
					buf.push_back(picture[m*(3 + j) + n]);
				}
			}
			window.push_back(buf);
		}
	}
	for (int i = 0; i < window.size(); i++)
	{
		int size = window[i].size();
		quickSort(window[i], window[i][0], window[i][size]);
	}

	//достаем 4 элемент после сортировки и записываем его назад в picture 
}

// Функция быстрой сортировки
void CImRecAMPDlg::quickSort(vector<unsigned> numbers, unsigned left, unsigned right)
{
	int pivot; // разрешающий элемент
	int l_hold = left; //левая граница
	int r_hold = right; // правая граница
	pivot = numbers[left];
	while (left < right) // пока границы не сомкнутся
	{
		while ((numbers[right] >= pivot) && (left < right))
			right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			numbers[left] = numbers[right]; // перемещаем элемент [right] на место разрешающего
			left++; // сдвигаем левую границу вправо 
		}
		while ((numbers[left] <= pivot) && (left < right))
			left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			numbers[right] = numbers[left]; // перемещаем элемент [left] на место [right]
			right--; // сдвигаем правую границу вправо 
		}
	}
	numbers[left] = pivot; // ставим разрешающий элемент на место
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
		quickSort(numbers, left, pivot - 1);
	if (right > pivot)
		quickSort(numbers, pivot + 1, right);
}




// ImRecAMPDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "ImRecAMP.h"
#include "ImRecAMPDlg.h"
#include "afxdialogex.h"

#include <chrono>
using namespace std::chrono;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CImRecAMPDlg

CImRecAMPDlg::CImRecAMPDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMRECAMP_DIALOG, pParent)
	, noise(5)
	, original(nullptr)
	, copy(nullptr)
	, copy_filtr(nullptr)
	, width_window(3)
	, height_window(3)
	, time_study_proc(0)
	, time_study_accel(0)
	, size_study(5)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// инициализация датчика случайных чисел
	srand((unsigned)time(nullptr));
}

void CImRecAMPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_picture_control, drawItemsReal);
	DDX_Control(pDX, IDC_picture_control3, drawItemsFiltr);
	DDX_Control(pDX, IDC_picture_control2, drawItemsNoise);
	DDX_Text(pDX, IDC_EDIT1, noise);

	DDX_Text(pDX, IDC_EDIT2, width_window);
	DDX_Text(pDX, IDC_EDIT3, height_window);
	DDX_Text(pDX, IDC_EDIT4, time_study_proc);
	DDX_Text(pDX, IDC_EDIT5, time_study_accel);
	DDX_Text(pDX, IDC_EDIT6, size_study);
}

BEGIN_MESSAGE_MAP(CImRecAMPDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CImRecAMPDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CImRecAMPDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CImRecAMPDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CImRecAMPDlg::OnBnClickedButton4)
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

void CImRecAMPDlg::DrawRealImage()
{
	Gdiplus::Bitmap img(L"Lenna_(test_image).bmp");
	original = img.Clone(0, 0, img.GetWidth(), img.GetHeight(), img.GetPixelFormat());

	drawItemsReal.SetBitmap(original);
}

void CImRecAMPDlg::Noise(unsigned* ptr)
{
	// количество зашумляемых пикселей
	int num = width * height * noise / 100;

	for (int i = 0; i < num; ++i)
	{
		// координата X пикселя
		int x = rand() % width;

		// координата Y пикселя
		int y = rand() % height;

		ptr[x * height + y] = randRGB();
	}
}
void CImRecAMPDlg::Med_Filtr(unsigned* ptrNoise, unsigned* prtFiltr)
{

	int median_number = (height_window + width_window - 1) / 2;
	int offset_to_center = (height_window - 1) / 2;
#pragma omp parallel for
	for (int i = 0; i < width - width_window-1; i++)
	{
		for (int j = 0; j < height - height_window-1; j++)
		{
			vector<MyRGB> buf;

			for (int m = i; m < width_window + i; m++)
			{
				for (int n = j; n < height_window + j; n++)
				{
					MyRGB rgb;
					unsigned pixel = ptrNoise[m * height + n];
					rgb.B = pixel & 0xFF;
					rgb.G = (pixel >> 8) & 0xFF;
					rgb.R = (pixel >> 16) & 0xFF;
					buf.push_back(rgb);
				}
			}

			SortSel(buf);
			prtFiltr[(i + offset_to_center) * height + (j + offset_to_center)] = buf[median_number].B | (buf[median_number].G << 8) | (buf[median_number].R << 16) | 0xFF000000;
		}
	}
	


}

void CImRecAMPDlg::DrawNoiseImage()
{
	width = original->GetWidth();
	height = original->GetHeight();
	copy_rect = Rect(0, 0, width, height);
	copy = original->Clone(copy_rect, PixelFormat32bppRGB);

	Status st = Lock(noiseBitmapData, copy, copy_rect);
	ptrFirstPixelNoise = (unsigned*)noiseBitmapData.Scan0;
	Noise(ptrFirstPixelNoise);
	st = Unlock(noiseBitmapData, copy);

	drawItemsNoise.SetBitmap(copy);

}

void CImRecAMPDlg::DrawFiltrImage()
{
	copy_filtr = copy->Clone(copy_rect, PixelFormat32bppRGB);

	Status st = Lock(noiseBitmapData, copy, copy_rect);
	ptrFirstPixelNoise = (unsigned*)noiseBitmapData.Scan0;

	st = Lock(filtrBitmapData, copy_filtr, copy_rect);
	ptrFirstPixelFiltr = (unsigned*)filtrBitmapData.Scan0;

	SetCursor(LoadCursor(nullptr, IDC_WAIT));
	Med_Filtr(ptrFirstPixelNoise, ptrFirstPixelFiltr);
	SetCursor(LoadCursor(nullptr, IDC_ARROW));

	st = Unlock(filtrBitmapData, copy_filtr);
	st = Unlock(noiseBitmapData, copy);

	drawItemsFiltr.SetBitmap(copy_filtr);
}

void CImRecAMPDlg::OnBnClickedButton1()
{
	DrawRealImage();
}

void CImRecAMPDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	DrawNoiseImage();
}

void CImRecAMPDlg::OnBnClickedButton3()
{
	DrawFiltrImage();
}

void CImRecAMPDlg::OnBnClickedButton4()
{
	UpdateData(TRUE);
	auto start = system_clock::now();
	for (int i = 0; i < size_study; i++)
	{
		DrawNoiseImage();
		DrawFiltrImage();
	}
	auto stop = system_clock::now();
	time_study_proc = duration_cast<milliseconds>(stop - start).count() / size_study;
	UpdateData(FALSE);
}

Status CImRecAMPDlg::Lock(BitmapData &bd, Bitmap* bmp, Rect rect)
{
	Status stat = bmp->LockBits(&rect, ImageLockModeRead | ImageLockModeWrite, PixelFormat32bppRGB, &bd);
	return stat;
}

Status CImRecAMPDlg::Unlock(BitmapData &bd, Bitmap* bmp)
{
	Status stat = bmp->UnlockBits(&bd);
	return stat;
}

unsigned CImRecAMPDlg::randRGB()
{
	unsigned noiseRGB;
	unsigned char R = rand() % 256;
	unsigned char G = rand() % 256;
	unsigned char B = rand() % 256;
	noiseRGB = B | (G << 8) | (R << 16) | 0xFF000000;
	return noiseRGB;
}

void CImRecAMPDlg::SortSel(vector<MyRGB>& A)
{

	int length = (int)A.size();
	// Перебираем каждый элемент массива
		// (кроме последнего, он уже будет отсортирован к тому времени, когда мы до него доберемся)
	for (int startIndex = 0; startIndex < length - 1; ++startIndex)
	{
		// В переменной smallestIndex хранится индекс наименьшего значения, которое мы нашли в этой итерации
		// Начинаем с того, что наименьший элемент в этой итерации - это первый элемент (индекс 0)
		int smallestIndexB = startIndex;
		int smallestIndexG = startIndex;
		int smallestIndexR = startIndex;

		// Затем ищем элемент поменьше в остальной части массива
		for (int currentIndex = startIndex + 1; currentIndex < length; ++currentIndex)
		{
			// Если мы нашли элемент, который меньше нашего наименьшего элемента
			if (A[currentIndex].B < A[smallestIndexB].B)
			{// запоминаем его
				smallestIndexB = currentIndex;
			}
			if (A[currentIndex].G < A[smallestIndexG].G)
			{// запоминаем его
				smallestIndexG = currentIndex;
			}
			if (A[currentIndex].R < A[smallestIndexR].R)
			{// запоминаем его
				smallestIndexR = currentIndex;
			}
		}

		// smallestIndex теперь наименьший элемент 
				// меняем местами наше начальное наименьшее число с тем, которое мы обнаружили
		swap(A[startIndex].B, A[smallestIndexB].B);
		swap(A[startIndex].G, A[smallestIndexG].G);
		swap(A[startIndex].R, A[smallestIndexR].R);
	}
}



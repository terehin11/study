
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
	, noise(20)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImRecAMPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_picture_control, drawItemsReal);
	DDX_Control(pDX, IDC_picture_control3, drawItemsFiltr);
	DDX_Control(pDX, IDC_picture_control2, drawItemsNoise);
	DDX_Text(pDX, IDC_EDIT1, noise);
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
	Image img(L"Lenna_(test_image).bmp", 0);
	drawItemsReal.im = img.Clone();
}

void CImRecAMPDlg::Noise(unsigned* ptr)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (RandomBool(noise))
			{
				ptr[i * height + j] = randRGB();
			}
		}
	}
}
void CImRecAMPDlg::Med_Filtr(unsigned* ptrNoise, unsigned* prtFiltr)
{
	vector<vector<MyRGB>> window;
	//window.resize(9);
	int x, y;
	for (int i = 0; i < width - 2; i++)
	{
		for (int j = 0; j < height - 2; j++)
		{
			vector<MyRGB> buf;

			buf.resize(0);
			int t = 0;
			for (int m = i; m < 3 + i; m++)
			{
				for (int n = j; n < 3 + j; n++)
				{

					if (j > 0)
					{										
						if (t == 4)
						{
							prtFiltr[m * (3 + j) + n] = buf[t].B  | (buf[t].G << 8)  | (buf[t].R << 16) | 0xFF000000;
						}
					}
					MyRGB rgb;
					rgb.B = ptrNoise[m * (3 + j) + n] & 0xFF;
					rgb.G = (ptrNoise[m * (3 + j) + n] >> 8) & 0xFF;
					rgb.R = (ptrNoise[m * (3 + j) + n] >> 16) & 0xFF;
					buf.push_back(rgb);		
					t++;
				}
			}
			SortSel(buf);
		}
	}
}



void CImRecAMPDlg::DrawNoiseImage()
{
	Bitmap imagenew(L"Lenna_(test_image).bmp");
	Bitmap* tmp;
	width = imagenew.GetWidth();
	height = imagenew.GetHeight();
	copy_rect = Rect(0, 0, width, height);
	copy = imagenew.Clone(copy_rect, PixelFormat32bppRGB);
	st = Lock(noiseBitmapData, copy, copy_rect);
	ptrFirstPixelNoise = (unsigned*)noiseBitmapData.Scan0;
	Noise(ptrFirstPixelNoise);
	st = Unlock(noiseBitmapData, copy);
	drawItemsNoise.noiseIm = copy;

}

void CImRecAMPDlg::DrawFiltrImage()
{
	st = Lock(noiseBitmapData, copy, copy_rect);
	copy_filtr = copy->Clone(copy_rect, PixelFormat32bppRGB);
	st = Lock(filtrBitmapData, copy_filtr, copy_rect);
	ptrFirstPixelFiltr = (unsigned*)filtrBitmapData.Scan0;
	Med_Filtr(ptrFirstPixelNoise, ptrFirstPixelFiltr);
	st = Unlock(filtrBitmapData, copy_filtr);
	drawItemsFiltr.filtrIm = copy_filtr;
}

void CImRecAMPDlg::OnBnClickedButton1()
{

	drawItemsReal.img = true;

	DrawRealImage();
	drawItemsReal.mepaint();
}


void CImRecAMPDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	drawItemsReal.img = false;
	drawItemsNoise.noiseDraw = true;
	DrawNoiseImage();
	drawItemsNoise.mepaint();

}

void CImRecAMPDlg::OnBnClickedButton3()
{
	drawItemsReal.img = false;
	drawItemsNoise.noiseDraw = false;
	drawItemsFiltr.noiseFiltr = true;
	DrawFiltrImage();
	drawItemsFiltr.mepaint();


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

bool CImRecAMPDlg::RandomBool(double ver)
{
	double a = 100 * rand() / RAND_MAX;
	if (a < ver) return 1;
	else return 0;
}

unsigned CImRecAMPDlg::randRGB()
{
	unsigned noiseRGB;
	unsigned char tmp = rand() % 256;
	noiseRGB = tmp | (tmp << 8) | (tmp << 16) | 0xFF000000;
	return noiseRGB;
}

void CImRecAMPDlg::SortSel(vector<MyRGB>& A)
{

	int length = A.size();
	// Перебираем каждый элемент массива
		// (кроме последнего, он уже будет отсортирован к тому времени, когда мы до него доберемся)
	for (int startIndex = 0; startIndex < length - 1; ++startIndex)
	{
		// В переменной smallestIndex хранится индекс наименьшего значения, которое мы нашли в этой итерации
		// Начинаем с того, что наименьший элемент в этой итерации - это первый элемент (индекс 0)
		int smallestIndex = startIndex;

		// Затем ищем элемент поменьше в остальной части массива
		for (int currentIndex = startIndex + 1; currentIndex < length; ++currentIndex)
		{
			// Если мы нашли элемент, который меньше нашего наименьшего элемента
			if (A[currentIndex].B < A[smallestIndex].B)
			{// запоминаем его
				smallestIndex = currentIndex;
			}
			if (A[currentIndex].G < A[smallestIndex].G)
			{// запоминаем его
				smallestIndex = currentIndex;
			}
			if (A[currentIndex].R < A[smallestIndex].R)
			{// запоминаем его
				smallestIndex = currentIndex;
			}
		}

		// smallestIndex теперь наименьший элемент 
				// меняем местами наше начальное наименьшее число с тем, которое мы обнаружили
		swap(A[startIndex].B, A[smallestIndex].B);
		swap(A[startIndex].G, A[smallestIndex].G);
		swap(A[startIndex].R, A[smallestIndex].R);
	}
}

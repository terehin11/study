#include "stdafx.h"
#include "graphics.h"
#include "vector"



ULONG_PTR token;

IMPLEMENT_DYNAMIC(graphics, CStatic);

graphics::graphics()
{
	GdiplusStartupInput input;
	Status s;
	s = GdiplusStartup(&token, &input, NULL);
	if (s != Ok)
	{
		MessageBox(L"Error", L"", MB_OK | MB_ICONERROR);
	}
	width = 0;
	height = 0;
}


graphics::~graphics()
{
	GdiplusShutdown(token);
}
BEGIN_MESSAGE_MAP(graphics, CStatic)
END_MESSAGE_MAP()


unsigned graphics::randRGB()
{
	unsigned noiseRGB;
	unsigned char tmp = rand() % 256;
	noiseRGB = tmp | (tmp << 8) | (tmp << 16) | 0xFF000000;
	return noiseRGB;
}




void SortSel(vector<MyRGB>& A)
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


bool RandomBool(double ver)
{
	double a = 100 * rand() / RAND_MAX;
	if (a < ver) return 1;
	else return 0;
}

//Функция получения размера Picture Control
Rect graphics::GetRect(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Rect  wndRect(
		0,
		0,
		lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left + 1,
		lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top + 1);
	return wndRect;
}

//Функция зашумления
void graphics::Noise(unsigned *ptr)
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


//Функция Медианного фильтра
void graphics::Med_Filtr(unsigned* ptrNoise, unsigned* prtFiltr)
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

			for (int m = i; m < 3 + i; m++)
			{
				for (int n = j; n < 3 + j; n++)
				{
					MyRGB rgb;
					rgb.B = ptrNoise[m * (3 + j) + n] & 0xFF;
					rgb.G = (ptrNoise[m * (3 + j) + n] >> 8) & 0xFF;
					rgb.R = (ptrNoise[m * (3 + j) + n] >> 16) & 0xFF;
					buf.push_back(rgb);
				}
			}
			window.push_back(buf);

		}
	}
	vector<vector<MyRGB>> tmp;

	for (int i = 0; i < window.size(); i++)
	{
		tmp.push_back(window[i]);
	}
	for (int i = 0; i < window.size(); i++)
	{
		SortSel(tmp[i]);
	}

	for (int i = 0; i < tmp[i].size(); i++)
	{
		window[i][4].B = tmp[i][4].B;
		window[i][4].G = tmp[i][4].G;
		window[i][4].R = tmp[i][4].R;
	}

	int p = 0;
	for (int i = 0; i < width - 2; i++)
	{
		for (int j = 0; j < height - 2; j++)
		{
			int t = 0;
			for (int m = i; m < 3 + i; m++)
			{
				for (int n = j; n < 3 + j; n++)
				{
					if (t == 4)
					{
						prtFiltr[m * (3 + j) + n] = window[p][t].B | (window[p][t].G << 8) | (window[p][t].R << 16) | 0xFF000000;

					}
					t++;
				}
			}
			p++;
		}
	}

}


void graphics::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	Graphics gr(lpDrawItemStruct->hDC);

	Rect wndRect = GetRect(lpDrawItemStruct);

	Bitmap imagenew(L"Lenna_(test_image).bmp");

	if (img)
	{
		Image im(L"Lenna_(test_image).bmp", 0);
		gr.DrawImage(&im, wndRect);
	}

	//Получения размера картинки
	width = imagenew.GetWidth();
	height = imagenew.GetHeight();
	//Запись в переменную Rect
	Rect copy_rect(0, 0, width, height);
	//Клонируем наше изображения
	Bitmap *copy = imagenew.Clone(copy_rect, PixelFormat32bppRGB);
	Status st;
	Gdiplus::BitmapData newbitmapData;


	//Блокируем биты
	st = copy->LockBits(&copy_rect, ImageLockModeRead | ImageLockModeWrite, PixelFormat32bppRGB, &newbitmapData);
	//Получаем указатель на первый элемент в памяти
	unsigned* ptrFirstPixel1;
	ptrFirstPixel1 = (unsigned*)newbitmapData.Scan0;
	if (noiseDraw)
	{



		Noise(ptrFirstPixel1);

		st = copy->UnlockBits(&newbitmapData);

		gr.DrawImage(copy, wndRect);
	}
	if (noiseFiltr)
	{
		st = copy->LockBits(&copy_rect, ImageLockModeRead, PixelFormat32bppRGB, &newbitmapData);
		Bitmap* copy_filter = copy->Clone(copy_rect, PixelFormat32bppRGB);
		unsigned* ptrFirstPixelFilter;
		Gdiplus::BitmapData newbitmapDataFiltr;
		st = copy_filter->LockBits(&copy_rect, ImageLockModeRead | ImageLockModeWrite, PixelFormat32bppRGB, &newbitmapDataFiltr);

		ptrFirstPixelFilter = (unsigned*)newbitmapDataFiltr.Scan0;

		Med_Filtr(ptrFirstPixel1, ptrFirstPixelFilter);
		st = copy_filter->UnlockBits(&newbitmapDataFiltr);

		gr.DrawImage(copy_filter, wndRect);
		delete copy_filter;
	}
	delete copy;
}






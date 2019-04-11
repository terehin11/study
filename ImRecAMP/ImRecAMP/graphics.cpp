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


unsigned randRGB()
{
	unsigned noiseRGB;
	unsigned char tmp = rand() % 256;
	noiseRGB = tmp | (tmp << 8) | (tmp << 16) | 0xFF000000;
	return noiseRGB;
}

//
//Bitmap Median_filter(BitmapData bitmapData,Rect copy_rect, Bitmap btmp)
//{
//	Bitmap *copy = btmp.Clone(copy_rect, PixelFormat32bppRGB);
//	Gdiplus::Bitmap *bitmapData;
//	Status st = copy->LockBits(&copy_rect, ImageLockModeRead|ImageLockModeWrite, PixelFormat32bppRGB, &bitmapData);	
//	unsigned* ptrFirstPixel1;
//	
//	ptrFirstPixel1 = (unsigned*)bitmapData.Scan0;
//
//	vector<unsigned> picture;
//	int stride = 2;
//	vector<vector<unsigned>> window;
//	//window.resize(9);
//	int x,y;
//	int wid = 0, hei = 0;
//	for (int i = 0; i < wid -2 ; i++)
//	{
//		for (int j = 0; j < hei -2 ; j++)
//		{
//			vector<unsigned> buf;
//			for (int m = i; m < 3 + i; m++)
//			{
//				for (int n = 0; n < 3 + j; n++)
//				{
//					buf.push_back(ptrFirstPixel1[m*(3 + j) + n]);
//				}
//			}
//			window.push_back(buf);
//		}
//	}
//	for (int i = 0; i < window.size(); i++)
//	{
//		int size = window[i].size();
//		quickSort(window[i], window[i][0], window[i][size]);
//	}
//
//	for(int i =0; i < wid - 2;i++)
//	{
//		for(int j = 0 ; j < hei - 2; j++)
//		{
//			
//		}
//	}
//	//достаем 4 элемент после сортировки и записываем его назад в picture 
//}
//
// Функция быстрой сортировки
void quickSort(vector<unsigned> numbers, unsigned left, unsigned right)
{
	unsigned pivot; // разрешающий элемент
	unsigned l_hold = left; //левая граница
	unsigned r_hold = right; // правая граница
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


void BubleSort(vector<MyRGB>& A)
{
	unsigned temp; // временная переменная для обмена элементов местами
	
	// Сортировка массива пузырьком
	for (int i = 0; i < A.size() - 1; i++)
	{
		for (int j = 0; j < A.size() - i - 1; j++)
		{
			if (A[j].B > A[j + 1].B)
			{
				// меняем элементы местами
				temp = A[j].B;
				A[j].B = A[j + 1].B;
				A[j + 1].B = temp;
			}
		}
	}
	for (int i = 0; i < A.size() - 1; i++)
	{
		for (int j = 0; j < A.size() - i - 1; j++)
		{
			if (A[j].G > A[j + 1].G)
			{
				// меняем элементы местами
				temp = A[j].G;
				A[j].G = A[j + 1].G;
				A[j + 1].G = temp;
			}
		}
	}
	for (int i = 0; i < A.size() - 1; i++)
	{
		for (int j = 0; j < A.size() - i - 1; j++)
		{
			if (A[j].R > A[j + 1].R)
			{
				// меняем элементы местами
				temp = A[j].R;
				A[j].R = A[j + 1].R;
				A[j + 1].R = temp;
			}
		}
	}
}


bool RandomBool(double ver)
{
	double a = 100*rand() / RAND_MAX ;
	if (a < ver) return 1;
	else return 0;
}


Rect graphics::GetRect(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Rect  wndRect(
		0,
		0,
		lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left + 1,
		lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top + 1);
	return wndRect;
}

void graphics::Noise(unsigned *ptr)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (RandomBool(noise))
			{
				ptr[i * height + j] = ::randRGB();
			}
		}
	}
}

void graphics::GetWeightHeight(Bitmap image)
{
	width = image.GetWidth();
	height = image.GetHeight();
}
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
		BubleSort(tmp[i]);
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
					prtFiltr[m * (3 + j) + n] = window[p][t].B | (window[p][t].G << 8) | (window[p][t].R << 16) | 0xFF000000;
					t++;
				}
			}
			p++;
		}
	}

}


void graphics::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	///////���� ����� ���������/////
	Graphics gr(lpDrawItemStruct->hDC);

	// ������� ����
	Rect wndRect = GetRect(lpDrawItemStruct);

	Bitmap imagenew(L"Lenna_(test_image).bmp");
	
	if (img)
	{
		Image im(L"Lenna_(test_image).bmp", 0);
		//gr.DrawI
		gr.DrawImage(&im, wndRect);
	}

	// ������� �����������
	//GetWeightHeight(imagenew);
	
	width = imagenew.GetWidth();
	height = imagenew.GetHeight();
	Rect copy_rect(0, 0, width, height);
	Bitmap *copy = imagenew.Clone(copy_rect, PixelFormat32bppRGB);
	Status st;

	unsigned* ptrFirstPixel1;
	if (noiseDraw)
	{
		Gdiplus::BitmapData newbitmapData;
		st = copy->LockBits(&copy_rect, ImageLockModeRead | ImageLockModeWrite, PixelFormat32bppRGB, &newbitmapData);

		ptrFirstPixel1 = (unsigned*)newbitmapData.Scan0;
		Noise(ptrFirstPixel1);

		st = copy->UnlockBits(&newbitmapData);

		gr.DrawImage(copy, wndRect);

		if (noiseFiltr)
		{
			Bitmap* copy_filter = copy->Clone(copy_rect, PixelFormat32bppRGB);
			unsigned* ptrFirstPixelFilter;
			Gdiplus::BitmapData newbitmapDataFiltr;
			st = copy_filter->LockBits(&copy_rect, ImageLockModeRead | ImageLockModeWrite, PixelFormat32bppRGB, &newbitmapDataFiltr);

			ptrFirstPixelFilter = (unsigned*)newbitmapDataFiltr.Scan0;

			Med_Filtr(ptrFirstPixel1, ptrFirstPixelFilter);
			st = copy_filter->UnlockBits(&newbitmapDataFiltr);
			/////////////////////////////////////////////////////
			gr.DrawImage(copy_filter, wndRect);
			delete copy_filter;
		}
	}
	


	delete copy;

}






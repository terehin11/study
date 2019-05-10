#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool gameOver;//конец игры
const int width = 20;//ширина  поля для игры
const int height = 20;//высота поля для игры
int x, y,//координаты змейки
fruitX, fruitY,//координаты фруктов
score;//счет игры
int tailX[100], tailY[100];
int nTail;//количество элементов в хвосте
enum eDIrection // для определния в какую сторону движется змейка
{
	STOP = 0,
	LEFT,
	RIGHT,
	DOWN,
	UP
};
eDIrection dir;

//Настройка параметров
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	system("cls");//очистка консоли
	//===============================================
	//============Рисование границ и змейки==========
	for (int i = 0; i < width + 1; i++) cout << "#";
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1) cout << "#";
			if (i == y && j == x) cout << "0";
			else if (i == fruitY && j == fruitX) cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						cout << "o";
					}
				}
				if(!print) cout << " ";
			}
		}
		
		cout << endl;
	}
	for (int i = 0; i < width + 1; i++) cout << "#";
	cout << endl;
	//===============================================

	cout << "Score: " << score << endl;

}

//отслеживание нажатий
void Input()
{
	while (_kbhit())//функция возвращает true, если пользователь нажал на кнопку
	{
		switch (_getche())//отслеживает какая кнопка нажата
		{
		case 'a': 
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}

}

//логика игры
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)//обработка хвоста
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x-=1;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	//if (x > width || x < 0 || y > height || y < 0) gameOver = true;
	if (x >= width-1) x = 0;
	else if (x < 0)	x = width - 2;
	if (y >= height) y = 0;
	else if (y < 0)	y = height - 1;

	
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(100);
	}
	cout << endl;
	cout << "Game Over!" << endl;
	system("pause");
	return 0;
}
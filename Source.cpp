#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
using namespace std;

void SaveScore(char Name[10], int Score);
void DisplayScore();

bool gameOver;
const int width = 20;
const int height = 20;
int SnakeX = 0;
int SnakeY = 0;
int fruitX = 0;
int fruitY = 0;
int Score = 0;
int tailX[100] = { 0 };
int tailY[100] = { 0 };
int nTail = 0;
char dir = '\0';

void Setup()
{
	gameOver = false;
	SnakeX = width / 2;
	SnakeY = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	Score = 0;
}
void Draw()
{
	bool print = false;

	system("cls"); //system("clear");
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == SnakeY && j == SnakeX)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width-1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << Score << endl;
}

void Moving()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = 'L';
			break;
		case 'd':
			dir = 'R';
			break;
		case 'w':
			dir = 'U';
			break;
		case 's':
			dir = 'D';
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X = 0;
	int prev2Y = 0;

	tailX[0] = SnakeX;
	tailY[0] = SnakeY;
	for (int i = 1; i < nTail; i++)
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
	case 'L':
		SnakeX--;
		break;
	case 'R':
		SnakeX++;
		break;
	case 'U':
		SnakeY--;
		break;
	case 'D':
		SnakeY++;
		break;
	default:
		break;
	}
	//if (x > width || x < 0 || y > height || y < 0)
	//  gameOver = true;
	if (SnakeX >= width)
		SnakeX = 0; 
	else if (SnakeX < 0) 
		SnakeX = width - 1;

	if (SnakeY >= height) 
		SnakeY = 0;
	else if (SnakeY < 0) 
		SnakeY = height - 1;

	for (int i = 0; i < nTail; i++)
	if (tailX[i] == SnakeX && tailY[i] == SnakeY)
		gameOver = true;

	if (SnakeX == fruitX && SnakeY == fruitY)
	{
		Score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
int main()
{
	char Name[10] = { '\0' };
	int Input = 0;

	Setup();
	while (!gameOver)
	{
		Draw();
		Moving();
		Logic();
		//Sleep(10);
	}

	system("cls");
	cout << "Game Over !!!!...." << endl;
	cout << "Your Final Score: " << Score << endl;
	cout << "Enter your name: ";
	cin >> Name;
	SaveScore(Name, Score);
	cout << "Press 1 to see score board or 0 to quit: ";
	cin >> Input;

	if (Input == 1)
	{
		DisplayScore();
	}
	system("pause");
}

void SaveScore(char Name[10], int Score)
{
	ofstream fout("score.txt", ios::app);
	fout << Name << ' ' << Score << endl;
	fout.close();
}

void DisplayScore()
{
	char FileName[10] = { '\0' };
	int FileScore = 0;

	ifstream fin("score.txt", ios::in);
	system("cls");
	cout << "******************************** Score Board ***********************************" << endl << endl;
	while (1)
	{
		fin >> FileName >> FileScore;
		if (fin.eof())
			break;

		cout << FileName << " " << FileScore << endl;
	}
	fin.close();
}
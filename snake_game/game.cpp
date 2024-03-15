#include <iostream>
#include <vector>
#include <math.h>
#include "keyboard.h"

void tabla(char* tablero)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			tablero[i * 10 + j] = ' ';
			if (i == 19 || i == 0)
			{
				tablero[j] = '|';
				tablero[20 * 10 - 10 + j] = '|';
			}
			else if (j == 0 || j == 9)
			{
				tablero[i * 10] = '-';
				tablero[9 + 10 * i] = '-';
			}
		}
	}
}

void initialpos(std::vector<short>& snake)
{
	snake.push_back(10);
	snake.push_back(5);
}

short last_move = 1;
void move()
{
	if (IsWPressed() || IsAPressed() || IsSPressed() || IsDPressed())
	{
		if (IsWPressed())
		{
			last_move = 1;
		}
		if (IsSPressed())
		{
			last_move = 2;
		}
		if (IsAPressed())
		{
			last_move = 3;
		}
		if (IsDPressed())
		{
			last_move = 4;
		}
	}
}
void moves(std::vector<short>& snake)
{
	switch (last_move)
	{
	case 1://se mueve para arriba
		for (int i = snake.size() - 1; i >= 0; i -= 2)
		{
			if (i == 1)
			{
				snake[i] = snake[i] - 1;
			}
			else
			{
				snake[i] = snake[i - 2];
				snake[i - 1] = snake[i - 3];
			}
		}
		break;
	case 2://se mueve para abajo
		for (int i = snake.size() - 1; i >= 0; i -= 2)
		{
			if (i == 1)
			{
				snake[i] = snake[i] + 1;
			}
			else
			{
				snake[i] = snake[i - 2];
				snake[i - 1] = snake[i - 3];
			}
		}
		break;
	case 3://se mueve para la izquierda
		for (int i = snake.size() - 1; i >= 1; i -= 2)
		{
			if (i == 1)
			{
				snake[i - 1] = snake[i - 1] - 1;
				snake[i] = snake[i];
			}
			else
			{
				snake[i] = snake[i - 2];
				snake[i - 1] = snake[i - 3];
			}
		}
		break;
	case 4://se mueve para la derecha
		for (int i = snake.size() - 1; i >= 1; i -= 2)
		{
			if (i == 1)
			{
				snake[i - 1] = snake[i - 1] + 1;
				snake[i] = snake[i];
			}
			else
			{
				snake[i] = snake[i - 2];
				snake[i - 1] = snake[i - 3];
			}
		}
		break;
	}
}
void rand_apple(std::vector<short>& apple)
{
	if (apple.empty())
	{
		srand(time(NULL));
		apple.push_back(rand() % (19 - 1) + 1);
		srand(time(NULL));
		apple.push_back(rand() % (9 - 1) + 1);
	}
	else
	{
		srand(time(NULL));
		apple[0] = rand() % (19 - 1) + 1;
		srand(time(NULL));
		apple[1] = rand() % (9 - 1) + 1;
	}
}
void update_tabla(char* tablero, std::vector<short>& snake, std::vector<short> apple, int& score)
{
	if (snake[0] == apple[0] && snake[1] == apple[1])
	{
		tablero[apple[0] * 10 + apple[1]] = ' ';
		rand_apple(apple);
		score = score + 15;
		snake.push_back(snake[snake.size() - 2]);
		snake.push_back(snake[snake.size() - 1]);
	}
	tabla(tablero);

	for (int i = 0; i <= snake.size() - 1; i += 2)
	{
		if (i == 0)
		{
			tablero[snake[i] * 10 + snake[i + 1]] = 'X';
		}
		else
		{
			tablero[snake[i] * 10 + snake[i + 1]] = 'x';
		}
	}
	tablero[apple[0] * 10 + apple[1]] = 'O';
}
void verify_game(char* tablero, std::vector<short> snake, bool& start, bool& gameOver)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (i == 19 || i == 0)
			{
				if (tablero[j] == 'X' || tablero[20 * 10 - 10 + j] == 'X')
				{
					start = true;
					gameOver = true;
				}
			}
			else if (j == 0 || j == 9)
			{
				if (tablero[i * 10] == 'X' || tablero[9 + 10 * i] == 'X')
				{
					start = true;
					gameOver = true;
				}
			}
		}
	}
}
void mostrar(char mostrar[20][10], int score)
{
	std::cout << "Score: " << score << std::endl;
	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 20; i++)
		{
			std::cout << mostrar[i][j];
		}
		std::cout << std::endl;
	}
}
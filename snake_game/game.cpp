#define LIMITEI 20
#define LIMITEJ 10
#define ZERO 0
#define UNO 1
#define DOS 2
#define TRES 3
#define CUATRO 4
#define VACIO ' '
#define PIPE '|'
#define GUIONES '-'
#define SnakeX 10
#define SnakeY 5
#define appleScore 15
#define appleX 0
#define appleY 1
#define FRUTA 'O'
#define CABEZA 'X'
#define CUERPO 'x'
#define VACIO ' '
#include <iostream>
#include <vector>
#include <math.h>
#include "keyboard.h"

//Funcion que crea la tabla
void tabla(char* tablero)
{
	//bucles que recorren todo el tablero
	for (short i = ZERO; i < LIMITEI; i++)
	{
		for (short j = ZERO; j < LIMITEJ; j++)
		{
			//Primero lo pondra todo con espaacios vacios
			tablero[i * LIMITEJ + j] = VACIO;
			//Luego se pones los limites
			if (i == LIMITEI - UNO || i == ZERO)
			{
				tablero[j] = PIPE;
				tablero[LIMITEI * LIMITEJ - LIMITEJ + j] = PIPE;
			}
			else if (j == ZERO || j == LIMITEJ - UNO)
			{
				tablero[i * LIMITEJ] = GUIONES;
				tablero[LIMITEJ - UNO + LIMITEJ * i] = GUIONES;
			}
		}
	}
}

//Pone la posicion inicial de la cabeza de la serpiente
void initialpos(std::vector<short>& snake, char* tablero)
{
	snake.push_back(SnakeX);
	snake.push_back(SnakeY);
	//mete la cabeza en el tablero
	tablero[snake[ZERO] * LIMITEJ + snake[ZERO + UNO]] = CABEZA;
}

short last_move = UNO;
//Funcion que actualiza las posiciones del cuerpo del snake
void moves(std::vector<short>& snake)
{
	if (IsWPressed() || IsAPressed() || IsSPressed() || IsDPressed())
	{
		//guarda numero 1
		if (IsWPressed())
		{
			last_move = UNO;
		}
		//guarda numero 2
		if (IsSPressed())
		{
			last_move = DOS;
		}
		//guarda numero 3
		if (IsAPressed())
		{
			last_move = TRES;
		}
		//guarda numero 4
		if (IsDPressed())
		{
			last_move = CUATRO;
		}
	}
	//dependiendo del numero guardado en la varible
	//realmente el unico que se mueve es la cabeza
	//el resto del cuerpo simplemente sigue a la x que tiene delante 
	switch (last_move)
	{
	//se mueve para arriba
	case UNO:
		for (short i = snake.size() - UNO; i >= ZERO; i -= DOS)
		{
			if (i == UNO)
			{
				//le resto una posicion a la cabeza
				snake[i] = snake[i] - UNO;
			}
			else
			{
				//cojo la posicion de la x de adelante y se la pongo a la de atras hasta llegar a la cabeza
				snake[i] = snake[i - DOS];
				snake[i - UNO] = snake[i - TRES];
			}
		}
		break;
	//se mueve para abajo
	case DOS:
		for (short i = snake.size() - UNO; i >= ZERO; i -= DOS)
		{
			if (i == UNO)
			{
				//le sumo una posicion a la cabeza
				snake[i] = snake[i] + UNO;
			}
			else
			{
				//cojo la posicion de la x de adelante y se la pongo a la de atras hasta llegar a la cabeza
				snake[i] = snake[i - DOS];
				snake[i - UNO] = snake[i - TRES];
			}
		}
		break;
	//se mueve para la izquierda
	case TRES:
		for (short i = snake.size() - UNO; i >= UNO; i -= DOS)
		{
			if (i == UNO)
			{
				//le resto una posicion a la cabeza
				snake[i - UNO] = snake[i - UNO] - UNO;
				snake[i] = snake[i];
			}
			else
			{
				//cojo la posicion de la x de adelante y se la pongo a la de atras hasta llegar a la cabeza
				snake[i] = snake[i - DOS];
				snake[i - UNO] = snake[i - TRES];
			}
		}
		break;
	//se mueve para la derecha
	case CUATRO:
		for (short i = snake.size() - UNO; i >= UNO; i -= DOS)
		{
			if (i == UNO)
			{
				//le sumo una posicion a la cabeza
				snake[i - UNO] = snake[i - UNO] + UNO;
				snake[i] = snake[i];
			}
			else
			{
				//cojo la posicion de la x de adelante y se la pongo a la de atras hasta llegar a la cabeza
				snake[i] = snake[i - DOS];
				snake[i - UNO] = snake[i - TRES];
			}
		}
		break;
	}
}

//funcion que coloca la manzana de manera aleatoria
void rand_apple(std::vector<short>& apple)
{
	//el if esta porque sino, el programa petaria ya que la posicion 0 y 1 no estan creadas al principio
	//se hace un random entre el 19 y el 1 para que no se salga de los limites de la x
	//se hace un random entre el 19 y el 1 para que no se salga de los limites de la y
	if (apple.empty())
	{
		srand(time(NULL));
		apple.push_back(rand() % (LIMITEI - DOS) + UNO);
		srand(time(NULL));
		apple.push_back(rand() % (LIMITEJ - DOS) + UNO);
	}
	else
	{
		srand(time(NULL));
		apple[appleX] = rand() % (LIMITEI - DOS) + UNO;
		srand(time(NULL));
		apple[appleY] = rand() % (LIMITEJ - DOS) + UNO;
	}
}

//funcion que acutaliza la tabla
void update_tabla(char* tablero, std::vector<short>& snake, std::vector<short> apple, int& score)
{
	//este if verifica si la serpiente se a comido la manzana
	if (snake[appleX] == apple[appleX] && snake[appleY] == apple[appleY])
	{
		//borra la posicion y vuelve a hacer el random
		tablero[apple[appleX] * LIMITEJ + apple[appleY]] = VACIO;
		rand_apple(apple);
		//suma 15 puntos cada vez que se come una manzana
		score = score + appleScore;
		//mete una x al cuerpo de la serpiente
		snake.push_back(snake[snake.size() - DOS]);
		snake.push_back(snake[snake.size() - UNO]);
	}

	//pone la tabla en blanco
	tabla(tablero);

	//este bucle pone el cuerpo de la serpiente entero en la tabla
	for (short i = ZERO; i <= snake.size() - UNO; i += DOS)
	{
		if (i == ZERO)
		{
			tablero[snake[i] * LIMITEJ + snake[i + UNO]] = CABEZA;
		}
		else
		{
			tablero[snake[i] * LIMITEJ + snake[i + UNO]] = CUERPO;
		}
	}

	//pongo la fruta en el tablero
	tablero[apple[appleX] * LIMITEJ + apple[appleY]] = FRUTA;
}

//funcion que verifica si acaba el juego o no
void gameOver(char* tablero, std::vector<short> snake, bool& start, bool& gameOver)
{
	//este bucle es el mismo que uso para crear la tabla
	//la idea es que si detecta que la cabeza esta en una posicion en la que deberia haber un '-' o '|' finaliza el juego
	for (short i = ZERO; i < LIMITEI; i++)
	{
		for (short j = ZERO; j < LIMITEJ; j++)
		{
			if (i == LIMITEI - UNO || i == ZERO)
			{
				if (tablero[j] == CABEZA || tablero[LIMITEI * LIMITEJ - LIMITEJ + j] == CABEZA)
				{
					start = true;
					gameOver = true;
				}
			}
			else if (j == ZERO || j == LIMITEJ - UNO)
			{
				if (tablero[i * LIMITEJ] == CABEZA || tablero[LIMITEJ - UNO + LIMITEJ * i] == CABEZA)
				{
					start = true;
					gameOver = true;
				}
			}
		}
	}
}

//funcion para mostrar la tabla y puntuacion
void mostrar(char mostrar[LIMITEI][LIMITEJ], int score)
{
	//muestro el score
	std::cout << "Score: " << score << std::endl;
	//muestra la tabla
	for (short j = ZERO; j < LIMITEJ; j++)
	{
		for (short i = ZERO; i < LIMITEI; i++)
		{
			std::cout << mostrar[i][j];
		}
		std::cout << std::endl;
	}
}
#define LIMITEI 20
#define LIMITEJ 10
#pragma once
void tabla(char* tablero);
void mostrar(char mostrar[LIMITEI][LIMITEJ], int score);
void initialpos(std::vector<short>& snake, char* tablero);
void moves(std::vector<short>& snake);
void rand_apple(std::vector<short>& apple);
void update_tabla(char* tablero, std::vector<short>& snake, std::vector<short> apple, int& score);
void gameOver(char* tablero, std::vector<short> snake, bool& start, bool& gameOver);
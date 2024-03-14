#pragma once
void tabla(char* tablero);
void mostrar(char mostrar[20][10]);
void initialpos(std::vector<short>& snake);
void move();
void moves(std::vector<short>& snake);
void rand_apple(std::vector<short>& apple);
void update_tabla(char* tablero, std::vector<short>& snake, std::vector<short> apple);
void verify_game(char* tablero, std::vector<short> snake, bool& start, bool& gameOver);
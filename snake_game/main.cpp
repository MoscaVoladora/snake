#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include "game.h"
#include "keyboard.h"

void main() {
    short framerate = 300;
    char table[20][10];
    std::vector<short> snake;
    std::vector<short> apple;
    bool bGameOver = false;
    bool start = false;
    tabla(table[0]);
    initialpos(snake);
    //While game is not over execute game loop
    std::cout << "PRESIONA W, A, S o D PARA EMPEZAR A JUGAR" << std::endl;
    mostrar(table);
    rand_apple(apple);
    while (!bGameOver) {
        if (IsWPressed() || IsAPressed() || IsSPressed() || IsDPressed())
        {
            while (!start)
            {
                move();
                moves(snake);
                if (table[apple[0]][apple[1]] != 'O')
                {
                    rand_apple(apple);
                }
                update_tabla(table[0], snake, apple);
                //Sleep main thread to control game speed execution
                std::this_thread::sleep_for(std::chrono::milliseconds(framerate));
                mostrar(table);
                if (framerate >= 100)
                {
                    framerate -= 0.5;
                }
                verify_game(table[0], snake, bGameOver, start);
            }
        }
    }
}
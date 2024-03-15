#define framerate 150
#define tableX 20
#define tableY 10
#define tableDefault 0
#define appleX 0
#define appleY 1
#define FRUTA 'O'

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include "game.h"
#include "keyboard.h"

void main() {
    //Hago un char de arrays que guardara la tabla
    char table[tableX][tableY];

    //Vector para guardar las posiciones del snake
    std::vector<short> snake;
    //Vector para guardar la posicion de la manzana
    std::vector<short> apple;

    //guardara la puntuacion del jugador
    int score = 0;

    //bool que sera false hasta que finalice el juego
    bool bGameOver = false;
    //bool que sera false hasta que finalice el juego
    bool start = false;

    //Esta funcion crea la tabla vacia
    tabla(table[tableDefault]);
    //Esta funcion mete la posicion inicial del snake
    initialpos(snake, table[0]);
    //funcion que crea una posicion random a la manzana
    rand_apple(apple);

    std::cout << "PRESIONA W, A, S o D PARA EMPEZAR A JUGAR" << std::endl;
    //funcion que muestra la tabla y la puntucacion
    mostrar(table, score);
    
    //Mientras no detecte que una de las teclas (W,S,D,A) este presionada no empieza
    while (!bGameOver) {
        if (IsWPressed() || IsAPressed() || IsSPressed() || IsDPressed())
        {
            //Mientras no acabe el juego ejecuta el bucle
            while (!start)
            {
                //La funcion, dependiendo de la tecla presionada en la funcion anterior, se movera el snake
                moves(snake);
                //si en la posicion de la manzana es diferente de O que haga random
                if (table[apple[appleX]][apple[appleY]] != FRUTA)
                {
                    rand_apple(apple);
                }
                //Actualiza la tabla en blanco y mete todas las posiciones de snake nuevas y de la manzana en caso de que se la haya comido
                update_tabla(table[tableDefault], snake, apple, score);
                //Sleep main thread to control game speed execution
                std::this_thread::sleep_for(std::chrono::milliseconds(framerate));
                //Muestro la tabla y la puntuacion
                mostrar(table, score);
                //Funcion que verifica si se choca contra un limite del mapa
                gameOver(table[tableDefault], snake, bGameOver, start);
                //Cada vez que acaba el bucle, suma dependiendo de x que tiene el cuerpo
                score = score + snake.size() / 2;
            }
        }
    }
}
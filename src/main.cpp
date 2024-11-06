#define SDL_MAIN_HANDLED
#include <iostream>
#include "List.h"
#include "Queues.h"
#include "Render.h"
#include "Game.h"

void verify(int amount, int minRange, int maxRange, bool& flag);
int main(){
    bool flag = true;
        int amount;
    while(flag){
        std::cout << "Bienvenido al juego serpientes y escaleras" << std::endl;
        std::cout << "Indique la cantidad de jugadores (Rango de jugadores 2 - 4): ";
        std::cin >> amount;
        try{
            verify(amount, 2, 4, flag);
        }catch(std::exception& e){
            std::cout << e.what() << std::endl;
            system("pause");
        }

    }

    flag = true;
        int filas = 0;
    while(flag){
        std::cout << "Ingrese la cantidad de filas que tendra el tablero (minimo 6): ";
        std::cin >> filas;
        try{
            verify(filas, 6, 20, flag);
        }catch(std::exception& e){
            std::cout << e.what() << std::endl; 
            system("pause");
        }
    }

    flag = true;
        int columnas = 0;
    while(flag){
        std::cout << "Ingrese la cantidad de columnas que tendra el tablero (minimo 6): ";
        std::cin >> columnas;
        try{
            verify(columnas, 6, 20, flag);
        }catch(std::exception& e){
            std::cout << e.what() << std::endl;
            system("pause");
        }
    }

    flag = true;
        int amountDice = 0;
    while(flag){
        std::cout << "Ingrese la cantidad de caras que tendra el dado de juego (Rango admitido de dados 6--10): ";
        std::cin >> amountDice;
        try{
            verify(amountDice, 6, 10, flag);
        }catch(std::exception& e){
            std::cout << e.what() << std::endl;
            system("pause");
        }

    }    

    Game game(amount, filas, columnas, amountDice, &game);
        game.mainGame();
    system("pause");
}

void verify(int amount, int minRange, int maxRange, bool& flag){
    if(amount < minRange || amount > maxRange){
        flag = true;
        throw std::out_of_range("La cantidad solicitada deber estar en el rango de: " + std::to_string(minRange) + " -- " + std::to_string(maxRange));
    }else{
        flag = false;
    }
}
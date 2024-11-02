#define SDL_MAIN_HANDLED
#include <iostream>
#include "Queues.h"
#include "Window.h"

void verify(int amount, int minRange, int maxRange, bool& flag);
int main(){
    bool flag = true;
    while(flag){
        int amount;
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
    int filas, columnas;
    std::cout << "Ingrese la cantidad de filas que tendra el tablero (minimo 5): ";
    std::cin >> filas;
    std::cout << "Ingrese la cantidad de columnas que tendra el tablero (minimo 6): ";
    std::cin >> columnas;
    int altura = 720/filas;
    int ancho = 720/columnas;
    int boxNumber = filas * columnas;
    Window ventana1;
    ventana1.principalWindow(altura, ancho, boxNumber);

}

void verify(int amount, int minRange, int maxRange, bool& flag){
    if(amount < minRange || amount > maxRange){
        flag = true;
        throw std::out_of_range("La cantidad de jugadores deber estar en el rango de 2 - 4");
    }else{
        flag = false;
    }
}
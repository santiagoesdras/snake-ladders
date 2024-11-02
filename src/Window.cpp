#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include <string>
#include <array>
#include "Window.h"

int Window::principalWindow(int altura, int ancho, int boxNumber) {
    this->altura = altura;
    this->ancho = ancho;
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "No se pudo inicializar SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Crear una ventana
    SDL_Window* ventana = SDL_CreateWindow("Serpientes y Escaleras", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 720, SDL_WINDOW_SHOWN);
    if (ventana == nullptr) {
        std::cerr << "No se pudo crear la ventana: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Crear un renderizador para dibujar
    SDL_Renderer* renderizador = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    if (renderizador == nullptr) {
        std::cerr << "No se pudo crear el renderizador: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    // Bucle principal
    bool ejecutando = true;
    SDL_Event evento;

    //Definicion del fondo
    SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255); // Color de fondo (negro)
    SDL_RenderClear(renderizador);

    //Dibujado del tablero
    printBackground(renderizador, boxNumber);

    while (ejecutando) {
        // Procesar eventos
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                ejecutando = false;
            }
/*             if (evento.type == SDL_KEYDOWN) {
                if (evento.key.keysym.sym == SDLK_w) {
                    rectangulo.y -= 10;  // Mover el rectángulo hacia arriba al presionar 'W'
                } else if (evento.key.keysym.sym == SDLK_s) {
                    rectangulo.y += 10;  // Mover el rectángulo hacia abajo al presionar 'S'
                } else if (evento.key.keysym.sym == SDLK_a) {
                    rectangulo.x -= 10;  // Mover el rectángulo hacia la izquierda al presionar 'A'
                } else if (evento.key.keysym.sym == SDLK_d) {
                    rectangulo.x += 10;  // Mover el rectángulo hacia la derecha al presionar 'D'
                }
            } */
        }


        // Actualizar el renderizador
        SDL_RenderPresent(renderizador);

        // Controlar la velocidad de actualización
        SDL_Delay(16); // Aproximadamente 60 FPS
    }

    // Limpiar recursos
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(ventana);
    SDL_Quit();

    return 0;
}

void Window::printBackground(SDL_Renderer* render, int boxNumber){
    SDL_Rect rectangulo;
    rectangulo.x = 0;
    rectangulo.y = 0;
    rectangulo.h = altura;
    rectangulo.w = ancho;

    std::array<std::string, 3> rutas = numberBlits(boxNumber);
    while(rectangulo.y != 720){
        while(rectangulo.x != 720){
            SDL_SetRenderDrawColor(render, 175, 36, 245, 255); // Color del rectángulo (morado)
            SDL_RenderFillRect(render, &rectangulo);
            printNumbers(render, rectangulo.x, rectangulo.y, rectangulo.h, rectangulo.w, rutas);
            rectangulo.x += ancho;
            boxNumber--;
            rutas = numberBlits(boxNumber);
            SDL_SetRenderDrawColor(render, 244, 244, 57, 255); // Color del rectángulo (morado)
            SDL_RenderFillRect(render, &rectangulo);
            printNumbers(render, rectangulo.x, rectangulo.y, rectangulo.h, rectangulo.w, rutas);
            rectangulo.x += ancho;
            boxNumber--;
            rutas = numberBlits(boxNumber);
        }
        rectangulo.x = 0;
        rectangulo.y += altura;
        while(rectangulo.x != 720){
            SDL_SetRenderDrawColor(render, 244, 244, 57, 255); // Color del rectángulo (morado)
            SDL_RenderFillRect(render, &rectangulo);
            printNumbers(render, rectangulo.x, rectangulo.y, rectangulo.h, rectangulo.w, rutas);
            rectangulo.x += ancho;
            boxNumber--;
            rutas = numberBlits(boxNumber);
            SDL_SetRenderDrawColor(render, 175, 36, 245, 255); // Color del rectángulo (morado)
            SDL_RenderFillRect(render, &rectangulo);
            printNumbers(render, rectangulo.x, rectangulo.y, rectangulo.h, rectangulo.w, rutas);
            rectangulo.x += ancho;
            boxNumber--;
            rutas = numberBlits(boxNumber);
        }
        rectangulo.x = 0;     
        rectangulo.y += altura;   
    }

}

std::array<std::string, 3> Window::numberBlits(int boxNumber){
    std::string numero = std::to_string(boxNumber);
    std::array<std::string, 3> rutas;
    for(int i = 0; i < 3; i++){
        switch (numero[i]){
            case '0':
            rutas[i] = "numbers/0.bmp";
                break;
            case '1':
            rutas[i] = "numbers/1.bmp";
                break;
            case '2':
            rutas[i] = "numbers/2.bmp";
                break;
            case '3':
            rutas[i] = "numbers/3.bmp";
                break;
            case '4':
            rutas[i] = "numbers/4.bmp";
                break;
            case '5':
            rutas[i] = "numbers/5.bmp";
                break;
            case '6':
            rutas[i] = "numbers/6.bmp";
                break;
            case '7':
            rutas[i] = "numbers/7.bmp";
                break;
            case '8':
            rutas[i] = "numbers/8.bmp";
                break;
            case '9':
            rutas[i] = "numbers/9.bmp";
                break;
            default:
            rutas[i] = "";
                break;
        }
    }
    return rutas;
}

void Window::printNumbers(SDL_Renderer* render, int x, int y, int h, int w, std::array<std::string, 3> rutas){
    int i = 0;
        SDL_Rect dest;
            dest.h = h / 3;
            dest.w = w / 5;
            dest.x = x;
            dest.y = y;
    while(i < 3){ 
            if(rutas[i] == ""){
                break;
            }   
            std::cout << "Digito 1: " << rutas[0] << " Digito 2: " << rutas[1] << " Digito 3: " << rutas[2] << std::endl;
            SDL_Surface* surface = SDL_LoadBMP(rutas[i].c_str());
            if (!surface) {
                std::cerr << "Error al cargar la imagen: " << SDL_GetError() << std::endl;
            }
            // Crear una textura desde la superficie
            SDL_Texture* textura = SDL_CreateTextureFromSurface(render, surface);
            SDL_FreeSurface(surface); // Liberar la superficie después de crear la textura
            if (!textura) {
                std::cerr << "Error al crear la textura: " << SDL_GetError() << std::endl;
            }

            SDL_RenderCopy(render, textura, nullptr, &dest);
            SDL_DestroyTexture(textura);
            dest.x += dest.w;
            i++;
            }
}

#pragma region ImagenEnPantalla
/*      SDL_Surface* surface = SDL_LoadBMP(rutaArchivo);
    if (!surface) {
        std::cerr << "Error al cargar la imagen: " << SDL_GetError() << std::endl;
        return false;
    }

    // Crear una textura desde la superficie
    SDL_Texture* textura = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); // Liberar la superficie después de crear la textura
    if (!textura) {
        std::cerr << "Error al crear la textura: " << SDL_GetError() << std::endl;
        return false;
    } */
#pragma endregion
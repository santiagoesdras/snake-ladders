#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <iostream>

class Window{
    private:
    SDL_Renderer* render;
    int ancho;
    int altura;
    public:
    int principalWindow(int altura, int ancho, int boxNumber);
    void printBackground(SDL_Renderer* render, int boxNumber);
    std::array<std::string, 3> numberBlits(int boxNumber);
    void printNumbers(SDL_Renderer* render, int x, int y, int h, int w, std::array<std::string, 3> rutas);
};
#endif
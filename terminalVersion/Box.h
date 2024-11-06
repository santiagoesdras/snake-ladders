#ifndef BOX_H
#define BOX_H

#include <iostream>

struct Box{
    std::string type;
    int number = 0;
    int coordx, coordy;
    Box* bottom = nullptr;  // Puntero para casillas especiales (serpientes/escuelas)
    Box* next = nullptr;

    Box(int x, int y, int n) : coordx(x), coordy(y), number(n), type("ordinary"), next(nullptr), bottom(nullptr) {}
};

#endif

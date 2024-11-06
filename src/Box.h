#ifndef BOX_H
#define BOX_H

#include <iostream>

        struct Box{
            std::string type;
            int number = 0;
            Box* bottom = nullptr; 
            int coordx = 0;
            int coordy = 0;
            Box* next;
            Box(int x, int y, int n): 
            type("ordinary"), number(n), coordx(x), coordy(y), next(nullptr){}
        };
#endif
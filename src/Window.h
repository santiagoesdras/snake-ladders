#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <SDL.h>
#include "List.h"
#include "Render.h"

class Game;

class Window{
    protected:
        Game* utilities1;
        SDL_Window* window;
        SDL_Renderer* renderer;
        int windowWidth;
        int windowHeight;
        bool playing;
        bool isMenuOpen;
    public:
        Window(int wW, int wH, Game* u);
        ~Window();
        void listener();
        bool initialiceSdl();
        void clearSdl();
};
#endif
#ifndef RENDER_H
#define RENDER_H

class Game;
#include <SDL.h>
#include <vector>
#include "List.h"
#include "Render.h"
#include "Box.h"

class Render{
    private:
        Game* utilities;
        SDL_Renderer* renderer;
        SDL_Texture* backgroundTexture;
        SDL_Texture* playerTexture;
        std::vector<Box*> snakes;
        std::vector<Box*> ladders;
        int windowWidth;
        int windowHeight;
        int boxWidth;
        int boxHeight;
        int boxNumber;
    public:
        Render(int wW, int wH, int rows, int columns, SDL_Renderer* r, Game* u);
        ~Render();
        void listener();
        bool initialiceSdl();
        void clearSdl();
        void renderBackground();
        void renderPlayer(int x, int y);
        void createBackground();
        void printNumbers(int x, int y, int h, int w, std::array<std::string, 3> rutas);
        void printSnakeAndLadders();
        void pauseMenu(bool isMenuOpen);
        SDL_Texture* loadImages();
};
#endif
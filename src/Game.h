#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string.h>
#include <array>
#include <random>
#include <set>
#include <vector>
#include <SDL.h>
#include "List.h"
#include "Box.h"
#include "Window.h"

class Game{
    private:
        Game* utilities;
        Window* window;
        List boxes;
        Box* snakePointers[10];
        Box* ladderPointers[10];
        int amountPlayers;
        int windowWidth;
        int windowHeight;
        int boxWidth;
        int boxHeight;
        int boxNumber;
        int snakesAmount;
        int laddersAmount;
        int diceSize;
        int rows;
        int columns;
        std::uniform_int_distribution<> distrib;
        std::string numberRoutes[10] = 
        {"numbers/0.bmp","numbers/1.bmp","numbers/2.bmp","numbers/3.bmp","numbers/4.bmp","numbers/5.bmp","numbers/6.bmp","numbers/7.bmp","numbers/8.bmp","numbers/9.bmp"};
    public:
        struct SnakeData {
            SDL_Rect rect;
            double angle;
            SDL_Point center;
        };
        Game(int aP, int r, int c, int dS, Game* u);
        std::array<std::string, 3> getNumberRoutes(int boxNumber);
        void mainGame();
        void pushBoxes(int x, int y, int bN);
        void printBoxes();
        void generateSnakesAndLadders();
        void splitSpecialBoxes();
        int releaseDice();
        int randomNumbers(int inferiorLimit, int superiorLimit, std::set<int> &usedNumber);
        std::vector<SnakeData> snakeDimensions();
        int getSnakesAmount();
        int getLaddersAmount();
        int getRows();
        int getColumns();
};
#endif
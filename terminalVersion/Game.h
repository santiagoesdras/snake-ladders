#ifndef GAME_H
#define GAME_H

#include "Queue.h"
#include "Player.h"
#include <vector>

class Game {
private:
    Queue playersQueue;
    int amountPlayers;
    int windowWidth;
    int windowHeight;
    int diceSize;
    bool utilities;

public:
    Game();
    Game(int, int, int, int);
    void startGame();
    void addPlayer(Player* player);
    void processTurn(Player* player);
    void createBackground();
    void releaseDice();
    bool isGameOver();
    void generateSnakeAndLadders();
    void displayBoard();
    void splitSpecialBoxes();
};

#endif

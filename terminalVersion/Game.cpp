#include "Game.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>  // Para usar rand()

Game::Game() : amountPlayers(0), windowWidth(800), windowHeight(600), diceSize(6), utilities(true) {}

Game::Game(int width, int height, int dice, int players) 
    : windowWidth(width), windowHeight(height), diceSize(dice), amountPlayers(players) {}

void Game::startGame() {
    createBackground();
    generateSnakeAndLadders();
    while (!isGameOver()) {
        Player* currentPlayer = playersQueue.dequeue();
        processTurn(currentPlayer);
        playersQueue.enqueue(currentPlayer);
    }
}

void Game::addPlayer(Player* player) {
    playersQueue.enqueue(player);
    amountPlayers++;
}

void Game::processTurn(Player* player) {
    int diceRoll = rand() % diceSize + 1;
    std::cout << player->getName() << " rolled a " << diceRoll << std::endl;
    player->move(diceRoll);

    // Verificar si cae en una serpiente o escalera
    if (player->getPosition() == 5) {
        std::cout << player->getName() << " hit a snake and moved back!" << std::endl;
        player->setPosition(2);  // Ejemplo de retroceder
    } else if (player->getPosition() == 10) {
        std::cout << player->getName() << " climbed a ladder!" << std::endl;
        player->setPosition(15);  // Ejemplo de avanzar
    }
}

void Game::createBackground() {
//Definir las dimensiones y coordenadas para las casillas del tablero
        BackGround background; 
        background.x = (windowWidth - windowHeight) / 2;
        background.y = 0;
    
    //Definir boxNumbertemporal para decrementar
    int tempBoxNumber = boxNumber;

    //Obtener ruta de las imagenes para numerar cada casilla

    //Bucle para imprimir las casillas y los numeros
    while(background.y < windowHeight){
        while(background.x < 1000){
            pushBoxes(background.x, background.y, tempBoxNumber);
            background.x += boxWidth;//Incrementar coordenada X para imprimir la siguiente casilla
            tempBoxNumber--;//Decrementar numero de casilla para renderizar el siguiente numero de casilla

            //Llamada printNumbers para renderizar imagen de los numeros de la casilla
            pushBoxes(background.x, background.y, tempBoxNumber);
            background.x += boxWidth;
            tempBoxNumber--;
        }
        background.x -= boxWidth;
        background.y += boxHeight;
        while(background.x > 280){

            pushBoxes(background.x, background.y, tempBoxNumber);
            background.x -= boxWidth;//Incrementar coordenada X para imprimir la siguiente casilla
            tempBoxNumber--;//Decrementar numero de casilla para renderizar el siguiente numero de casilla

            pushBoxes(background.x, background.y, tempBoxNumber);
            background.x -= boxWidth;
            tempBoxNumber--;
        }
        background.x = (windowWidth - windowHeight) / 2;
        background.y += boxHeight;
    }
    // Aquí va la implementación de la creación de fondo
    std::cout << "Fondo del juego creado." << std::endl;

}

void Game::releaseDice() {
    std::cout << "Dice released!" << std::endl;
}

bool Game::isGameOver() {
    return amountPlayers <= 0;
}

void Game::generateSnakeAndLadders() {
    std::cout << "Snake and Ladders generated!" << std::endl;
    // Lógica para generar serpientes y escaleras en el tablero
}

void Game::displayBoard() {
    std::cout << "Displaying the board..." << std::endl;
    // Lógica para mostrar el tablero
}

void Game::splitSpecialBoxes() {
    std::uniform_int_distribution<> specialBoxesPercent(10, 25);
    int percent = boxNumber * specialBoxesPercent(gen) / 100;
    std::uniform_int_distribution<> specialBoxesAmount(1, percent / 1.5);
    snakesAmount = specialBoxesAmount(gen);
    laddersAmount = percent - snakesAmount;
}

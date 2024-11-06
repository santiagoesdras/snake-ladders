#include "Game.h"

    // Semilla para el generador aleatorio
    std::random_device rd; 
    std::mt19937 gen(rd()); // Generador Mersenne Twister


Game::Game(int aP, int r, int c, int dS, Game* u):
amountPlayers(aP), windowWidth(1280), windowHeight(720), diceSize(dS), utilities(u), rows(r), columns(c)
{   
    boxWidth = windowHeight / columns;
    boxHeight = windowHeight / rows;
    boxNumber = rows * columns;
    window = new Window(windowWidth, windowHeight, utilities);
    distrib = std::uniform_int_distribution<>(1, diceSize);
    splitSpecialBoxes();
}

void Game::mainGame(){
    window->listener();
}
std::array<std::string, 3> Game::getNumberRoutes(int boxNumber){
    std::string numero = std::to_string(boxNumber);
    std::array<std::string, 3> rutas;
    for(int i = 0; i < 3; i++){
        switch(numero[i]){
            case '0':
                rutas[i] = numberRoutes[0];
                break;
            case '1':
                rutas[i] = numberRoutes[1];
                break;
            case '2':
                rutas[i] = numberRoutes[2];
                break;
            case '3':
                rutas[i] = numberRoutes[3];
                break;
            case '4':
                rutas[i] = numberRoutes[4];
                break;
            case '5':
                rutas[i] = numberRoutes[5];
                break;
            case '6':
                rutas[i] = numberRoutes[6];
                break;
            case '7':
                rutas[i] = numberRoutes[7];
                break;
            case '8':
                rutas[i] = numberRoutes[8];
                break;
            case '9':
                rutas[i] = numberRoutes[9];
                break;
            default:
                rutas[i] = "";
                break;
        }
    }
    return rutas;
}

void Game::printBoxes(){
    for(int i = 0; i < boxes.getSize(); i++){
        Box* tempBox = boxes.getItem(i);
        std::cout << "Propiedades de la casilla almacenada en el indice " << i << std::endl;
        std::cout << "Coordenada en x: " << tempBox->coordx << std::endl;
        std::cout << "Coordenada en y: " << tempBox->coordy << std::endl;
        std::cout << "Numero de casilla: " << tempBox->number << std::endl;
        std::cout << "Tipo de casilla: " << tempBox->type << std::endl;
        std::cout << "Direccion de memoria top: " << tempBox << std::endl;
        std::cout << "Direccion de memoria bottom: " << tempBox->bottom << std::endl;
    }
}

void Game::pushBoxes(int x, int y, int bN){
    boxes.Add(x, y, bN);
}

int Game::releaseDice(){
    return distrib(gen);
}

void Game::generateSnakesAndLadders(){
    int headSnakes[snakesAmount];
    int tailSnakes[snakesAmount];
    int bottomLadders[laddersAmount];
    int topLadders[laddersAmount];
    int inferiorLimit = columns + 1;
    int superiorLimit =  boxNumber - 1;
    int inferiorLimit1 = 1;
    int superiorLimit1 = 0;
    std::set<int> usedNumbers;

    //Generacion aleatoria de las serpientes
    for(int i = 0; i < snakesAmount; i++){
        headSnakes[i] = randomNumbers(inferiorLimit, superiorLimit, usedNumbers);
        superiorLimit1 = (headSnakes[i] - (headSnakes[i] % columns));
        tailSnakes[i] = randomNumbers(inferiorLimit1, superiorLimit1, usedNumbers);
        std::cout << "Cabeza serpiente no." << i <<": " << headSnakes[i] << std::endl;
        std::cout << "Cola serpiente no." << i << ": " << tailSnakes[i] << std::endl;
    }

    inferiorLimit1 = 2;
    superiorLimit1 = boxNumber - columns;

    //Generacion aleatoria de las escaleras
    for(int i = 0; i < laddersAmount; i++){
        bottomLadders[i] = randomNumbers(inferiorLimit1, superiorLimit1, usedNumbers);
        inferiorLimit = (bottomLadders[i] + (columns - (bottomLadders[i] % columns)));
        superiorLimit = boxNumber - 1;
        topLadders[i] = randomNumbers(inferiorLimit, superiorLimit, usedNumbers);
        std::cout << "Base escalera no" << i << ": " << bottomLadders[i] << std::endl;
        std::cout << "Tope escalera no" << i << ": " << topLadders[i] << std::endl;
    }

    //Carga de punteros a serpientes y escaleras en arreglos de punteros a serpientes y escaleras
    for(int i = 0; i < snakesAmount; i ++){

        //Cargar serpientes al arreglo de punteros a casillas de tipo serpiente
        Box* tempBox = boxes.getItem((boxNumber - headSnakes[i] - 1));
        std::cout << "Numero de casilla del puntero actual" << tempBox->number << std::endl;
        if(!tempBox){
            std::cout << "Error: Puntero tempbox para serpientes vacio" << std::endl;
            std::cout << "Indice al que se trato de acceder: " << (boxNumber - headSnakes[i] - 1) << std::endl;
            std::cout << "Numero asignado en headsnakes: " << headSnakes[i] << std::endl;
            system("pause");
        }
        tempBox->type = "HEAD-SNAKE";
        tempBox->bottom = boxes.getItem(boxNumber - tailSnakes[i] - 1);
        snakePointers[i] = tempBox;
    } 
}

void Game::splitSpecialBoxes(){
    std::uniform_int_distribution<>specialBoxesPercent (10, 25);
    int percent = boxNumber * specialBoxesPercent(gen) / 100;
    std::uniform_int_distribution<>specialBoxesAmount (1, percent / 1.5);
    snakesAmount = specialBoxesAmount(gen);
    laddersAmount = percent - snakesAmount;
}

int Game::randomNumbers(int inferiorLimit, int superiorLimit, std::set<int> &usedNumbers){
    int randomN = 0;
    std::uniform_int_distribution<> limits(inferiorLimit, superiorLimit);
    bool isValid = false;
    while(!isValid){
        randomN = limits(gen);
        if(usedNumbers.count(randomN) == 0){
            isValid = true;
            usedNumbers.insert(randomN);
        }
    }
    return randomN;
}

/* std::vector<SDL_Rect> Game::snakeDimensions(){
    std::vector<SDL_Rect> retorno;
    for(int i = 0; i < snakesAmount; i++){
        int topX = snakePointers[i]->coordx;
        int bottomX = snakePointers[i]->bottom->coordx;
        int topY = snakePointers[i]->coordy;
        int bottomY = snakePointers[i]->bottom->coordy;
        int a;
        int b;
        SDL_Rect tempDest;
        tempDest.w = boxWidth / 2;
        if(bottomX > topX){
            a = topX - bottomX;
            b = bottomY - topY;
            tempDest.h = sqrt( a * a + b * b);
        }
        if(topX > bottomX){
            a = bottomX - topX;
            b = bottomY - topY;
            tempDest.h = sqrt( a * a + b * b);
        }
        if(topX == bottomX){
            tempDest.h = std::abs(bottomY - topY);
        }
        tempDest.x = topX + (bottomX - topX) / 2;
        tempDest.y = topY;
        retorno.push_back(tempDest);
    }
    return retorno;
}
 */  


std::vector<Game::SnakeData> Game::snakeDimensions() {
    std::vector<Game::SnakeData> retorno;

    for(int i = 0; i < snakesAmount; i++) {
        // Coordenadas de la cabeza (top) y cola (bottom) de la serpiente
        int topX = snakePointers[i]->coordx;
        int topY = snakePointers[i]->coordy;
        int bottomX = snakePointers[i]->bottom->coordx;
        int bottomY = snakePointers[i]->bottom->coordy;

        // Calcular la distancia entre cabeza y cola
        int deltaX = bottomX - topX;
        int deltaY = bottomY - topY;
        double length = sqrt(deltaX * deltaX + deltaY * deltaY);

        // Calcular el ángulo en grados
        double angle = atan2(deltaY, deltaX) * 180 / M_PI;

        // Crear el rectángulo para representar la serpiente
        SDL_Rect tempDest;
        tempDest.w = 10; // Ancho fijo del rectángulo (puedes ajustar este valor)
        tempDest.h = static_cast<int>(length); // Altura igual a la longitud de la serpiente
        tempDest.x = topX - (tempDest.w / 2); // Posición X centrada en la cabeza
        tempDest.y = topY; // Posición Y en la cabeza

        // Centro de rotación en la parte superior del rectángulo (donde está la cabeza)
        SDL_Point center;
        center.x = tempDest.w / 2;
        center.y = 0;

        // Guardar los datos calculados
        retorno.push_back({tempDest, angle, center});
    }

    return retorno;
}



int Game::getSnakesAmount(){
    return snakesAmount;
}

int Game::getLaddersAmount(){
    return laddersAmount;
}
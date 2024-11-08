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
    std::cout << "Cantidad casillas especiales: " << snakesAmount + laddersAmount << std::endl;
    for(int i = 0; i < boxes.getSize(); i++){
        Box* tempBox = boxes.getItem(i);
        if(tempBox->type == "HEAD-SNAKE" || tempBox->type == "TOP-LADDER"){
            std::cout << "Tipo de casilla: " << tempBox->type << std::endl;
            std::cout << "Numero de casillas: " << tempBox->number << std::endl;
            std::cout << "Continuacion: " << tempBox->bottom->number << std::endl;
        }
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
    int superiorLimit =  boxNumber - 2;
    int inferiorLimit1 = 1;
    int superiorLimit1 = 0;
    std::set<int> usedNumbers;

    //Generacion aleatoria de las serpientes
    for(int i = 0; i < snakesAmount; i++){
        headSnakes[i] = randomNumbers(inferiorLimit, superiorLimit, usedNumbers);
        superiorLimit1 = (headSnakes[i] - (headSnakes[i] % columns));
        tailSnakes[i] = randomNumbers(inferiorLimit1, superiorLimit1, usedNumbers);
    }

    inferiorLimit1 = 2;
    superiorLimit1 = boxNumber - columns;

    //Generacion aleatoria de las escaleras
    for(int i = 0; i < laddersAmount; i++){
        bottomLadders[i] = randomNumbers(inferiorLimit1, superiorLimit1, usedNumbers);
        inferiorLimit = (bottomLadders[i] + (columns - (bottomLadders[i] % columns)));
        superiorLimit = boxNumber - 1;
        topLadders[i] = randomNumbers(inferiorLimit, superiorLimit, usedNumbers);
    }

    //Carga de punteros a serpientes y escaleras en arreglos de punteros a serpientes y escaleras
    for(int i = 0; i < snakesAmount; i ++){
        int index = (boxNumber - headSnakes[i] - 1);
        if(index < 1 || index > boxNumber + 1){
            index = randomNumbers(inferiorLimit, superiorLimit, usedNumbers);
        }
        //Cargar serpientes al arreglo de punteros a casillas de tipo serpiente
        Box* tempBox = boxes.getItem(index);
        if(!tempBox){
            std::cout << "Error: Puntero tempbox para serpientes vacio" << std::endl;
            std::cout << "Indice al que se trato de acceder: " << (boxNumber - headSnakes[i] - 1) << std::endl;
            std::cout << "Numero asignado en headsnakes: " << headSnakes[i] << std::endl;
            system("pause");
        }
        tempBox->type = "HEAD-SNAKE";
        tempBox->bottom = boxes.getItem(boxNumber - tailSnakes[i] - 1);
        snakePointers[i] = tempBox;

        int index1 = (boxNumber - topLadders[i] - 1);
        if(index1 < 1 || index1 > boxNumber + 1){
            index = randomNumbers(inferiorLimit1, superiorLimit1, usedNumbers);
        }
        //Carga escacleras al arreglo de punteros a casillas de tipo serpiente
        Box* tempBox1 = boxes.getItem(index1);
        if(!tempBox1){
            std::cout << "Error: Puntero a tempbox para escaleras vacio" << std::endl;
            std::cout << "Inice al que se trato de acceder: " << (boxNumber - topLadders[i] - 1) << std::endl;
            std::cout << "Numero asignado en headsnakes: " << topLadders[i] << std::endl;
            system("pause");
        }
        tempBox1->type = "TOP-LADDER";
        tempBox1->bottom = boxes.getItem((boxNumber - bottomLadders[i] - 1));
        snakePointers[i] = tempBox1;
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
    std::vector<SnakeData> retorno;

    for(int i = 0; i < snakesAmount; i++) {
        // Obtener las coordenadas de la cabeza y la cola
        int topX = snakePointers[i]->coordx;
        int bottomX = snakePointers[i]->bottom->coordx;
        int topY = snakePointers[i]->coordy;
        int bottomY = snakePointers[i]->bottom->coordy;

        // Variables para la distancia y el ángulo
        int a, b;
        double angle;
        SDL_Rect tempDest;
        tempDest.w = boxWidth / 2;  // Ancho ajustado de la serpiente

        // Calcular la distancia entre la cabeza y la cola
        if(bottomX > topX) {
            // La cabeza está a la izquierda de la cola, la rotación será hacia la derecha
            a = bottomX - topX;
            b = bottomY - topY;
            tempDest.h = sqrt(a * a + b * b);  // Distancia entre la cabeza y la cola
            angle = atan2(b, a) * 180 / M_PI;  // Calculamos el ángulo en grados
        } else if(topX > bottomX) {
            // La cabeza está a la derecha de la cola, la rotación será hacia la izquierda
            a = topX - bottomX;
            b = bottomY - topY;
            tempDest.h = sqrt(a * a + b * b);  // Distancia entre la cabeza y la cola
            angle = atan2(b, -a) * 180 / M_PI;  // Calculamos el ángulo en grados y ajustamos el signo
        } else {
            // Caso especial: cuando la cabeza y la cola están alineadas verticalmente
            tempDest.h = std::abs(bottomY - topY);  // Altura es la diferencia en Y
            angle = (bottomY > topY) ? 90 : -90;  // Si la cola está abajo, rotación hacia abajo, sino hacia arriba
        }

        // Calcular la posición del centro para la rotación
        tempDest.x = topX + (bottomX - topX) / 2;
        tempDest.y = topY;

        // Guardamos los resultados de las serpientes y su ángulo de rotación
        retorno.push_back({tempDest, angle});
    }

    return retorno;
}

int Game::getSnakesAmount(){
    return snakesAmount;
}

int Game::getLaddersAmount(){
    return laddersAmount;
}

int Game::getRows(){
    return rows;
}

int Game::getColumns(){
    return columns;
}
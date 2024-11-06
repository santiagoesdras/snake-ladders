#include "Game.h"

Render::Render(int wW, int wH, int rows, int columns, SDL_Renderer* r, Game* u):
        windowWidth(wW), windowHeight(wH), renderer(r), utilities(u){
        boxWidth = wH / 10;
        boxHeight = wH / 10;
        boxNumber = 10 * 10;
    }

Render::~Render(){}

void Render::renderBackground(){
    if (backgroundTexture) {
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
} else {
    std::cerr << "Background texture not loaded!" << std::endl;
}

}

void Render::renderPlayer(int x, int y){
    SDL_Rect position;
        position.h = boxHeight / 2;
        position.w = boxWidth / 2;
        position.x = x;
        position.y = y;
    SDL_RenderCopy(renderer, playerTexture, nullptr, &position);
}

void Render::createBackground(){
    //Crear la textura para el fondo y el tablero
    backgroundTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, windowWidth, windowHeight);
    if(!backgroundTexture){
        std::cerr << "Error al crear tablero de juego: " << SDL_GetError() << std::endl;
        return;
    }

    //Configurar el renderizador para dibujar sobre la textura del tablero
    SDL_SetRenderTarget(renderer, backgroundTexture);

    //Dibujar el tablero sobre la textura 

    //Definir las dimensiones y coordenadas para las casillas del tablero
    SDL_Rect background;
        background.h = boxHeight;
        background.w = boxWidth;
        background.x = (windowWidth - windowHeight) / 2;
        background.y = 0;
    
    //Definir boxNumbertemporal para decrementar
    int tempBoxNumber = boxNumber;

    //Obtener ruta de las imagenes para numerar cada casilla
    std::array<std::string, 3> routes = utilities->getNumberRoutes(tempBoxNumber);

    //Definicion fondo de color negro
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//    SDL_RenderClear(renderer);

    //Bucle para imprimir las casillas y los numeros
    while(background.y < windowHeight){
        while(background.x < 1000){

            //Renderizado casillas moradas    
            SDL_SetRenderDrawColor(renderer, 175, 36, 245, 255);//Definir color del rectangulo (morado)
            SDL_RenderFillRect(renderer, &background); //Renderizar rectangulo (casilla) en base a posicion y coordenadas

            //LLamada printNumbers para renderizar imagen de los numeros de la casilla
            printNumbers(background.x, background.y, background.h, background.w, routes); 
            utilities->pushBoxes(background.x, background.y, tempBoxNumber);
            background.x += boxWidth;//Incrementar coordenada X para imprimir la siguiente casilla
            tempBoxNumber--;//Decrementar numero de casilla para renderizar el siguiente numero de casilla
            routes = utilities->getNumberRoutes(tempBoxNumber); //Actualizacion de rutas a imagenes del numero de casillas

            //Renderizado casillas amarillas
            SDL_SetRenderDrawColor(renderer, 244, 244, 57, 255);//Definir color del rectangulo (amarillo)
            SDL_RenderFillRect(renderer, &background); //Renderizar rectangulo (casilla) en base a posicion y coordenadas

            //Llamada printNumbers para renderizar imagen de los numeros de la casilla
            printNumbers(background.x, background.y, background.h, background.w, routes);
            utilities->pushBoxes(background.x, background.y, tempBoxNumber);
            background.x += boxWidth;
            tempBoxNumber--;
            routes = utilities->getNumberRoutes(tempBoxNumber);
        }
        background.x -= boxWidth;
        background.y += boxHeight;
        while(background.x > 280){

            //Renderizado casillas moradas    
            SDL_SetRenderDrawColor(renderer, 175, 36, 245, 255);//Definir color del rectangulo (morado)
            SDL_RenderFillRect(renderer, &background); //Renderizar rectangulo (casilla) en base a posicion y coordenadas

            //LLamada printNumbers para renderizar imagen de los numeros de la casilla
            printNumbers(background.x, background.y, background.h, background.w, routes); 
            utilities->pushBoxes(background.x, background.y, tempBoxNumber);
            background.x -= boxWidth;//Incrementar coordenada X para imprimir la siguiente casilla
            tempBoxNumber--;//Decrementar numero de casilla para renderizar el siguiente numero de casilla
            routes = utilities->getNumberRoutes(tempBoxNumber); //Actualizacion de rutas a imagenes del numero de casillas

            //Renderizado casillas amarillas
            SDL_SetRenderDrawColor(renderer, 244, 244, 57, 255);//Definir color del rectangulo (amarillo)
            SDL_RenderFillRect(renderer, &background); //Renderizar rectangulo (casilla) en base a posicion y coordenadas

            //Llamada printNumbers para renderizar imagen de los numeros de la casilla
            printNumbers(background.x, background.y, background.h, background.w, routes);
            utilities->pushBoxes(background.x, background.y, tempBoxNumber);
            background.x -= boxWidth;
            tempBoxNumber--;
            routes = utilities->getNumberRoutes(tempBoxNumber);
        }
        background.x = (windowWidth - windowHeight) / 2;
        background.y += boxHeight;
    }
    printSnakeAndLadders();
    SDL_SetRenderTarget(renderer, nullptr);
    //utilities->printBoxes();
}

void Render::printNumbers(int x, int y, int h, int w, std::array<std::string, 3> rutas){
    int i = 0;
    SDL_Rect dest;
        dest.h = h /3;
        dest.w = w / 5;
        dest.x = x;
        dest.y = y;
    while(i < 3){
        if(rutas[i] == ""){
            break;
        }
        //std::cout << "Digito 1: " << rutas[0] << " Digito 2: " << rutas[1] << " Digito 3: " << rutas[2] << std::endl;
        SDL_Surface* numberSurface = SDL_LoadBMP(rutas[i].c_str());
        if(!numberSurface){
            std::cerr << "Error al cargar imagen del numero " << i << ": " << SDL_GetError() << std::endl;
        }

        SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, numberSurface);
        if(!tempTexture){
            std::cerr << "Error al renderizar la textura: " << SDL_GetError() << std::endl;
        }
        
        SDL_RenderCopy(renderer, tempTexture, nullptr, &dest);
        SDL_DestroyTexture(tempTexture);
        dest.x += dest.w;
        i++;
    }

}

void Render::pauseMenu(bool isMenuOpen){
    if(isMenuOpen){
        SDL_Rect windowSize;
        windowSize.h = windowHeight;
        windowSize.w = windowWidth;
        windowSize.x = 0;
        windowSize.y = 0;
        //Renderizado fondo transparente menu de pausa
        SDL_SetRenderDrawColor(renderer, 123, 236, 232, 175); // Color de fondo (celeste)
        SDL_RenderFillRect(renderer, &windowSize);

        //Renderizado botones del menu
        SDL_Rect button1;
        button1.h = 50;
        button1.w = 150;
        button1.x = (windowWidth - button1.w) / 2;
        button1.y = 260;
        SDL_SetRenderDrawColor(renderer, 219, 123, 236, 200); // Color de botones (fusia)
        SDL_RenderFillRect(renderer, &button1);

        SDL_Rect button2 = button1;
        button2.y += 75;
        SDL_RenderFillRect(renderer, &button2);

        SDL_Rect button3 = button2;
        button3.y += 75;
        SDL_RenderFillRect(renderer, &button3);
    }    
    return;
}

void Render::printSnakeAndLadders() {
    SDL_Texture* tempTexture = loadImages();
    utilities->generateSnakesAndLadders();
    // Verificar que la textura se haya cargado correctamente
    if (!tempTexture) {
        std::cerr << "No se pudo cargar la textura para las serpientes." << std::endl;
        return;  // Salir de la función si no se pudo cargar la textura
    }

    // Obtener las dimensiones de las serpientes y sus ángulos
    std::vector<Game::SnakeData> snakeData = utilities->snakeDimensions();
    int snakesAmount = utilities->getSnakesAmount();

    // Comprobamos si el número de serpientes coincide con las dimensiones
    if (snakeData.size() != snakesAmount) {
        std::cerr << "Error: La cantidad de serpientes no coincide con las dimensiones proporcionadas." << std::endl;
        SDL_DestroyTexture(tempTexture);  // Liberar la textura si hay un error
        return;
    }

    // Iteramos para renderizar las serpientes
    for (int i = 0; i < snakesAmount; i++) {
        SDL_Rect dest = snakeData[i].rect;
        double angle = snakeData[i].angle;  // Obtiene el ángulo calculado

        // Calculamos el centro de la textura
        SDL_Point center = { dest.w / 2 , dest.h / 2 };  // Centrado de la textura

        // Renderizamos la serpiente con la rotación aplicada
        SDL_RenderCopyEx(renderer, tempTexture, nullptr, &dest, angle, &center, SDL_FLIP_NONE);
    }

    // Liberar la textura después de renderizar
    SDL_DestroyTexture(tempTexture);
}


SDL_Texture* Render::loadImages() {
    SDL_Surface* tempSurface = SDL_LoadBMP("snakes/Serpiente3.bmp");
    if (!tempSurface) {
        std::cerr << "Error al cargar imagen: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);  // Liberar la superficie después de crear la textura

    if (!tempTexture) {
        std::cerr << "Error al renderizar la textura: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    
    return tempTexture;
}

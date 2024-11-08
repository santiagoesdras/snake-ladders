#include "Window.h"
#include "Render.h"
#include "Game.h"

Render* renderizado;
Window::Window(int wW, int wH, Game* u):
    windowWidth(wW), windowHeight(wH), playing(true), utilities1(u), isMenuOpen(false)
{
    if(!initialiceSdl()){
        std::cout << "Error al inicializar SDL" << std::endl;
    }
    int rows = utilities1->getRows();
    int columns = utilities1->getColumns();
    renderizado = new Render(windowWidth, windowHeight, rows, columns, renderer, utilities1);
}

Window::~Window(){
    clearSdl();
}

void Window::listener(){
    SDL_Event eventHandler;
    renderizado->createBackground();
    //Bucle principal del juego
    while(playing){

        //Manejador de ventos
        while(SDL_PollEvent(&eventHandler)){
            if(eventHandler.type == SDL_QUIT){
                playing = false;
            }

            if(eventHandler.type == SDL_KEYDOWN){
                switch(eventHandler.key.keysym.sym){
                    case SDLK_ESCAPE:
                        isMenuOpen = !isMenuOpen;
                        break;
                    case SDLK_e:
                        std::cout << "Resultado del dado: " << utilities1->releaseDice() << std::endl;
                        break;          
                    case SDLK_z:
                        utilities1->printBoxes();
                        break;
                }
            }
        }

        //Renderizador del fondo y limpieza de en cada frame
        SDL_RenderClear(renderer);
        renderizado->renderBackground();

        if(isMenuOpen){
            renderizado->pauseMenu(isMenuOpen);
        }

        //Dibujar el renderizado en pantalla
        SDL_RenderPresent(renderer);

        //Delay antes de procesar el siguiente frame (60 FPS aproximadamente)
        SDL_Delay(16);
    }

    clearSdl();
}

bool Window::initialiceSdl(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "No se puede inicializar SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow("Serpientes y Escaleras", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if(!window){
        std::cerr << "No se pudo crear la ventana: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if(!renderer){
        std::cerr << "No se pudo crear el renderizador: " << SDL_GetError() << std::endl;
        return false;
    }

    //Configuracion del canal alfa para generara figuras con transparencia
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    //createBackground();
    return true;
}

void Window::clearSdl(){
    if(renderer){
        SDL_DestroyRenderer(renderer);
    }

    if(window){
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}
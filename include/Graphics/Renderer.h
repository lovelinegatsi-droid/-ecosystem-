
/*#pragma once 
#include <SDL3/SDL.h>
 
/*SDL_Init(SDL_INIT_VIDEO) ;

SDL_Window* window = SDL_CreateWindow("ecosystem simulator", 800, 600, 0);

if(!window){
    std::cout << " erreur de creation de fenetre :" << SDL_GetError() << std::endl;
    SDL_Quit();
}

SDL_Renderer* rendu = SDL_Createrenderer(window, 0 ,SDL_RENDERER_ACCELERATED) ;

if(!rendu) {
    std::cout << "erreur de generation de rendu :" << SDL_GetError() << std::endl ;
    SDL_Quit() ;
}

bool running = true ;
SDL_Event e;*/

/*while (running)
{
    while (SDL_PollEvent(&e)){
        
    }
     code 

✅ *3. render.cpp*
Contient le code pour dessiner les entités.

À inclure :
- Fonction drawEntite(SDL_Renderer*, Entite&)
- Fonction drawNourriture(...)
- Utilisation de SDL_SetRenderDrawColor() et SDL_RenderFillRectF()*/
/*namespace Ecosystem{
    const float WEIGHT = 1200.0f;
    const float HEIGHT = 800.0f;
    namespace Graphics{
        SDL_Init(SDL_INIT_VIDEO) ;{
            SDL_Init(SDL_INIT_VIDEO) ;

            SDL_Window * win = ("ma fenetre de simulation", WEIGHT, HEIGHT, 0) ;

            if(!win.Initialisation()){
                std::cout << " erreur d'initialisation du programme" << SDL_GetError() << std::endl;
            }

            SDL_Renderer * rendu - (win , nullptr, SDL_RENDERER_ACCELERATED) ;

            if(!rendu.Initialisation()) {
                std::cout << "erreur de generation de rendu " << SDL_GetError() << std::endl ;
            }

            
        }
    }
}*/




#ifndef RENDER_UTILS_HPP
#define RENDER_UTILS_HPP


#include <SDL2/SDL_render.h>

namespace Render{

    SDL_Window* makeWindow(){
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::runtime_error("SDL:n alustaminen epäonnistui: " + std::string(SDL_GetError()));
        }

        // luodaan ikkuna
        SDL_Window* window = SDL_CreateWindow("SDL-testi -ikkuna",
                                                SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                            SDL_WINDOW_SHOWN);

        if (!window) {
            throw std::runtime_error("SDL-ikkunan luominen epäonnistui: " + std::string(SDL_GetError()));
            SDL_Quit();
        }

        return window;
    }

    SDL_Renderer* makeRenderer(SDL_Window* window){
        // luodaan renderöijä ikkunalle
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            throw std::runtime_error("SDL-renderöijän luominen epäonnistui: " + std::string(SDL_GetError()));
            SDL_DestroyWindow(window);
            SDL_Quit();

        }

        return renderer;
    }
}





#endif
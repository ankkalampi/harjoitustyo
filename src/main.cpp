#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <ostream>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL ei voinut alustaa! SDL_Virhe: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    // luodaan ikkuna
    SDL_Window* window = SDL_CreateWindow("SDL-testi -ikkuna",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            800, 600,
                                        SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "ikkunan luonti epäonnistui: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }


    // luodaan renderöijä ikkunalle
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderöijän luonti epäonnistui" << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    // Aseta renderöijän taustaväri (RGB: punainen)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);


    // tyhjennä renderöijä ja näytä väri
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    //odota 5sek ennen ohjelman sulkemista
    SDL_Delay(5000);

    //Vapauta resurssit ja sulje SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

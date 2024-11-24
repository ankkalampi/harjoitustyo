#ifndef RENDER_UTILS_HPP
#define RENDER_UTILS_HPP


#include <SDL2/SDL_render.h>

namespace Render{
    SDL_Window* makeWindow();

    SDL_Renderer* makeRenderer(SDL_Window* window);
}





#endif
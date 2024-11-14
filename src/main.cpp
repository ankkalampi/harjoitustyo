#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <ostream>
#include <vector>

#include <random>


constexpr int WIDTH = 1680;
constexpr int HEIGHT = 1050;


// neliön rakenne
struct Square {
    SDL_Rect rect;
    int dx, dy;
    SDL_Color color;
};


// Neliöiden piirtäminen
void drawSquare(SDL_Renderer* renderer, const Square& square) {
    SDL_SetRenderDrawColor(renderer, square.color.r, square.color.g, square.color.b, square.color.a);
    SDL_RenderFillRect(renderer, &square.rect);
}

void moveSquare(Square& square){
    
    square.rect.x += square.dx;
    square.rect.y += square.dy;

    // tarkistetaan törmäys seinien kanssa ja käännetään suuntaa
    if (square.rect.x <= 0 || square.rect.x + square.rect.w >= WIDTH) {
        square.dx = -square.dx;
    }
    if (square.rect.y <= 0 || square.rect.y + square.rect.h >= HEIGHT) {
        square.dy = -square.dy;
    }
    
}

std::vector<Square> generateSquares(int number){
    std::random_device rd;
    std::mt19937 gen(rd());

    int colormin = 0;
    int colormax = 255;

    int xmin = 0;
    int xmax = 1000;

    int ymin = 0;
    int ymax = 1000;

    int dxmin = -15;
    int dxmax = 15;

    int dymin = -15;
    int dymax = 15;

    int minwid = 2;
    int maxwid = 5;

    int minhei = 2;
    int maxhei = 5;

    std::uniform_int_distribution<int> colordistrib(colormin, colormax);
    std::uniform_int_distribution<int> xdistrib(xmin, xmax);
    std::uniform_int_distribution<int> ydistrib(ymin, ymax);
    std::uniform_int_distribution<int> dxdistrib(dxmin, dxmax);
    std::uniform_int_distribution<int> dydistrib(dymin, dymax);
    std::uniform_int_distribution<int> widdistrib(minwid, maxwid);
    std::uniform_int_distribution<int> heidistrib(minhei, maxhei);

    std::vector<Square> squares;

    for (int i = 0; i < number; i++){
        int r = colordistrib(gen);
        int g = colordistrib(gen);
        int b = colordistrib(gen);

        int x = xdistrib(gen);
        int y = ydistrib(gen);

        int dx = dxdistrib(gen);
        int dy = dydistrib(gen);

        int wid = widdistrib(gen);
        int hei = heidistrib(gen);

        Square square = Square{{x, y, wid, hei}, dx, dy, {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), 255}};

        squares.push_back(square);
    }

    return squares;

}





int main() {

    

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL ei voinut alustaa! SDL_Virhe: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    // luodaan ikkuna
    SDL_Window* window = SDL_CreateWindow("SDL-testi -ikkuna",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            WIDTH, HEIGHT,
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

    // luodaan neliöitä
    std::vector<Square> squares2 = {
        {{100,100,50,50}, 2, 1, {144, 34, 230,255}},
        {{100,100,50,50}, -3, -1, {55,30,0,255}},
        {{100,100,50,50}, -4, 2, {12,125,0,255}},
        {{100,100,50,50}, -3, 4, {55,30,0,255}},
        {{100,100,50,50}, 1, 5, {12,125,0,255}},
        {{100,100,50,50}, 7, 1, {144, 34, 230,255}},
        {{100,100,50,50}, 2, 1, {255,0,0,255}},
        {{100,100,50,50}, -3, -1, {55,30,0,255}},
        {{100,100,50,50}, -7, 2, {12,125,0,255}},
        {{100,100,50,50}, -3, -4, {144, 34, 230,255}},
        {{100,100,50,50}, -1, 5, {12,125,0,255}},
        {{100,100,50,50}, 7, -12, {255,0,0,255}},
        {{100,100,50,50}, 2, 1, {255,0,0,255}},
        {{100,100,50,50}, -3, -1, {55,30,0,255}},
        {{100,100,50,50}, -5, 2, {12,125,0,255}},
        {{100,100,50,50}, -3, 4, {144, 34, 230,255}},
        {{100,100,50,50}, 1, 6, {12,125,0,255}},
        {{100,100,50,50}, 7, 1, {255,0,0,255}},
        {{100,100,50,50}, 11, 1, {144, 34, 230,255}},
        {{100,100,50,50}, -3, -1, {55,30,0,255}},
        {{100,100,50,50}, -4, 5, {144, 34, 230,255}},
        {{100,100,50,50}, -3, -4, {55,30,0,255}},
        {{100,100,50,50}, 1, 5, {12,125,0,255}},
        {{100,100,50,50}, -7, 1, {144, 34, 230,255}},

    };

    std::vector<Square> squares = generateSquares(5000);


    



    // luodaan pelisilmukka
    bool quit = false;
    SDL_Event e;

    while (!quit){
        //tapahtumien käsittely
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Aseta renderöijän taustaväri (RGB: musta)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);


        // tyhjennä renderöijä ja näytä väri
        SDL_RenderClear(renderer);

        for (auto& square : squares){
            moveSquare(square);
            drawSquare(renderer, square);
        }



        // piirretään neliöt

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }




    //Vapauta resurssit ja sulje SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

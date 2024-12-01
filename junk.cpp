#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>
#include <string>

#include <random>

#include <omp.h>

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <sstream>

constexpr int WIDTH = 1680;
constexpr int HEIGHT = 1050;





struct Entity {
    int id;
    std::string name;



};

struct PhysicsComponent {
    int id;
    glm::vec2 velocity;

    SDL_Rect rect;

    PhysicsComponent(int id, int x, int y, int w, int h, int dx, int dy) : id(id){
        rect = {x, y, w, h};
        velocity = {dx, dy};
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << "PhysicsComponent(id=" << id << ", velocity=" << velocity[0] << "," << velocity[1] << " rect=" << &rect << ")";
        return oss.str();
    }




};

using PCVector = std::vector<std::shared_ptr<PhysicsComponent>>;
using PC = std::shared_ptr<PhysicsComponent>;



struct RenderComponent {
    int id;
    PC physComp;
    SDL_Color* color;

    RenderComponent(int i, PC physC, SDL_Color* color) : id(i), physComp(physC), color(color){

    }

    std::string toString() const {
        std::ostringstream oss;
        oss << "RenderComponent(id=" << id << ", physComp=" << &physComp << " color= r: " << static_cast<int>(color->r) << " g: " << static_cast<int>(color->g) << " b: " << static_cast<int>(color->b) << ")";
        return oss.str();
    }

};

using RCVector = std::vector<std::shared_ptr<RenderComponent>>;
using RC = std::shared_ptr<RenderComponent>;



struct BehaviorComponent {
    int id;
    PhysicsComponent* physComp;

    BehaviorComponent(int i, PhysicsComponent* physC) : id(i), physComp(physC){}

    void act(){
        std::cout << "Acting! Entity number: " << id << std::endl;
    }
};

class BehaviorSystem {
    public:
    std::vector<BehaviorComponent*> behaviorComps;


    void update(){


        for (auto& behavComp : behaviorComps){
            behavComp->act();
        }
    }


};




class PhysicsSystem {
    public:
    PCVector physComps;



    void update(){

        #pragma omp parallel for
        for (PC pc1 : physComps){
            /*
            for (PC pc2 : physComps){
                if (checkCollision(pc1, pc2) && pc1->id != pc2->id){
                    std::cout << "HIT!!!!!" << std::endl;
                    resolveCollision(pc1, pc2);
                }

            }
            */
            resolveBoundsCollision(pc1);
            move(pc1);

        }


    }

    bool checkBoundsCollision(PC pc){
        return false;
    }

    bool checkCollision(PC pc1, PC pc2){
        return (pc1->rect.x + pc1->rect.w >= pc2->rect.x
                && pc1->rect.x <= pc2->rect.x + pc2->rect.w
                && pc1->rect.y + pc1->rect.h >= pc2->rect.y
                && pc1->rect.y <= pc2->rect.y + pc2->rect.h );
    }

    void resolveCollision(PC pc1, PC pc2){
        float normal_x = pc1->rect.x - pc2->rect.x;
        float normal_y = pc1->rect.y - pc2->rect.y;
    }

    void resolveBoundsCollision(PC pc){
        // tarkistetaan törmäys seinien kanssa ja käännetään suuntaa
        if (pc->rect.x <= 0 || pc->rect.x + pc->rect.w >= WIDTH) {
            pc->velocity[0] = -pc->velocity[0];
        }
        if (pc->rect.y <= 0 || pc->rect.y + pc->rect.h >= HEIGHT) {
            pc->velocity[1] = -pc->velocity[1];
        }
    }

    void move(PC pc){
        pc->rect.x += pc->velocity[0];
        pc->rect.y += pc->velocity[1];
    }


};

class RenderSystem {
    public:
    RCVector rendComps;
    SDL_Renderer* renderer;


    void update(){
        SDL_SetRenderDrawColor(renderer, 45,87,94,255);

        // tyhjennä renderöijä ja näytä väri
        SDL_RenderClear(renderer);
        //std::cout << "updating, rendcomps size: " << rendComps.size() << std::endl;

        //std::cout << "starting to iterate rendcomps" << std::endl;

        for (RC rendComp : rendComps){
            std::cout << "rendering: " << rendComp->toString() << std::endl;
            draw(rendComp);
            //drawSimple();
        }

        //drawSimple();


        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    void draw(RC rc){
        //std::cout << "starting draw function" << std::endl;
        //std::cout << "DRAWING!!! rect x: " << rc->physComp->rect.x  << "renderer: " << &renderer << std::endl;
        SDL_SetRenderDrawColor(renderer, rc->color->r, rc->color->g, rc->color->b, rc->color->a);
        //std::cout << "rendercolor set" << std::endl;

        //std::cout << "rc is: " << rc->toString() << std::endl;
        //std::cout << "physcomp is: " << rc->physComp->toString() << std::endl;
        SDL_RenderFillRect(renderer, &rc->physComp->rect);
        //std::cout << "renderfillrect done" << std::endl;

    }



};




// neliön rakenne
struct Square {
    SDL_Rect rect;
    int dx, dy;
    SDL_Color color;
};

class App {
    public:
    SDL_Renderer* renderer;
    SDL_Window* window;

    PhysicsSystem* physicsSystem;
    RenderSystem* renderSystem;
    BehaviorSystem behaviorSystem;

    int init(){
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL ei voinut alustaa! SDL_Virhe: " << SDL_GetError() << std::endl;
        return 1;
        }

        // luodaan ikkuna
        this->window = SDL_CreateWindow("SDL-testi -ikkuna",
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
        this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            std::cerr << "Renderöijän luonti epäonnistui" << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        }

        // yhdistetään renderöijä render systemille
        std::cout << "nyt yhdistetään rendersystem" << std::endl;
        this->renderSystem->renderer = renderer;
        std::cout << "rendersystem yhdistetty" << std::endl;
        return 0;

    }

    void run(){
        // luodaan pelisilmukka
        bool quit = false;
        SDL_Event e;

        std::cout << "rendercomps size at beginning: " << renderSystem->rendComps.size() << std::endl;
        std::cout << "physcomps size at beginning: " << physicsSystem->physComps.size() << std::endl;

        while (!quit){
            //tapahtumien käsittely
            while(SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }

            //std::cout << "updating physsystem" << std::endl;
            physicsSystem->update();
            //std::cout << "updating rendersystem" << std::endl;
            //std::cout << "rendercomps size: " << renderSystem.rendComps.size() << std::endl;
            renderSystem->update();
            //behaviorSystem.update();

            //SDL_SetRenderDrawColor(renderer, 45,87,94,255);

            // tyhjennä renderöijä ja näytä väri
            //SDL_RenderClear(renderer);
            /*
            for (RenderComponent* rendComp : rendComps){

                draw(rendComp);
                drawSimple();
            }
            */

            //SDL_RenderPresent(renderer);
            //SDL_Delay(16);

        }

        //Vapauta resurssit ja sulje SDL
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }


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

std::vector<Square> generateSquares(int number, int minwidth=1, int maxwidth=1, int minheighth=1, int maxheighth=1){
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

    int minwid = minwidth;
    int maxwid = maxwidth;

    int minhei = minheighth;
    int maxhei = maxheighth;

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


void generateSquareEntities(RenderSystem* rs, PhysicsSystem* ps, int number){

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

    int minwid = 30;
    int maxwid = 30;

    int minhei = 30;
    int maxhei = 30;

    std::uniform_int_distribution<int> colordistrib(colormin, colormax);
    std::uniform_int_distribution<int> xdistrib(xmin, xmax);
    std::uniform_int_distribution<int> ydistrib(ymin, ymax);
    std::uniform_int_distribution<int> dxdistrib(dxmin, dxmax);
    std::uniform_int_distribution<int> dydistrib(dymin, dymax);
    std::uniform_int_distribution<int> widdistrib(minwid, maxwid);
    std::uniform_int_distribution<int> heidistrib(minhei, maxhei);


    for (int i = 1; i <= number; i++){
        Uint8 r = static_cast<Uint8>(colordistrib(gen));
        Uint8 g = static_cast<Uint8>(colordistrib(gen));
        Uint8 b = static_cast<Uint8>(colordistrib(gen));

        //std::cout << "color is r:  " << r << " g: " << g << " b: " << b << std::endl;

        int x = xdistrib(gen);
        int y = ydistrib(gen);

        int dx = dxdistrib(gen);
        int dy = dydistrib(gen);

        int wid = widdistrib(gen);
        int hei = heidistrib(gen);

        SDL_Color color = {r,g,b, 255};
        //std::cout << "color is r:  " << color.r << " g: " << color.g << " b: " << color.b << std::endl;

        PC pc = std::make_shared<PhysicsComponent>(i, x, y, wid, hei, dx, dy);
        RC rc = std::make_shared<RenderComponent>(i, pc, &color );

        ps->physComps.push_back(pc);
        rs->rendComps.push_back(rc);
        std::cout << "Size of physics vector: " << ps->physComps.size() << std::endl;
        std::cout << "Size of render vector: " << rs->rendComps.size() << std::endl;
        //std::cout << pc->toString() << std::endl;
        //std::cout << rc->toString() << std::endl;
    }
    /*
    std::cout << "getting info of component vectors:" << std::endl;
    std::cout << "Physics vector: " << &ps.physComps << std::endl;
    std::cout << "Render vector: " << &rs.rendComps << std::endl;

    std::cout << "Going through component vectors:" << std::endl;
    std::cout << "Physics components:" << std::endl;
    for (PhysicsComponent* pc : ps.physComps){
        std::cout << pc->toString() << std::endl;

    }

    std::cout << "Render Components:" << std::endl;

    for(RenderComponent* rc : rs.rendComps){
        std::cout << rc->toString() << std::endl;
    }
    */

    std::cout << "Size of physics vector after generation: " << ps->physComps.size() << std::endl;
    std::cout << "Size of render vector after generation: " << rs->rendComps.size() << std::endl;




}




void junk() {

    App app;

    app.init();

    generateSquareEntities(app.renderSystem, app.physicsSystem, 5000);
    std::cout << "rendcomps size just before run: " << app.renderSystem->rendComps.size() << std::endl;
    std::cout << "physcomps size just before run: " << app.physicsSystem->physComps.size() << std::endl;

    app.run();

/*
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

    std::vector<Square> squares = generateSquares(1500,100, 200, 15, 150);

    // luodaan järjestelmät
    BehaviorSystem behaviorSystem;


    // luodaan entityjä




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

    */
}

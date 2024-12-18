#pragma once


#include "BulletDynamics/Dynamics/btRigidBody.h"
#include <SDL2/SDL_render.h>
#include <vector>
#include "../systems/system.hpp"
#include "render_component.hpp"
#include "render_group.hpp"
#include "render_utils.hpp"

namespace Render{





    constexpr int DEFAULT_SCREEN_WIDTH = 1240;
    constexpr int DEFAULT_SCREEN_HEIGHT = 1080;


    inline int SCREEN_WIDTH = DEFAULT_SCREEN_WIDTH;
    inline int SCREEN_HEIGHT = DEFAULT_SCREEN_HEIGHT;





    class RenderSystem : Systems::System {
        public:

        static bool initialized;

        static SDL_Window* window;
        static SDL_Renderer* renderer;

        


        void init() override{

        if(!RenderSystem::initialized){

            RenderSystem::initialized = true;

            RenderSystem::window = makeWindow();
            RenderSystem::renderer = makeRenderer(RenderSystem::window);



        }



    }

    void update() override
        {

            RenderGroup::update();
        }




    void execute() override{

        SDL_SetRenderDrawColor(RenderSystem::renderer, 0, 0, 0, 255);

        SDL_RenderClear(RenderSystem::renderer);
        SDL_SetRenderDrawColor(RenderSystem::renderer, 20, 90, 100, 255);

        RenderGroup::update();
        RenderGroup::execute();

        SDL_RenderPresent(RenderSystem::renderer);







    }

    void terminate() override{

    }


    };










}


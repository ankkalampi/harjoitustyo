

#include "../include/render_system.hpp"
#include "../include/render_utils.hpp"
#include "../include/render_group.hpp"

namespace Render{




    void init(){

        if(!RenderSystem::initialized){

            RenderSystem::initialized = true;

            RenderSystem::window = makeWindow();
            RenderSystem::renderer = makeRenderer(RenderSystem::window);

        }



    }

    void updateData()
        {

            RenderGroup::update();
        }




    void execute(){

        SDL_SetRenderDrawColor(RenderSystem::renderer, 0, 0, 0, 255);

        SDL_RenderClear(RenderSystem::renderer);
        SDL_SetRenderDrawColor(RenderSystem::renderer, 20, 90, 100, 255);

        RenderGroup::update();
        RenderGroup::execute();

        SDL_RenderPresent(RenderSystem::renderer);







    }

    void terminate(){

    }




}

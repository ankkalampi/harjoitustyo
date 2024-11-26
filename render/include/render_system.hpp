#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP


#include "BulletDynamics/Dynamics/btRigidBody.h"
#include <SDL2/SDL_render.h>
#include <vector>
#include "../../systems/include/system.hpp"
#include "render_component.hpp"

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



        void init() override;

        void updateData() override;




        void execute() override;

        void terminate() override;

    };










}


#endif

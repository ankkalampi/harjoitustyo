#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP


#include "BulletDynamics/Dynamics/btRigidBody.h"
#include <SDL2/SDL_render.h>
#include <vector>

namespace Render{





    constexpr int DEFAULT_SCREEN_WIDTH = 1240;
    constexpr int DEFAULT_SCREEN_HEIGHT = 1080;


    inline int SCREEN_WIDTH = DEFAULT_SCREEN_WIDTH;
    inline int SCREEN_HEIGHT = DEFAULT_SCREEN_HEIGHT;


    extern SDL_Window* window;
    extern SDL_Renderer* renderer;

    inline std::vector<int> startIndices;
    inline std::vector<int> numVertices;
    inline std::vector<int> triangleIndices;
    inline std::vector<SDL_Vertex> allVertices;





    void init();

    void updateRenderDataFromPhysics(
                                        const std::vector<btRigidBody*>& rigidBodies,
                                        std::vector<SDL_Vertex>& vertices,
                                        const std::vector<int>& startIndices,
                                        const std::vector<int>& numberVertices);




    void update();

    void terminate();





}


#endif

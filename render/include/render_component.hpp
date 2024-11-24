#ifndef RENDER_COMPONENT_HPP
#define RENDER_COMPONENT_HPP

#include <SDL2/SDL_render.h>
#include <vector>
#include "../../data/include/component.hpp"


namespace Render{

    class RenderComponent : public Data::Component {
        public:
        std::vector<SDL_Vertex> vertices;
        std::vector<int> triangleIndices;

    };


    void addRenderComponent(RenderComponent* renderComponent);

    void removeRenderComponent(int id);
}


#endif
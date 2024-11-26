#ifndef RENDER_COMPONENT_HPP
#define RENDER_COMPONENT_HPP

#include <SDL2/SDL_render.h>
#include <vector>
#include "../../systems/include/component.hpp"
#include "LinearMath/btTransform.h"





namespace Render{

    class RenderComponent : public Systems::Component {
        public:
        std::vector<SDL_Vertex> vertices;
        std::vector<int> triangleIndices;
        btTransform* transform;
        bool visible;



        void addComponent(RenderComponent* renderComponent);

        void removeComponent(int id);

        ~RenderComponent();
    };



}


#endif
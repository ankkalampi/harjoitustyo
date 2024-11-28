#ifndef RENDER_DATA_HPP
#define RENDER_DATA_HPP

#include "LinearMath/btTransform.h"
#include "SDL_render.h"
#include "render_component.hpp"
#include <vector>

namespace Render {

    class RenderData{
        public:
        std::vector<SDL_Vertex> vertices;
        std::vector<int> triangles;
        btTransform* transform;
        RenderComponent* renderComponent;
        int meshSize;

        RenderData(
                    std::vector<SDL_Vertex> vertices,
                    std::vector<int> triangleIndices,
                    btTransform* transform,
                    RenderComponent *renderComponent) :
                    vertices(vertices),
                    triangles(triangleIndices),
                    transform(transform),
                    renderComponent(renderComponent),
                    meshSize(vertices.size()){}



    };
}


#endif
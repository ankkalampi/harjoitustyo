#pragma once

#include <SDL2/SDL_render.h>
#include <vector>
#include "../systems/component.hpp"
#include "LinearMath/btTransform.h"





namespace Render{

    class RenderComponent : public Systems::ComponentTemplate<RenderComponent> {
        public:
        std::vector<SDL_Vertex> vertices;
        std::vector<int> triangles;
        btTransform* transform;
        int id;

        



        void addComponent(RenderComponent* renderComponent);

        void removeComponent(int id);

        ~RenderComponent();
    };

    // function for saving render component data to render system's data structures
    void addRenderComponent(RenderComponent* renderComponent){

        size_t verticesTotal = allVertices.size();

        // add start point of this render component's vertices to startIndices
        startIndices.push_back(verticesTotal);

        // add number of this render component's vertices to numVertices
        numVertices.push_back(renderComponent->vertices.size());

        // add this render component's vertices to the end of allVertices
        allVertices.insert(allVerices.end(), renderComponent->vertices.begin(), renderComponent->vertices.end());

        // add triangulation information of this render component's vertices to triangleIndices
        for (int index : renderComponent->triangleIndices){
            triangleIndices.push_back(index + verticesTotal);
        }



    }


    void removeRenderComponent(int id);



}


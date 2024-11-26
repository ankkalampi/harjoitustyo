#include "../include/render_component.hpp"
#include "../include/render_system.hpp"
#include "../include/render_group.hpp"


namespace Render{

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
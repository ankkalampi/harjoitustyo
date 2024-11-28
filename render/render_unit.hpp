#ifndef RENDER_UNIT_HPP
#define RENDER_UNIT_HPP

#include "SDL_render.h"
#include "render_component.hpp"
#include "render_data.hpp"
#include <vector>
namespace Render{

    /*
    Meshes of same size form a render unit that use shared vertex vector. This makes
    removing render components easy, as the last render component's vertices can be
    moved to fill the empty space. This is only possibe is all meshes in the vector
    are of the same size.
    */

    class RenderUnit{
        public:

        std::vector<SDL_Vertex> vertices;               // vector containing all vertices

        std::vector<int> triangles;                     // vector containing triangle data

        std::vector<RenderComponent*> renderComponents; // rendercomponents of this render unit


        int meshSizeTriangle;                           // number of triangles in this render unit

        int meshSizeVertex;                             // number of vertices in this render unit

        int id;                                         // id numner for this render unit

        RenderUnit(int meshSizeVertex, int meshSizeTriangle, int id);

        // add mesh to render unit
        void add(RenderData* renderData);

        // remove component from render unit and manage vertex vector
        void remove(int componentIndex);


        // update render unit based of transforms
        void update();



        // generate render call
        void execute();

        RenderUnit::RenderUnit(
                            int meshSizeVertex,
                            int meshSizeTriangle,
                            int id) :

                            id(id),
                            meshSizeVertex(meshSizeVertex),
                            meshSizeTriangle(meshSizeTriangle),

                            vertices(std::vector<SDL_Vertex>()),
                            triangles(std::vector<int>()),

                            renderComponents(std::vector<RenderComponent*>()){}





    // add mesh to render unit
    void RenderUnit::add(RenderData* renderData){

            // add vertices
            this->vertices.insert(
                                    this->vertices.end(),
                                    renderData->vertices.begin(),
                                    renderData->vertices.end());

            // add triangles
            this->triangles.insert(
                                    this->triangles.end(),
                                    renderData->triangles.begin(),
                                    renderData->triangles.end());

            // add rendercomponent
            this->renderComponents.push_back(renderData->renderComponent);

    }

    // remove component from render unit and manage vertex vector
    // copies last item on each vector to replace the removed item(s)
    // and updates RenderGroup::groupMap
    void RenderUnit::remove(int componentIndex){

        // calculate start index of vertices to be removed
        int removableVertexIndex = componentIndex * this->meshSizeVertex;

        // calculate start index of triangles to be removed
        int removableTriangleIndex = componentIndex * this->meshSizeTriangle;

        // copy vertices of last mesh on top of removable vertices
        int lastMeshIndex = (this->vertices.size() * this->meshSizeVertex) - this->meshSizeVertex;
        for (int i = 0; i < this->meshSizeVertex; ++i){
            this->vertices[removableVertexIndex + i] = this->vertices[lastMeshIndex + i];
        }

        // copy triangles of last mest on top of removable triangles
        lastMeshIndex = (this->triangles.size() * this->meshSizeTriangle) - this->meshSizeTriangle;
        for (int i = 0; i < this->meshSizeVertex; ++i){
            this->triangles[removableTriangleIndex + i] = this->triangles[lastMeshIndex + i];
        }

        // delete renderComponent
        delete this->renderComponents[componentIndex];

        // move last render unit to componentIndex
        this->renderComponents[componentIndex] = this->renderComponents.back();
        this->renderComponents.pop_back();

        // remove vertices of last mesh
        for (int i = 0; i < this->meshSizeVertex; i++) this->vertices.pop_back();

        // remove triangles of last mesh
        for (int i = 0; i < this->meshSizeTriangle; i++) this->triangles.pop_back();


    }


    // update render unit based of transforms
    void RenderUnit::update(){

        // go through every render component
        for (int componentIndex = 0; componentIndex < this->renderComponents.size(); ++componentIndex){

            // get transform of render component
            btTransform* transform = this->renderComponents[componentIndex]->transform;
            btVector3 position = transform->getOrigin();
            btQuaternion rotation = transform->getRotation();

            // get start index and number of vertices of render component
            int start = this->meshSizeVertex * componentIndex;
            int count = this->meshSizeVertex;

            // check if render component is set to visible
            bool visible = this->renderComponents[componentIndex]->visible;

            // update all vertices affiliated with entity
            for (int i = 0; i < count; ++i) {
                SDL_Vertex& vertex = this->vertices[start + i];

                // convert vertices based on transform's position and rotation
                btVector3 localVertex(vertex.position.x, vertex.position.y, 0.0f);

                btVector3 worldVertex = *transform * localVertex;

                vertex.position.x = worldVertex.getX();
                vertex.position.y = worldVertex.getY();

                // turn vertices invisible or visible based on render component
                if (visible) vertex.color.a = 1.0f; else vertex.color.a = 0.0f;

            }


        }


    }



    // generate render call
    void RenderUnit::execute(){
        SDL_RenderGeometry(
                            RenderSystem::renderer,
                            NULL,
                            this->vertices.data(),
                            this->vertices.size(),
                            this->triangles.data(),
                            this->triangles.size());

    }






    };
}



#endif
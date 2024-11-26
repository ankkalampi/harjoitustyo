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





    };
}



#endif
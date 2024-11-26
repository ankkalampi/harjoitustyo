#ifndef RENDER_PIPELINE_HPP
#define RENDER_PIPELINE_HPP


#include "render_component.hpp"
#include "render_unit.hpp"
#include "render_data.hpp"
#include <SDL2/SDL_render.h>
#include <unordered_map>
#include <vector>
namespace Render {

    /*This module is responsible for creating render units for batched rendering.

    Meshes of same size form render units that use shared vertex vector. This makes
    removing render components easy, as the last render component's vertices can be
    moved to fill the empty space. This is only possibe is all meshes in the vector
    are of the same size.

    New render units are created on the fly when meshes are added, if no render unit
    can accomodate the mesh being added. */

    class RenderGroup{
        public:

        static bool unitsExist; // for checking if any render units exist

        static int runningId; // running number for render unit id numbers

        static std::unordered_map<RenderComponent*, std::pair<int, int>> groupMap;    // map to find correct component for removal
                                                                                    // pair: int unit, int index in unit

        static std::vector<RenderUnit> units;       // all render units


        // add mesh to group system. If no suitable unit found, create new one
        static void add(RenderData* renderData);

        // update all units based on transforms
        static void update();

        // generate render calls for all units
        static void execute();

        // remove component from group system
        static void remove(RenderComponent* renderComponent);


    };




}


#endif
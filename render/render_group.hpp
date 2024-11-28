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



    // add mesh to group system. If no suitable unit found, create new one
    void RenderGroup::add(RenderData* renderData){

        // check if any units exist, if not create unit vector
        if (!unitsExist) {
            RenderGroup::units = std::vector<RenderUnit>();
            RenderGroup::unitsExist = true;
        }

        // check if any unit is suitable for mesh size of render data
        for (RenderUnit& unit : RenderGroup::units){
            if (unit.meshSizeVertex == renderData->meshSize){
                unit.add(renderData);
                return;
            }
        }

        // if no suitable group found, create new group for this mesh size
        RenderGroup::units.push_back(RenderUnit(
                                                    renderData->meshSize,
                                                    renderData->triangles.size(),
                                                    RenderGroup::runningId));
        RenderGroup::runningId++;

    }

    // update all units based on transforms
    void RenderGroup::update(){
        if (!unitsExist) return;

        for(RenderUnit& unit : RenderGroup::units) unit.update();
    }

    // generate render calls for all units
    void RenderGroup::execute(){
        if (!unitsExist) return;

        for(RenderUnit& unit : RenderGroup::units) unit.execute();
    }

    // remove component from groups
    void RenderGroup::remove(RenderComponent* renderComponent){

        // find the correct group and index for render component to be removed
        int unit = RenderGroup::groupMap.find(renderComponent)->second.first;
        int index = RenderGroup::groupMap.find(renderComponent)->second.second;

        // remove renderComponent from its render unit. This deletes renderComponent
        // and moves last render component of unit to index of deleted renderComponent
        RenderGroup::units[unit].remove(index);

        // update groupMap so that reference to deleted render component is removed, and render component
        // that was moved to take its place now has updated reference.
        RenderGroup::groupMap.erase(renderComponent);
        RenderGroup::groupMap[RenderGroup::units[unit].renderComponents[index]].first = unit;
        RenderGroup::groupMap[RenderGroup::units[unit].renderComponents[index]].second = index;


    }


    };




}


#endif
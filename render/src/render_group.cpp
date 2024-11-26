#include "../include/render_unit.hpp"
#include "../include/render_group.hpp"
#include "../include/render_system.hpp"

#include "../include/render_data.hpp"
#include <SDL2/SDL_render.h>
#include <vector>

namespace Render{



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




    // constructor is called only when no suitable group is found for renderData, private constructor!
    RenderGroup::RenderGroup(RenderData* renderData){

        this->startIndices = std::vector<int>();
        this->numVertices = std::vector<int>();
        this->vertices = std::vector<SDL_Vertex>();
        this->triagleIndices = std::vector<int>();
        this->renderComponents = std::vector<RenderComponent*>();

        this->meshSize = renderData->vertices.size();
        this->add(renderData);


    }

    // add mesh to a group
    void RenderGroup::addToGroup(RenderData* renderData){

        int index; // index where mesh will be put
        if (this->hole){
            index = this->holeId;
            this->hole = false;
        } else {
            index = vertices.size();
        }
        this->numVertices.push_back(this->meshSize);
        this->startIndices.push_back(index);
        this->renderComponents.push_back(renderData->renderComponent);
        this->vertices.insert(
                                this->vertices.begin() + index,
                                renderData->vertices.begin(),
                                renderData->vertices.end());
        this->triagleIndices.insert(
                                this->triagleIndices.end()ääää,
                                renderData->triangleIndices.begin(),
                                renderData->triangleIndices.end());

    }

    // generate render call for a single group
    void RenderGroup::executeGroup(){
        SDL_RenderGeometry(
                            RenderSystem::renderer,
                            NULL,
                            this->vertices.data(),
                            this->vertices.size(),
                            this->startIndices.data(),
                            this->triagleIndices.size());
    }

    // update single group based of transforms
    void RenderGroup::updateGroup(){

        // go through every render component
            for (int entityRenderIndex = 0; entityRenderIndex < this->renderComponents.size(); ++entityRenderIndex){

                // get transform of render component
                btTransform* transform = this->renderComponents[entityRenderIndex]->transform;
                btVector3 position = transform->getOrigin();
                btQuaternion rotation = transform->getRotation();

                // get start index and number of vertices of render component
                int start = this->startIndices[entityRenderIndex];
                int count = this->numVertices[entityRenderIndex];

                // check if render component is set to visible
                bool visible = this->renderComponents[entityRenderIndex]->visible;

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





}

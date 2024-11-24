

#include "../include/render_system.hpp"
#include "../include/render_utils.hpp"
#include "../../physics/include/physics_system.hpp"
#include "BulletDynamics/Dynamics/btRigidBody.h"

namespace Render{




    void init(){
        window = makeWindow();
        renderer = makeRenderer(window);

    }

    void updateRenderDataFromPhysics(
                                        const std::vector<btRigidBody*>& rigidBodies,
                                        std::vector<SDL_Vertex>& vertices,
                                        const std::vector<int>& startIndices,
                                        const std::vector<int>& numberVertices)
        {



            for (size_t entityIndex = 0; entityIndex < rigidBodies.size(); entityIndex++) {
                btRigidBody* rigidBody = rigidBodies[entityIndex];

                // Hae rigidbodyn sijainti ja orientaatio
                btTransform transform;
                transform.setIdentity();
                rigidBody->getMotionState()->getWorldTransform(transform);


                btVector3 position = transform.getOrigin();
                btQuaternion rotation = transform.getRotation();

                // Päivitä kaikki vertexit tähän sijaintiin ja orientaatioon
                int start = startIndices[entityIndex];
                int count = numberVertices[entityIndex];
                for (int i = 0; i < count; ++i) {
                    SDL_Vertex& vertex = vertices[start + i];

                    // Muunna vertexin sijainti rigidbodyn sijainnin ja orientaation perusteella
                    btVector3 localVertex(vertex.position.x, vertex.position.y, 0.0f);

                    btVector3 worldVertex = transform * localVertex;

                    vertex.position.x = worldVertex.getX();
                    vertex.position.y = worldVertex.getY();

                }
            }

        }




    void update(){

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 20, 90, 100, 255);

        updateRenderDataFromPhysics(
                                    Physics::rigidBodies,
                                    allVertices,
                                    startIndices,
                                    numVertices);


        SDL_RenderGeometry(
                            renderer,
                            NULL,
                            allVertices.data(),
                            allVertices.size(),
                            triangleIndices.data(),
                            triangleIndices.size());

        SDL_RenderPresent(renderer);







    }

    void terminate(){

    }




}

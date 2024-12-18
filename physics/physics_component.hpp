#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP

#include "BulletCollision/CollisionShapes/btCollisionShape.h"

#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "LinearMath/btScalar.h"
#include "LinearMath/btVector3.h"


#include "../../systems/entity.hpp"
#include "../../systems/component.hpp"
#include "../../render/render_component.hpp"

namespace Physics{

    enum ColliderType{
        CONVEX,
        SQUARE,
        CIRCLE
    };

    class PhysicsComponent : public Systems::Component {
        public:
        btRigidBody* rigidBody;
        btCollisionShape* shape;

        btScalar* mass;
        btVector3* localInertia;
        btDiscreteDynamicsWorld* world;

        PhysicsComponent(
                        Systems::Entity* entity,
                        btRigidBody* rigidBody,
                        btCollisionShape* shape,
                        btScalar* mass,
                        btVector3* localInertia,
                        btDiscreteDynamicsWorld* world)
                        :
                        Systems::Component(entity),
                        rigidBody(rigidBody),
                        shape(shape),
                        mass(mass),
                        localInertia(localInertia),
                        world(world){}

        ~PhysicsComponent(){
            delete rigidBody;
            delete shape;
            delete mass;
            delete localInertia;
        }



    };

    // create new physics component object from render component (later data)
    PhysicsComponent* createPhysicsComponentFromRenderComponent(Render::RenderComponent& renderComponent);


    void addPhysicsComponent(PhysicsComponent* physicsComponent);

    void removePhysicsComponent(int id);

        // create new physics component object from render component (later data)
    PhysicsComponent* createPhysicsComponentFromRenderComponent(Render::RenderComponent& renderComponent){

        btConvexHullShape* collider = getColliderFromRenderComponent(&renderComponent);
        Systems::Entity* entity = getEntityFromRenderComponent(&renderComponent);
        btTransform* transform = getTransformFromRenderComponent(&renderComponent);
        btScalar mass = getMassFromData();
        btVector3 localInertia = getInertiaFromData(collider, mass);
        btRigidBody* rigidBody = getRigidBodyFromRenderComponent(
                                                                    transform,
                                                                    mass,
                                                                    collider,
                                                                    localInertia,
                                                                    g_world,
                                                                    g_rigidBodies,
                                                                    COLLISION_GROUP,
                                                                    COLLISION_MASK);

        // build PhysicsComponent
        PhysicsComponent* physComp = new PhysicsComponent(
                                                            entity,
                                                            rigidBody,
                                                            collider,
                                                            &mass,
                                                            &localInertia,
                                                            g_world);

        return physComp;
    }

    // function for saving render component data to render system's data structures
    void addPhysicsComponent(PhysicsComponent* physicsComponent){
        g_rigidBodies.push_back(physicsComponent->rigidBody);

    }

    void removePhysicsComponent(int id){

    }
}


#endif


#include "../include/physics_system.hpp"
#include "../include/physics_component.hpp"
#include "../include/physics_utils.hpp"

#include "../../render/include/render_component.hpp"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "LinearMath/btDefaultMotionState.h"
#include "LinearMath/btScalar.h"
#include "LinearMath/btTransform.h"
#include "LinearMath/btVector3.h"

#include <BulletCollision/CollisionShapes/btConvexHullShape.h>
#include "../../systems/include/entity.hpp"
#include "../../systems/include/component.hpp"



namespace Physics{

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

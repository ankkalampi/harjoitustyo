#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP

#include "BulletCollision/CollisionShapes/btCollisionShape.h"

#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "LinearMath/btScalar.h"
#include "LinearMath/btVector3.h"


#include "../../systems/include/entity.hpp"
#include "../../systems/include/component.hpp"
#include "../../render/include/render_component.hpp"

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
}


#endif

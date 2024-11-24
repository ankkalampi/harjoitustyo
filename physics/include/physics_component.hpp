#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP

#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include "BulletCollision/CollisionShapes/btConvexHullShape.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "LinearMath/btScalar.h"
#include "LinearMath/btVector3.h"
#include "SDL_render.h"
#include <vector>

#include "../../data/include/entity.hpp"
#include "../../data/include/component.hpp"

namespace Physics{

    enum ColliderType{
        CONVEX,
        SQUARE,
        CIRCLE
    };

    class PhysicsComponent : public Data::Component {
        public:
        btRigidBody* rigidBody;
        btCollisionShape* shape;

        btScalar* mass;
        btVector3* localInertia;

        PhysicsComponent(
                        Data::Entity* entity,
                        btRigidBody* rigidBody,
                        btCollisionShape* shape,
                        btScalar* mass,
                        btVector3* localInertia)
                        :
                        Data::Component(entity),
                        rigidBody(rigidBody),
                        shape(shape),
                        mass(mass),
                        localInertia(localInertia){}

        ~PhysicsComponent(){
            delete rigidBody;
            delete shape;
            delete mass;
            delete localInertia;
        }



    };

    PhysicsComponent createPhysicsComponentFromVertices(std::vector<SDL_Vertex>* vertices, ColliderType type);


    void addPhysicsComponent(PhysicsComponent* physicsComponent);

    void removePhysicsComponent(int id);
}


#endif


#include "../include/physics_system.hpp"
#include "../include/physics_component.hpp"
#include "../include/physics_utils.hpp"

#include "../../render/include/render_component.hpp"
#include "LinearMath/btDefaultMotionState.h"
#include "LinearMath/btTransform.h"
#include "LinearMath/btVector3.h"

#include <BulletCollision/CollisionShapes/btConvexHullShape.h>
#include "../../data/include/entity.hpp"
#include "../../data/include/component.hpp"



namespace Physics{

    // create new physics component object from render component
    PhysicsComponent* createPhysicsComponentFromRenderComponent(Render::RenderComponent& renderComponent, ColliderType type=ColliderType::CONVEX){

        // create collision shape for physics component from render component's vertices
        btConvexHullShape* collisionShape = createColliderFromVertices(renderComponent.vertices);

        // get render component's parent entity
        Data::Entity* entity = renderComponent.entity;

        // get render components parent entity's transform
        btTransform* transform = entity->transform;
        transform->setIdentity();

        // set mass and inertia
        btScalar mass = 1.0f;
        btVector3 localInertia(0, 0, 0);
        collisionShape->calculateLocalInertia(mass, localInertia);

        // create new rigidbody
        btDefaultMotionState* motionState = new btDefaultMotionState(*transform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, collisionShape, localInertia);
        btRigidBody* rigidBody = new btRigidBody(rbInfo);

        // add rigidbody to world
        world->addRigidBody(rigidBody, COLLISION_GROUP, COLLISION_MASK);
        create2DConstraint(rigidBody, world);
        rigidBodies.push_back(rigidBody); // Tallenna viite myöhempää päivitystä varten

        // build PhysicsComponent
        PhysicsComponent* physComp = new PhysicsComponent(entity, rigidBody, collisionShape, &mass, &localInertia);

        return physComp;


    }

    // function for saving render component data to render system's data structures
    void addPhysicsComponent(PhysicsComponent* physicsComponent){





    }

    void removePhysicsComponent(int id);
}


void generateRigidBodies(
        btDynamicsWorld* world,
        const std::vector<SDL_Vertex>& vertices,
        const std::vector<int>& startIndices,
        const std::vector<int>& numberVertices,
        std::vector<btRigidBody*>& rigidBodies){

            for (size_t entityIndex = 0; entityIndex < startIndices.size(); ++entityIndex){
                int start = startIndices[entityIndex];
                int count = numberVertices[entityIndex];

                // Luo törmäysmuoto (Convex Hull)
                btConvexHullShape* collisionShape = new btConvexHullShape();
                for (int i = 0; i < count; i++) {
                    const SDL_Vertex& vertex = vertices[start + i];
                    collisionShape->addPoint(btVector3(vertex.position.x, vertex.position.y, 0.0f));

                }



                std::cout << "adding shape, points in shape:  " << collisionShape->getNumPoints() << std::endl;
                // Aseta rigidbodyn alkuperäinen sijainti
                btTransform transform;
                transform.setIdentity();

                transform.setOrigin(btVector3(0.0f, 0.0f, 0.0f)); // Alkuperäinen sijainti

                // Rigidbodyn massa ja inertia
                btScalar mass = 1.0f;
                btVector3 localInertia(0, 0, 0);
                collisionShape->calculateLocalInertia(mass, localInertia);

                // Luo rigidbody
                btDefaultMotionState* motionState = new btDefaultMotionState(transform);
                btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, collisionShape, localInertia);
                btRigidBody* rigidBody = new btRigidBody(rbInfo);

                // Lisää rigidbody maailmaan
                world->addRigidBody(rigidBody, COLLISION_GROUP, COLLISION_MASK);
                make2D(rigidBody, world);
                rigidBodies.push_back(rigidBody); // Tallenna viite myöhempää päivitystä varten

            }

    }
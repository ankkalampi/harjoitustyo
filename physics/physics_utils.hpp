#ifndef PHYSICS_UTILS_HPP
#define PHYSICS_UTILS_HPP



#include "BulletCollision/CollisionShapes/btConvexHullShape.h"
#include "BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include <vector>
#include "../../render/render_component.hpp"


namespace Physics{

    // FUNCTIONS FOR GENERATING DATA FROM COMPONENT
    Systems::Entity* getEntityFromRenderComponent(Render::RenderComponent* rendComp);

    btTransform* getTransformFromRenderComponent(Render::RenderComponent* rendComp);

    btScalar getMassFromData();

    btConvexHullShape* getColliderFromRenderComponent(Render::RenderComponent* rendComp);

    btVector3 getInertiaFromData(btConvexHullShape* collisionShape, btScalar &mass);

    btRigidBody* getRigidBodyFromRenderComponent(
                                                    btTransform* transform,
                                                    btScalar &mass,
                                                    btConvexHullShape* collisionShape,
                                                    btVector3 &localInertia,
                                                    btDiscreteDynamicsWorld* world,
                                                    std::vector<btRigidBody*> rigidBodies,
                                                    short COLLISION_GROUP,
                                                    short COLLISION_MASK);


    // HELPER FUNCTIONS
    void create2DConstraint(btRigidBody *rigidBody, btDynamicsWorld* world);

    // FUNCTIONS FOR GENERATING COMPONENT FROM RENDER COMPONENT (later from data)
    Systems::Entity* getEntityFromRenderComponent(Render::RenderComponent* rendComp){
        return rendComp->entity;
    }

    btTransform* getTransformFromRenderComponent(Render::RenderComponent* rendComp){
        return rendComp->entity->transform;
    }

    btScalar getMassFromData(){
        btScalar mass = 1.0f;
        return mass;
    }

    btConvexHullShape* getColliderFromRenderComponent(Render::RenderComponent* rendComp){

        std::vector<SDL_Vertex>& vertices = rendComp->vertices;

        btConvexHullShape* collisionShape = new btConvexHullShape();
        for (int i = 0; i < vertices.size(); ++i ){
            const SDL_Vertex& vertex = vertices[i];
            collisionShape->addPoint(btVector3(vertex.position.x, vertex.position.y, 0.0f));
        }

        return collisionShape;
    }

    btVector3 getInertiaFromData(btConvexHullShape* collisionShape, btScalar &mass){
        btVector3 localInertia(0, 0, 0);
        collisionShape->calculateLocalInertia(mass, localInertia);

        return localInertia;
    }

    btDiscreteDynamicsWorld* getWorldFromData(){
        return Physics::g_world;
    }

    btRigidBody* getRigidBodyFromRenderComponent(
                                                    btTransform* transform,
                                                    btScalar &mass,
                                                    btConvexHullShape* collisionShape,
                                                    btVector3 &localInertia,
                                                    btDiscreteDynamicsWorld* world,
                                                    std::vector<btRigidBody*> rigidBodies,
                                                    short COLLISION_GROUP,
                                                    short COLLISION_MASK){

        btDefaultMotionState* motionState = new btDefaultMotionState(*transform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, collisionShape, localInertia);
        btRigidBody* rigidBody = new btRigidBody(rbInfo);
        world->addRigidBody(rigidBody, COLLISION_GROUP, COLLISION_MASK);
        create2DConstraint(rigidBody, world);
        rigidBodies.push_back(rigidBody); // Tallenna viite myöhempää päivitystä varte

        return rigidBody;
    }



    // HELPER FUNCTIONS
    void create2DConstraint(btRigidBody *rigidBody, btDynamicsWorld* world){
        btTransform zeroTranslation = btTransform::getIdentity();
        zeroTranslation.setOrigin(btVector3(0, 0, 0));  // Ei siirtoa Z-akselilla

        // Luo rajoite, joka estää liikkeen Z-akselilla
        btPoint2PointConstraint* constraint = new btPoint2PointConstraint(
                                                                        *rigidBody,
                                                                        btVector3(0, 0, 0));  // Rajoite X-Y-akseleilla

        world->addConstraint(constraint);

    }

}




#endif
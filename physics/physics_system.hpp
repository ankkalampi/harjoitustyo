#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include <SDL2/SDL_render.h>
#include <vector>


namespace Physics{

    // collision detection groups for bullet
    const short COLLISION_GROUP = 0x0001;
    const short COLLISION_MASK = -1;

    constexpr int DEFAULT_FPS = 60;
    inline int FPS_LIMIT = DEFAULT_FPS;


    inline std::vector<btRigidBody*> g_rigidBodies;


    inline btBroadphaseInterface* g_broadphase;
    inline btCollisionConfiguration* g_collisionConfig;
    inline btCollisionDispatcher* g_dispatcher;
    inline btSequentialImpulseConstraintSolver* g_solver;
    inline btDiscreteDynamicsWorld* g_world = new btDiscreteDynamicsWorld(g_dispatcher, g_broadphase, g_solver, g_collisionConfig);;



    void init();



    void generateRigidBodies(
                                btDynamicsWorld* world,
                                const std::vector<SDL_Vertex>& vertices,
                                const std::vector<int>& startIndices,
                                const std::vector<int>& numberVertices,
                                std::vector<btRigidBody*>& rigidBodies);

    void update();


    // bulletin törmäystarkistusryhmät
    const short COLLISION_GROUP = 0x0001;
    const short COLLISION_MASK = -1;








    void init(Data* data) {
        this->data = data;
        broadphase = new btDbvtBroadphase();
        collisionConfig = new btDefaultCollisionConfiguration();
        dispatcher = new btCollisionDispatcher(collisionConfig);
        solver = new btSequentialImpulseConstraintSolver();
        world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);






        generateRigidBodies(world, data->vertices, data->startIndices, data->numVertices, data->rigidBodies);
    }


    void make2D(btRigidBody *rigidBody, btDynamicsWorld* world){
        btTransform zeroTranslation = btTransform::getIdentity();
        zeroTranslation.setOrigin(btVector3(0, 0, 0));  // Ei siirtoa Z-akselilla

        // Luo rajoite, joka estää liikkeen Z-akselilla
        btPoint2PointConstraint* constraint = new btPoint2PointConstraint(
            *rigidBody, btVector3(0, 0, 0));  // Rajoite X-Y-akseleilla

        world->addConstraint(constraint);
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

    void update(){

        world->stepSimulation(1.0f / 60.0f);

    }

}

#endif
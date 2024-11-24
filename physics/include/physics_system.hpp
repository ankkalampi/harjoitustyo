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


    inline std::vector<btRigidBody*> rigidBodies;


    inline btBroadphaseInterface* broadphase;
    inline btCollisionConfiguration* collisionConfig;
    inline btCollisionDispatcher* dispatcher;
    inline btSequentialImpulseConstraintSolver* solver;
    inline btDynamicsWorld* world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);;



    void init();



    void generateRigidBodies(
                                btDynamicsWorld* world,
                                const std::vector<SDL_Vertex>& vertices,
                                const std::vector<int>& startIndices,
                                const std::vector<int>& numberVertices,
                                std::vector<btRigidBody*>& rigidBodies);

    void update();

}

#endif
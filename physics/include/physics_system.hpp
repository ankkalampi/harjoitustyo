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

}

#endif
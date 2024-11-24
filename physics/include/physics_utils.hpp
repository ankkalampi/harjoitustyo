#ifndef PHYSICS_UTILS_HPP
#define PHYSICS_UTILS_HPP



#include "BulletCollision/CollisionShapes/btConvexHullShape.h"
#include "BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "SDL_render.h"
#include <vector>


namespace Physics{

    btConvexHullShape* createColliderFromVertices(std::vector<SDL_Vertex>& vertices);

    void create2DConstraint(btRigidBody *rigidBody, btDynamicsWorld* world);

}




#endif
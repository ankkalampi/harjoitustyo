#ifndef PHYSICS_UTILS_HPP
#define PHYSICS_UTILS_HPP



#include "BulletCollision/CollisionShapes/btConvexHullShape.h"
#include "BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include <vector>
#include "../../render/include/render_component.hpp"


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

}




#endif
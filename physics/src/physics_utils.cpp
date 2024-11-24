
#include "../include/physics_utils.hpp"
#include "BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

namespace Physics {
    btConvexHullShape* createColliderFromVertices(std::vector<SDL_Vertex>& vertices){

        btConvexHullShape* collisionShape = new btConvexHullShape();
        for (int i = 0; i < vertices.size(); ++i ){
            const SDL_Vertex& vertex = vertices[i];
            collisionShape->addPoint(btVector3(vertex.position.x, vertex.position.y, 0.0f));
        }

        return collisionShape;
    }

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
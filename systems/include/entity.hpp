#ifndef ENTITY_HPP
#define ENTITY_HPP


#include "LinearMath/btTransform.h"
#include <string>




namespace Systems{

    struct Entity {
        int id;
        std::string name;
        btTransform* transform;

    };








}


#endif
#ifndef ENTITY_HPP
#define ENTITY_HPP


#include "LinearMath/btTransform.h"
#include <map>
#include <string>
#include <vector>




namespace Data{

    struct Entity {
        int id;
        std::string name;
        btTransform* transform;

    };








}


#endif
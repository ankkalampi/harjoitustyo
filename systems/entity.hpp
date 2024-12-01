#ifndef ENTITY_HPP
#define ENTITY_HPP


#include "LinearMath/btTransform.h"
#include "component.hpp"
#include <string>
#include <unordered_map>
#include <vector>




namespace Systems{


    
    class Entity {
        public:

        static std::vector<Entity*> entities;
        

        static std::unordered_map<btTransform*, Entity*> entityTransformMap;

        int id;
        std::string name;
        btTransform* transform;
        std::vector<Component*> components;

    };








}


#endif
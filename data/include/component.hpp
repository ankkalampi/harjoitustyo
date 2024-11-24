#ifndef COMPONENT_HPP
#define COMPONENT_HPP



#include <map>
#include <vector>


#include "entity.hpp"

namespace Data{


    class Component {

        public:


        Entity* entity;

        Component(Entity* entity) : entity(entity){}

        virtual ~Component() = default;


    };

    inline std::map<Entity, std::vector<Component>> componentMap;




}


#endif
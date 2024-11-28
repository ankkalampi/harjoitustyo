#ifndef COMPONENT_HPP
#define COMPONENT_HPP





#include "entity.hpp"

namespace Systems{


    class Component {

        public:


        Entity* entity;

        Component(Entity* entity) : entity(entity){}

        virtual Component generateComponent();

        virtual void addComponent();

        virtual void removeComponent();

        virtual ~Component() = default;


    };






}


#endif
#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "LinearMath/btTransform.h"
#include <map>
#include <vector>
#include "entity.hpp"
#include "component.hpp"


namespace Systems{






    class System{
        public:

        static std::vector<btTransform*> transforms;
        static std::map<Entity, std::vector<Component>> componentMap;
        static std::vector<Entity> allEntities;

        virtual void init();

        virtual void updateData();

        virtual void execute();

        virtual void terminate();


    };


    class SystemData{

    };
}

#endif
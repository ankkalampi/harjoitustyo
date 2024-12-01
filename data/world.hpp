#pragma once

#include "../systems/system.hpp"
#include "../systems/entity.hpp"

namespace Data{

    class World{
        public:

        static World* currentWorld;

        // map structure for all loaded worlds. key: string name
        static std::pmr::unordered_map<std::string, World*> worldsMap;

        // all systems in world instance
        std::vector<Systems::System*> systems;

        // all entities in world instance 
        std::vector<Systems::Entity*> entities;


    };

}
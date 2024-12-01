#pragma once

#include <vector>
#include "../systems/system.hpp"
#include "../systems/entity.hpp"
#include "../data/data_handler.hpp"

namespace Runtime{

    enum class RuntimeGroup{
        GROUP1,
        GROUP2,
        GROUP3,
        GROUP4,
        EVERY_N1,
        EVERY_N2,
        EVERY_N3,
        EVERY_N4,
        EVERY_N5,
        EVERY_N6,
        EVERY_N7
    };

    constexpr int n1 = 0;
    constexpr int n2 = 0;
    constexpr int n3 = 0;
    constexpr int n4 = 0;
    constexpr int n5 = 0;
    constexpr int n6 = 0;
    constexpr int n7 = 0;


    class Runtime{

        // all active entities in runtime
        static std::vector<Systems::Entity*> entities;

        // all active systems in runtime
        static std::vector<Systems::System*> systems;


        // ADD-FUNCTIONS--------------------------------------------------------------

        // add an entity to worldfile
        static void add(Systems::Entity* entity){
            entities.push_back(entity);
            for (Systems::Component* component : entity->components){
                
            }
        }

        // add a world file to runtime
        static void add(std::string worldFile){
            for(Systems::Entity* entity : Data::loadEntities(worldFile)){
                add(entity);
            }
        }

        //-----------------------------------------------------------------------------


        void run();

        void terminate();

        

    };
    

}

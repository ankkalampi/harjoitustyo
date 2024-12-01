#pragma once

#include "../systems/system.hpp"
#include "../systems/component.hpp"
#include <vector>
#include "../libs/json.hpp"

const std::string PATH_TO_WORLDS = "../assets/worlds";
const std::string PATH_TO_CONCEPTS = "../assets/concepts";
const std::string PATH_TO_COMPONENTS = "../assets/components";

using json = nlohmann::json;
namespace Data{

    static std::vector<Systems::Component*> loadConcept(){

    }


    static Systems::Entity* loadEntity(){

    }

    static void loadWorld(){

    }

    static std::vector<Systems::Entity*> loadEntities(std::string world){
        
    }

}
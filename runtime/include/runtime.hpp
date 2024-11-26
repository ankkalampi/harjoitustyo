#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <vector>
#include "../../systems/include/system.hpp"
#include "../../systems/include/entity.hpp"

namespace Runtime{

    enum RuntimePriority{
        HIGH1,
        HIGH2,
        HIGH3,
        MEDIUM1,
        MEDIUM2,
        MEDIUM3,
        LOW1,
        LOW2,
        LOW3
    };

    inline std::vector<Systems::System> g_systems;
    inline std::vector<Systems::Entity> g_entities;



    void init();

    void run();

    void terminate();

}

#endif
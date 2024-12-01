#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "LinearMath/btTransform.h"
#include <map>
#include <vector>
#include "entity.hpp"
#include "component.hpp"
#include <functional>
//#include "../runtime/runtime.hpp"



namespace Systems{

    // forward declaration of runtimegroup
    namespace Runtime{
        enum class RuntimeGroup;
    }
    

    class System{
        public:


        // this map tells which add function to use for each system
        static std::unordered_map<std::string, std::function<void(Entity*)>> systemStartMap;


        

    };

    template <typename Derived>
    class SystemTemplate : System{
        public: 

        


        static Derived* instance;

        // this function adds system's add function to systemsstartmap without the need 
        // for instantiating the system
        static bool registerSystem(){
            System::systemStartMap[Derived::systemName] = Derived::add;
            return true;
        }
        const static bool registered = registerSystem();

        static void add(Entity* entity){

        }

        const std::string systemName;

        const Runtime::RuntimeGroup runtimeGroup;

        

        // adds entity to system. If entity has a component that hasn't been 
        // added yet, add that component to system
        void systemAdd(Component* component){
            if (!Derived::instance){
                Derived::instance = new Derived();
            }
            instance->add(component);

        }

        // remove entity from system. If this is the last entity to be connected with 
        // its component, remove component also
        void systemRemove(){

        }

        // read relevant data to update system data
        void systemUpdate(){

        }

        // execute the main function of system. Rendering for render system, physics simulation
        // for physics system etc
        void systemExecute(){

        }

        // close system and delete all its possessions
        void systemTerminate(){

        }
    };


    
}

#endif
#ifndef COMPONENT_HPP
#define COMPONENT_HPP





#include <string>
namespace Systems{


    class Component {
        public:

        
    };

    template <typename Derived>
    class ComponentTemplate : public Component{
        public:

        static Derived* loadComponent(std::string component){

        }
    };






}


#endif
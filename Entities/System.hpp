#ifndef ENGINE_SYSTEM_H
#define ENGINE_SYSTEM_H

#include <vector>
#include "EntityComponent.hpp"
/*system takes a set of components and updates them*/

class BaseSystem {

public:

    BaseSystem(std::vector<uint32_t>& types) : componenttypes(types){}
    virtual void UpdateComponents(float d, BaseComponent** comp);
    const std::vector<uint32_t > GetComponentTypes(){ return  this->componenttypes ; }

private:
    /*array or component id's*/
    std::vector<uint32_t> componenttypes;
};


#endif //ENGINE_SYSTEM_H

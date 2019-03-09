#include "EntityComponent.hpp"



uint32_t BaseComponent::Register(CreateComponent createfn, DestroyComponent destroyfn, size_t compsize) {


    uint32_t compID = componentstore.size();

    componentstore.push_back(std::tuple<CreateComponent ,DestroyComponent, size_t >(createfn,destroyfn,compsize));


    return compID;
}

//
// Created by zach on 3/9/19.
//

#include "ECS.hpp"
#include <stdio.h>


ECS::~ECS(){
    uint32_t i;

    uint32_t esize = entities.size();
    for(i = 0; i < esize; i++)
        delete entities[i];


    for (auto it = components.begin(); it != components.end(); ++it){
        /*get size and delete implementation for a component*/
        size_t compsize = BaseComponent::GetComponentSize(it->first);
        DestroyComponent destroyfn = BaseComponent::GetDestroyFunction(it->first);

        for(i = 0; i < it->second.size(); i+= compsize )
            destroyfn((&it->second[i]));
    }

}

/**** ENTITY FUNCTIONS****/

void *ECS::MakeEntity(BaseComponent *comp, const uint32_t *compId, size_t ncomp) {

    /*create the new entity */
    std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t> > >*  newentity =

            new std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t> >>();
    /*get the raw memory address of the new entitiey*/
    void* newentityhandle = reinterpret_cast<void*>(newentity);

    for( uint32_t i = 0; i < ncomp; i++ ){

        if(!BaseComponent::IsValid(compId[i])){
            delete newentity;
            return nullptr;
        }

        TypeSafeAdd(newentity->second, compId[i], &comp[i]);

        /*get base component creation and how to create*/
        /*create this way for easier reading*/
        //std::pair<uint32_t , uint32_t > tostore;
        //tostore.first = compId[i];
        //CreateComponent createfn = BaseComponent::GetCreateFunction(compId[i]);
        //tostore.second = createfn(components[compId[i]], newentityhandle, &comp[i]);

        /*store handle to the component and create the component*/
        //newentity->second.push_back(tostore);
        //(components[compId[i]] , newentityhandle, &comp[i] );
    }

    /*get the size and add to list*/
    newentity->first = entities.size();
    entities.push_back(newentity);

    return newentity;
}

void ECS::RemoveEntity(void *handle) {

    std::vector<std::pair<uint32_t , uint32_t >&> ent = FindType(handle);

    for( uint32_t i = 0; i < ent.size(); i++ ){

        TypeSafeRemove(ent[i].first , ent[i].second);
    }

    uint32_t  dindex = EntiesIDHandle((handle));
    uint32_t  findex = ent[entities.size()-1];
    /*last entity to deleted memory to 'begining of arr*/
    delete entities[dindex];
    entities[dindex]=entities[findex];
    /*possibly change to other data structure in future*/
    entities.pop_back();
}

void ECS::TypeSafeRemove(uint32_t id, uint32_t index) {


}

void
ECS::TypeSafeAdd(std::vector<std::pair<uint32_t, uint32_t>> &entity, uint32_t componentid, BaseComponent *component) {

    /*get base component creation and how to create*/
    /*create this way for easier reading*/
    std::pair<uint32_t , uint32_t > tostore;
    tostore.first = componentid;
    CreateComponent createfn = BaseComponent::GetCreateFunction(componentid);
    tostore.second = createfn(components[componentid], handle, component);

    /*store handle to the component and create the component*/
    entity.push_back(tostore);


}









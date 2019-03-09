#ifndef ENGINE_ECS_H
#define ENGINE_ECS_H

#include "EntityComponent.hpp"
#include "System.hpp"
#include <vector>
#include <map>


class ECS {

public:
    ECS(){};
    ~ECS();

    void* MakeEntity(BaseComponent* comp, const uint32_t* compId, size_t ncomp);
    void RemoveEntity(void* handle);

    template <class Component>
    void AddComponent(void* entity, Component* comp){

        TypeSafeAdd( EntitiesHandle(entity), Component::ID, comp);
    };

    template <class Component>
    void RemoveComponent(void* entity);

    template <class Component>
    void GetComponent(void* entity);



    inline void AddSystem(BaseSystem& system){
        systems.push_back(&system);
    };

    inline void UpdateSystem(float d){

    }

private:
    std::vector<BaseSystem*> systems;
    std::map< uint32_t , std::vector<uint32_t> > components;

    std::vector<std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t> > >* > entities;


    inline std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t> > >* FindType(void* handle){

        return reinterpret_cast<std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t> > >*>(handle);

    }

    inline uint32_t EntiesIDHandle(void* handle){
        return FindType(handle)->first;
    }

    inline std::vector<std::pair<uint32_t , uint32_t >>&EntitiesHandle(void* handle){

        return FindType(handle)->second;
    }

    void TypeSafeRemove(uint32_t id, uint32_t index);

    void TypeSafeAdd(std::vector<std::pair<uint32_t,uint32_t>> &entity , uint32_t componentid ,
            BaseComponent* component);

};


#endif //ENGINE_ECS_H

/*entity management system based a lot off
 * https://www.gamedev.net/articles/programming/general-and-gameplay-programming/the-entity-component-system-c-game-design-pattern-part-1-r4803/*/
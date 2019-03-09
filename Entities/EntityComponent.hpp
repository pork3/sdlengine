#ifndef ENGINE_ENTITYCOMPONENT_H
#define ENGINE_ENTITYCOMPONENT_H
#include <cstdint>
#include <vector>
#include <tuple>
/*
 * This class is the base of the component system. The architecture is based off the ECS (entity component system
 * architecture... the separation of data, what to draw and how to interact. This is the base of all entities within
    the game. As a component may be of any type, a 'dynamic' typing system is needed to manage all entieis

 */
class BaseComponent;
#define NULL_HANDLE nullptr
/*function pointer typedefs*/
typedef uint32_t (*CreateComponent)(std::vector<uint32_t>& array, void* handle , BaseComponent* component);
typedef void (*DestroyComponent)(BaseComponent* comp);

/*The base class, containing a handle to the entity and a unique id*/
class BaseComponent {

public:
    /*way to refer to what component is attached to right now void*
     * to refer to a memory address*/
    void* EntityID = NULL_HANDLE;

    /*way of generating a referal id*/
    static uint32_t Register(CreateComponent createfn , DestroyComponent destroyfn, size_t compsize);

    /*Getters for accessing registered components*/

    inline static CreateComponent GetCreateFunction(uint32_t id){

        return std::get<0>((componentstore)[id]);
    }

    inline static DestroyComponent GetDestroyFunction(uint32_t id){

        return std::get<1>((componentstore)[id]);
    }

    inline static size_t GetComponentSize(uint32_t id){

        return std::get<2>((componentstore)[id]);
    }

    inline static bool IsValid(uint32_t id){
        return id <= componentstore.size();
    }



private:
    /*private data of all components registerd*/
    static std::vector<std::tuple<CreateComponent ,DestroyComponent, size_t > > componentstore;
};


/*template class used for entity creation, allows for the user
 * to easily create a component and have the system automatially
 * handle back end creation */
template <typename T>
class BaseComponentData : public BaseComponent{

    /*unique ID to refer to component*/
    static const uint32_t  ID;
    /*size of the entity with this ID in bytes*/
    static const uint32_t SIZE_B;
    static const CreateComponent CREATE;
    static const DestroyComponent DESTROY;
};

/*template class to craete a 'component'  calculates how much memory is needed  for the entity, allocates
 * enough space if needed then creates the handle to the created obj*/
template<typename Component>
uint32_t TCreateComponent(std::vector<uint32_t>& mem, void* handle , BaseComponent* component){

    uint32_t index = mem.size();
    mem.resize(index + Component::SIZE);
    Component* newcomp = new(&mem[index]) Component(*(Component*)component);
    newcomp->EntityID = handle;
};

/*template class to ensure the destructor will always be called*/
template<typename Component>
void TDestroyComponent(BaseComponent* comp){
    /*ensure the destructor is called*/
    Component* c = reinterpret_cast<Component*>(comp);
    c->~Component();
};

/*template function to increase the id on Creation*/
template <typename T>
const uint32_t BaseComponentData<T>::ID(BaseComponent::Register(TCreateComponent<T>) ,TDestroyComponent<T> , sizeof(T) );

/*template function to returen the size of in bytes of a component*/
template <typename T>
const uint32_t BaseComponentData<T>::SIZE_B(sizeof(T));


template<typename T>
const CreateComponent BaseComponentData<T>::CREATE(TCreateComponent<T>);

template<typename T>
const DestroyComponent BaseComponentData<T>::DESTROY(TDestroyComponent<T>);






#endif //ENGINE_ENTITYCOMPONENT_H


/*example usage
 *
 * class : public BaseComponentData<entity>{
 *
 * int x;
 * int y;
 * }
*/

/* entity component overview and example code based off
 * https://www.gamasutra.com/blogs/TobiasStein/20171122/310172/The_EntityComponentSystem__An_awesome_gamedesign_pattern_in_C_Part_1.php
 * */
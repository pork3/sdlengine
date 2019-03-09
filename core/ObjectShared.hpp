#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H
// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
#include "Transform.h"
#include "../rendering/Mesh.h"
#include "../rendering/Textures.hpp"

/*
 *
 *	Last updated by: Zachary Bower
 *	Last updated on: Mar 3, 2019
 *
 *	Purpose:
 *		Base class for all entities, all objects will inherit from this class
 *      
 *
 */

class ObjectShared {

public:

    ObjectShared() {};

    virtual void Update();

    virtual Transform* GetTransform();

    virtual void Render(const Textures& t, const Mesh& m);



private:


};


#endif //ENGINE_ENTITY_H

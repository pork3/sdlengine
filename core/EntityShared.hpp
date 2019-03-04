#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H
// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
#include "Transform.h"

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

class EntityShared {

public:

    EntityShared() = 0;

    virtual void ProcessInput(const Event& e, float d);

    virtual void Update();

    virtual Transform* GetTransform()



private:


};


#endif //ENGINE_ENTITY_H

// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 
 	Last updated by: Chase Craig
 	Last updated on: Mar. 11, 2019
 
 	Purpose:
		This file serves as a class to handle transformations of objects in 3-D space.
			Handles the creation of the world transformation matrix for rendering models.
   
	Notes:
		See Transform.h for usage of this object.
 */

// Required for headers below. Enables experimental GLM state
#define GLM_ENABLE_EXPERIMENTAL 

// Headers to use matrix transformations

#include "Transform.h"
#include <glm/gtx/transform.hpp>

// Constructor, takes a offset, a rotation and a scaling vector to define the transformation matrix.
Transform::Transform(const glm::vec3& pos, const glm::vec3 rot, const glm::vec3 scl){

        this->pos = pos;
        this->rot = rot;
        this->scl = scl;
}
// Function that returns the transformation matrix for GLM.
glm::mat4 Transform::MatModel() const {

        /*creates the transform matrix for position and scale*/
        glm::mat4 posmat = glm::translate(this->pos);
        glm::mat4 sclmat = glm::translate(this->scl);

        /*right now use matrix, eventually switch to quaternion rotation*/
        glm::mat4 rotmatx = glm::rotate(rot.x, glm::vec3(1,0,0));
        glm::mat4 rotmaty = glm::rotate(rot.y, glm::vec3(0,1,0));
        glm::mat4 rotmatz = glm::rotate(rot.z, glm::vec3(0,0,1));

        /*combine the rotation matrix*/
        glm::mat4 rotmat = rotmatz * rotmaty * rotmatx;

        /*combine all matrices... this scales, rotates and then moves matrix*/
        return posmat * rotmat * sclmat;
}



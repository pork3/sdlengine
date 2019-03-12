#ifndef ENGINE_TRANSFORM_H
#define ENGINE_TRANSFORM_H

// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 
 	Last updated by: Chase Craig
 	Last updated on: Mar. 11, 2019
 
 	Purpose:
		This file serves as a class to handle transformations of objects in 3-D space.
			Handles the creation of the world transformation matrix for rendering models.
   
	Usage:
		One can use this class for handling scaling/rotations and offsets for rendering models with opengl.
		
		Has getters and setters for the offset (position) vector, the rotation vector, and the scale vector.
		(Get/SetPos, Get/SetRot, Get/SetScl respectively).
		
		An additional function named MatModel() returns the matrix transformation following the 
			offset * rotation * scaling transformation scheme.
 */

#include <glm/glm.hpp>

class Transform {

public:

	// Default constructor for the identity transform.
	Transform() : pos(glm::vec3(0,0,0)), rot(glm::vec3(0,0,0)), scl(glm::vec3(1,1,1)){}
	// Constructor, requires a position, rotation and scalar vectors to define the transformation matrix.
    Transform(const glm::vec3& pos, const glm::vec3 rot , const glm::vec3 scl);

    /*getters for position, rotation and scale*/
    glm::vec3& GetPos(){return pos;}
    glm::vec3& GetRot(){return rot;}
    glm::vec3& GetScl(){return scl;}

    /*setters for position rotation and scale*/
    void SetPos(const glm::vec3& p){this->pos = p;}
    void SetRot(const glm::vec3& r){this->rot = r;}
    void SetScl(const glm::vec3& s){this->scl = s;}

    glm::mat4 MatModel() const;

private:
    /*position*/
    glm::vec3 pos;
    /*rotation*/
    glm::vec3 rot;
    /*scale*/
    glm::vec3 scl;

};


#endif //ENGINE_TRANSFORM_H

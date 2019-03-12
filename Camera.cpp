#include "Camera.h"


// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 
 	Last updated by: Chase Craig
 	Last updated on: Mar. 11, 2019
 
 	Purpose:
		This file allows for setting up the projection of the user's rendering view, named a camera.
			
	Note:
		See Camera.h for usage and notes.
 */

Camera::Camera(const glm::vec3 &pos, float fov, float aspect, float near, float far){

    perspective = glm::perspective(fov, aspect, near, far );
    this->position = pos;

    // Currently the camera is forced to look forward and up. In future revisions this will be updated
	// 		to support different forward/up vectors.
    this->forward = glm::vec3(0,0,-1);
    this->up = glm::vec3(0,1,0);
}

glm::mat4 Camera::GetProjection() const {

    // Get the perspective the camera should have based on current position and forward and up
    return perspective * glm::lookAt(position, position + forward , up);

}

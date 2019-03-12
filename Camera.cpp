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
    this->position = glm::vec4(pos,1.0f);

    // Currently the camera is forced to look forward and up. In future revisions this will be updated
	// 		to support different forward/up vectors.
    this->forward = glm::vec4(0,0,-1,1);
    this->up = glm::vec4(0,1,0,1);
}

glm::mat4 Camera::GetProjection() const {
    glm::vec4 temporary = position + forward;
    // Get the perspective the camera should have based on current position and forward and up
    return perspective * glm::lookAt(glm::vec3(position[0], position[1], position[2]), glm::vec3(temporary[0], temporary[1], temporary[2]), glm::vec3(up[0], up[1], up[2]));

}



void Camera::CleanupLookVectors(){



}


void Camera::SetEulerRotation(glm::vec3& rot){
    this->rotation = rot;

    glm::mat4 rotM = glm::rotate(rot[0], glm::vec3(1.0f,0.0f,0.0f));
    rotM = glm::rotate(rotM, rot[1], glm::vec3(rotM * glm::vec4(0.0f,1.0f,0.0f,1.0f)));
    rotM = glm::rotate(rotM, rot[2], glm::vec3(rotM * glm::vec4(0.0f,0.0f,1.0f,1.0f)));
    this->forward = rotM * glm::vec4(0,0,-1,1);
    this->up = rotM * glm::vec4(0,1,0,1);
}

void Camera::SetEulerRotation(glm::vec3&& rot){
    this->rotation = rot;
    glm::mat4 rotM = glm::rotate(rot[0], glm::vec3(1.0f,0.0f,0.0f));
    rotM = glm::rotate(rotM, rot[1], glm::vec3(rotM * glm::vec4(0.0f,1.0f,0.0f,1.0f)));
    rotM = glm::rotate(rotM, rot[2], glm::vec3(rotM * glm::vec4(0.0f,0.0f,1.0f,1.0f)));
    this->forward = rotM * glm::vec4(0,0,-1,1);
    this->up = rotM * glm::vec4(0,1,0,1);
}
void Camera::MoveRelativeToView(glm::vec3& pos){

    glm::mat4 rotM = glm::rotate(this->rotation[0], glm::vec3(1.0f,0.0f,0.0f));
    rotM = glm::rotate(rotM, this->rotation[1], glm::vec3(rotM * glm::vec4(0.0f,1.0f,0.0f,1.0f)));
    rotM = glm::rotate(rotM, this->rotation[2], glm::vec3(rotM * glm::vec4(0.0f,0.0f,1.0f,1.0f)));
    this->position += rotM * glm::vec4(pos, 1);
}
void Camera::MoveRelativeToView(glm::vec3&& pos){

    glm::mat4 rotM = glm::rotate(this->rotation[0], glm::vec3(1.0f,0.0f,0.0f));
    rotM = glm::rotate(rotM, this->rotation[1], glm::vec3(rotM * glm::vec4(0.0f,1.0f,0.0f,1.0f)));
    rotM = glm::rotate(rotM, this->rotation[2], glm::vec3(rotM * glm::vec4(0.0f,0.0f,1.0f,1.0f)));
    this->position += rotM * glm::vec4(pos, 1);
}
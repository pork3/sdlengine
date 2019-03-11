#include "Camera.h"

Camera::Camera(const glm::vec3 &pos, float fov, float aspect, float near, float far){

    perspective = glm::perspective(fov, aspect, near, far );
    /*calculate with function?*/
    this->position = pos;

    /******* HARD CODED VALUES CHANGE ******/
    this->forward = glm::vec3(0,0,-1);
    this->up = glm::vec3(0,1,0);
}

glm::mat4 Camera::GetProjection() const {

    /*get the perspective the camera should have based on current position and forward and up*/
    return perspective * glm::lookAt(position, position + forward , up);

}

#include "Camera.h"

Camera::Camera(const glm::vec3 &pos, float fov, float aspect, float near, float far){

    perspective = glm::perspective(fov, aspect, near, far );
    /*calculate with function?*/
    this->position = pos;


    this->forward = glm::vec3(0,0,1);
    this->up = glm::vec3(0,1,0);
}

glm::mat4 Camera::GetProjection() const {

    return perspective * glm::lookAt(position, position + forward , up);

}

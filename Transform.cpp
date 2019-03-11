//
// Created by zach on 2/17/19.
//

#include "Transform.h"
/*header to use matrix transformations*/
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

Transform::Transform(const glm::vec3& pos, const glm::vec3 rot, const glm::vec3 scl){

        this->pos = pos;
        this->rot = rot;
        this->scl = scl;
}

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



#ifndef ENGINE_TRANSFORM_H
#define ENGINE_TRANSFORM_H
/*class that deals with matrix transformations of vectors
 * currently can handler moving position, rotation and scale*/
#include <glm/glm.hpp>

class Transform {

public:
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

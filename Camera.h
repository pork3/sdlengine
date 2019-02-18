#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {

public:
    Camera(const glm::vec3& pos , float fov, float aspect, float near, float far);

    glm::mat4 GetProjection() const;


private:
    glm::mat4 perspective;
    glm::vec3 position;

    /*forward disrection from current view angle*/
    glm::vec3 forward;
    /*up direction from current view angle*/
    glm::vec3 up;


};


#endif //ENGINE_CAMERA_H

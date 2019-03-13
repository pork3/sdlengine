#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 
 	Last updated by: Chase Craig
 	Last updated on: Mar. 12, 2019
 
 	Purpose:
		This file allows for setting up the projection of the user's rendering view, named a camera.
			
	Usage:
		This will take a camera position (offset in the world), a field of view (fov), an aspect ratio
		the near plane rendering cutoff (anything to be rendered closer than this to the camera will not 
		render), and the far plane rendering cutoff (anything to be rendered further than this to the camera
		will not render).
		
		The camera does not and will never have a default constructor!
		
		The camera has its own rendering transformation matrix for rendering.
		
	Notes:
		The camera currently does not support changing the "up" and "forward" directions, however, this shall
		be fixed in a future revision.
 */

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {

public:
    Camera(const glm::vec3& pos , float fov, float aspect, float near, float far);

    glm::mat4 GetProjection() const;

    void SetPosition(glm::vec3& pos){this->position = glm::vec4(pos,1.0f);}
    void SetPosition(glm::vec3&& pos){this->position = glm::vec4(pos,1.0f);}

    void MoveRelativeToView(glm::vec3& pos);
    void MoveRelativeToView(glm::vec3&& pos);


    // Sets the rotation of the system
    void SetEulerRotation(glm::vec3& rot);
    void SetEulerRotation(glm::vec3&& rot);

    // Note, when calling this function, unless CleanupLookVectors is called, the vectors may be coupled.
    void SetForwardVector(glm::vec3& forw){this->forward = glm::vec4(forw,1.0f);}
    void SetUpVector(glm::vec3& up){this->up = glm::vec4(up,1.0f);}

    // Will take the up vector, subtract off the coupling and will attempt to renormalize. If up is 0,
    // then it will default both up and forward to the default up and forward vectors.
    void CleanupLookVectors();

private:
    glm::mat4 perspective;
    glm::vec4 position;

    glm::vec3 rotation;

    
	//	Forward disrection from current view angle
    glm::vec4 forward;
    //	Up direction from current view angle
    glm::vec4 up;


};


#endif //ENGINE_CAMERA_H

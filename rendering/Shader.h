#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

#include <string>
#include <GL/glew.h>
#include "../core/Transform.h"
#include "Camera.h"

class Shader {

public:
    Shader(const std::string& fname);
    ~Shader();

    /*TODO add separate creation functions for
     * vertex and fragment shaders*/

    void Bind();
    /*updated the values in the shader*/
    void Update(const Transform& t, const Camera& camera);

private:

    /** HELPER FUNCTIONS FOR CREATING AND VERIFYING SHADERS*/
    std::string loadshader(const std::string fname);
    GLuint createshader(const std::string& file, GLenum type);
    /*change in final to use error class*/
    void verifyshader(GLuint shader, GLuint flag, bool isprog, const std::string& error);

    /* enum to refer to shader types*/
    enum SHADERTYPE{
        VERTEX,
        FRAGMENT,
        N_SHADER
    };

    enum UNIFORM{
        TRANSFORM,
        NUNIFORM
    };

    /*handle of current position*/
    GLuint prog;
    /*array of shaders*/
    GLuint nshaders[N_SHADER];
    /*array of uniform types*/
    GLuint nuniform[NUNIFORM];


};


#endif //ENGINE_SHADER_H

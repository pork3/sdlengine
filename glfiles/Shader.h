#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H
// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*

 	Last updated by: Zachary Bower
 	Last updated on: Mar. 11, 2019

 	Purpose:
		This file creates a shader used by opengl to perform operations on the drawn vertices. A vertex shader
		is a shader that affects all vertices (usually used in transforms) a fragment shader is a shader which
		normally affects pixels (color)


 */


#include <string>
#include <GL/glew.h>
#include "../Transform.h"
#include "../Camera.h"

class Shader {

public:
    /*takes a string as an input, the filename of the desired shader. Shader programs are written in
     * GLSL and should be placed in the directory /glfiles/shaders
     * the current convention is for frament to end in a .frag and vertex shaders to end in a .vert*/

    Shader(const std::string& fname);
    ~Shader();

    /*TODO add separate creation functions for
     * vertex and fragment shaders*/
    /*tell OpenGL to use these shaders within the current context*/
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
    /*enum to rever to the current UNIFORM
     * a uniforma is a reference to the shader and this
     * program*/
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

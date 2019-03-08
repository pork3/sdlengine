#include "Shader.h"
#include <iostream>
#include <fstream>

                /*filename of the shader*/
Shader::Shader(const std::string& fname){

    prog = glCreateProgram();

    nshaders[VERTEX] = createshader(loadshader(fname + ".vert"), GL_VERTEX_SHADER);
    nshaders[FRAGMENT] = createshader(loadshader(fname + ".frag"), GL_FRAGMENT_SHADER);

    /*adding shader to shader program*/
    for(unsigned int i = 0; i < N_SHADER; i++){
        glAttachShader(prog, nshaders[i]);
    }

    /*tells opengl which part of data to read as variable*/
    glBindAttribLocation(prog, 0, "position");

    glLinkProgram(prog);
    verifyshader(prog, GL_LINK_STATUS, true, "Error  shader failed to link");

    glValidateProgram(prog);
    verifyshader(prog, GL_VALIDATE_STATUS, true, "Error in shader failed validation");



}

Shader::~Shader(){

    std::cout << "FJFJJFFJJJJJJJJJJJJJJJ" << std::endl;
    /*removes all instances of shaders*/
    unsigned int i;
    for(i = 0; i < N_SHADER; i++){
        glDetachShader(prog, nshaders[i] );
        glDeleteShader(nshaders[i]);
    }
    glDeleteProgram(prog);

}
/*
void Shader::Update(const Transform& t, const Camera& camera)  {

    glm::mat4 mdl = camera.GetProjection() * t.MatModel();

    /*update the shader with a transform*/
  //  glUniformMatrix4fv(nuniform[TRANSFORM], 1, GL_FALSE,&mdl[0][0]);
//}

void Shader::Bind() {
    /*binds the shader to opengl*/
    glUseProgram(prog);
}

GLuint Shader::createshader(const std::string& file, GLenum type){

        GLuint shader = glCreateShader(type);

        if( shader == 0 ){
            std::cout << "Error creating shader " << std::endl;
        }
        const GLchar* shaderfile[1];
        GLint length[1];

        shaderfile[0] = file.c_str();
        length[0] = file.length();

        glShaderSource(shader, 1, shaderfile, length);
        glCompileShader(shader);

        verifyshader(shader, GL_COMPILE_STATUS,false, "COMPILE");

        return shader;
}

std::string Shader::loadshader(const std::string fname){

    std::ifstream fstr;
    std::cout << fname << std::endl;

    fstr.open((fname).c_str());
    std::string in,out;

    if( fstr.is_open() ){

        while( fstr.good() ){

            getline(fstr, in);
            out.append(in + "\n");
        }
    } else {

        std::cout << "Error while loading shader data" << std::endl;
    }
    return out;

}

void Shader::verifyshader(GLuint shader, GLuint flag, bool isprog, const std::string& error){

    GLint status = 0;
    GLchar err[1024] = {0};

    if( isprog ){
        glGetProgramiv(shader,flag,&status);
    } else{
        glGetShaderiv(shader,flag,&status);
    }
    if( status == GL_FALSE){

        if( isprog ){
            glGetProgramInfoLog(shader, sizeof(err), nullptr, err);
        } else {
            glGetShaderInfoLog(shader, sizeof(err), nullptr, err);
        }

        std::cout << "Shader  failed with : " << error << " : "<< status  << err << std::endl;
    }

}

/** REFERENCES
 * much of this code was derived from
 * https://www.khronos.org/opengl/wiki/Shader_Compilation
 *
 * The error checking portion
 * https://www.khronos.org/opengl/wiki/Example/GLSL_Shader_Compile_Error_Testing
 */

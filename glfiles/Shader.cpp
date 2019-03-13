#include "Shader.h"
#include "../err/Error.hpp"
#include <iostream>
#include <fstream>

                /*filename of the shader*/
Shader::Shader(const std::string& fname){

    /*inform opengl to create the shader program, find space, and give
     * a reference number for the program*/
    prog = glCreateProgram();
                    std::string v = loadshader((fname + ".vert"));
                    std::string f = loadshader((fname + ".frag"));
    /*load the text from the shader files, and create... load into */
    nshaders[VERTEX] = createshader(v, GL_VERTEX_SHADER);
    nshaders[FRAGMENT] = createshader(f, GL_FRAGMENT_SHADER);

    /*loop through shader buffer and attach to opengl flow*/
    unsigned int i;
    for(i = 0; i < N_SHADER; i++){
        glAttachShader( prog, nshaders[i] );
    }
    /*tells opengl what attribute to read from shaders*/
    glBindAttribLocation( prog, 0, "position" );
    glBindAttribLocation( prog, 1, "textcoord" );

    glLinkProgram(prog);
    /*verify opengl was able to read and link the shader progs*/
    verifyshader(prog, GL_LINK_STATUS,true, "LINKING");
    /*verify opengl is able to interpret shader 'no errors in the shader*/
    glValidateProgram(prog);
    verifyshader(prog, GL_VALIDATE_STATUS,true, "COMPILING");

    /*Find out the location of the handle to  uniforms, takes handler to
     * shader program, and the name of attribute in shader*/
    nuniform[TRANSFORM] = glGetUniformLocation(prog, "transform");




}

Shader::~Shader(){

    /*removes all instances of shaders*/
    unsigned int i;
    for(i = 0; i < N_SHADER; i++){
        glDetachShader( prog, nshaders[i] );
        glDeleteShader(nshaders[i]);
    }
    glDeleteProgram(prog);

}

void Shader::Update(const Transform& t, const Camera& camera)  {
    /*used to update a transforma and camera
     * this give the illusion of movement*/
    glm::mat4 mdl = camera.GetProjection() * t.MatModel();

    /*update the shader with a transform*/
    glUniformMatrix4fv(nuniform[TRANSFORM], 1, GL_FALSE,&mdl[0][0]);
}

void Shader::Bind() {
    /*binds the shader to opengl*/
    glUseProgram(prog);
}

GLuint Shader::createshader(const std::string& file, GLenum type){
        /*shaders are created during program compile time*/
        GLuint shader = glCreateShader(type);

        if( shader == 0 ){
            std::cout << "Error creating shader " << std::endl;
        }
        const GLchar* shaderfile[1];
        GLint length[1];

        shaderfile[0] = file.c_str();
        length[0] = file.length();
        /*compile the shader from the input file*/
        glShaderSource(shader, 1, shaderfile, length);
        glCompileShader(shader);
        /*verify the shader has been created*/
        verifyshader(shader, GL_COMPILE_STATUS,false, "COMPILE");

        return shader;
}
/*
 * Parses the contents of a shader file storing them into a
 * string
 */
std::string Shader::loadshader(const std::string fname){

    std::ifstream fstr;
    std::cout << fname << std::endl;
    /*standard c++ file stream operations*/
    fstr.open((fname).c_str());
    std::string in,out;

    if( fstr.is_open() ){

        while( fstr.good() ){

            getline(fstr, in);
            out.append(in + "\n");
        }
    } else {
        /*unable to open the file*/
        Error::WriteError("Error while loading shader data" );
    }
    return out;

}

void Shader::verifyshader(GLuint shader, GLuint flag, bool isprog, const std::string& error){
    /*OpenGL is a c library, so useing char[] instead of a string*/
    GLint status = 0;
    GLchar err[1024] = {0};
    /*the isprog is checking to see if the passed in shader is defined as a program for OpenGL to
     * run (shader*/
    if( isprog ){
        /*internal OpenGL functions to verify the shader*/
        glGetProgramiv(shader,flag,&status);
    } else{
        /*internal OpenGL functions to verify the shader*/
        glGetShaderiv(shader,flag,&status);
    }

    if( status == GL_FALSE){

        if( isprog ){
            /*internal OpenGL functions to verify the shader*/
            glGetProgramInfoLog(shader, sizeof(err), nullptr, err);
        } else {
            /*internal OpenGL functions to verify the shader*/
            glGetShaderInfoLog(shader, sizeof(err), nullptr, err);
        }
        /*verification or compilation failed*/
        std::cout << "Shader  failed with : " << error << " : " << err << std::endl;
    }

}

/** REFERENCES
 * much of this code was derived from
 * https://www.khronos.org/opengl/wiki/Shader_Compilation
 *
 * The error checking portion
 * https://www.khronos.org/opengl/wiki/Example/GLSL_Shader_Compile_Error_Testing
 */

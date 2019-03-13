#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H
// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*

 	Last updated by: Zachary Bower
 	Last updated on: Mar. 11, 2019

 	Purpose:
		This file creates a 3D collection of vertices, either through user defined points or through an OBJ file
		the vertex class is the representation of the vertex to OpenGL.

	Notes:
		This class uses a third party library OBJ loader
 */


#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include "ObjLoader.h"

/*temporary fix for mac compatibility*/
#ifdef __APPLE__
#undef glGenVertexArrays
#undef glBindVertexArray
#undef glDeleteVertexArrays
#define glGenVertexArrays glGenVertexArraysAPPLE
#define glBindVertexArray glBindVertexArrayAPPLE
#define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#endif

/* data class represented by vertex with
 * a x, y, z  * [1 , 2 , 3] */
class Vertex{

public:
    /*vertex representation in open gl, with position and texture*/
    Vertex(const glm::vec3& p, const glm::vec2& t){
        this->pos = p;
        this->tex = t;
    }

    glm::vec3* GetPos(){return &pos;}
    glm::vec2* GetTex(){return &tex;}


private:
    /*position*/
    glm::vec3 pos;
    /*texture*/
    glm::vec2 tex;
};



class Mesh {

public:
    /*takes a vertex array, the number of vertices (bytes), an indeces array and number of indeces (bytes)
     * an index is an optimization OpenGL offers, if two polygons share an edge only one is drawn*/
    Mesh(Vertex* vert, unsigned int nvert, unsigned int* indeces, unsigned int nindeces);
    /*constructor takes an OBJ file as input*/
    Mesh(const std::string& fname);

    ~Mesh();

    /*the actual render function, this draws the mesh*/
    void DrawMesh();

private:
    /*anonymous enum to create more human readable code
    with each element reprsenting a vertex value. Index representing
     indeces and nbuff the total number of options parsed in the OBJ file*/
    enum{
        POSITION_VB,
        TEXTURE_VB,
        INDEX,
        NBUFF
    };

    /*helper function used load the data from the OBJ object*/
    void InitMesh(const IndexedModel& model);

    /*vertex array requires at least version 3.0*/
    GLuint vertArr;
    GLuint vertArrBuf[NBUFF];

    /*tells opengl how much of the buffer want to draw
     * how many vertices to draw*/
    unsigned int ndraw;

};


#endif //ENGINE_MESH_H

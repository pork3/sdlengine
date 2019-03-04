#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H
// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 *
 *	Last updated by: Zachary Bower
 *	Last updated on: Mar 03 2019
 *
 *	Purpose:
 *		This header class is to provide base classes for managing the game.
 *
 *
 *
 *
 */
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include "../lib/ObjLoader.h"

/* data class represented by vertex with
 * a x, y, z  * [1 , 2 , 3] */
class Vertex{

public:
    Vertex(const glm::vec3& p, const glm::vec2& t, const glm::vec3& n){
        this->pos = p;
        this->tex = t;
        this->norm = n;
    }

    glm::vec3* GetPos(){return &pos;}
    glm::vec2* GetTex(){return &tex;}
    glm::vec3* GetNorm(){return &norm;}


private:
    glm::vec3 pos;
    glm::vec2 tex;
    glm::vec3 norm;
};



class Mesh {

public:
    Mesh(Vertex* vert, unsigned int nvert, unsigned int* indeces, unsigned int nindeces);
    Mesh(const std::string& fname);

    ~Mesh();

    void DrawMesh();

private:


    enum{
        POSITION_VB,
        TEXTURE_VB,
        NORMAL_VB,
        INDEX,
        NBUFF
    };

    void InitMesh(const IndexedModel& model);

    /*vertex array requires at least version 3.0*/
    GLuint vertArr;
    GLuint vertArrBuf[NBUFF];

    /*tells opengl how much of the buffer want to draw
     * how many vertices to draw*/
    unsigned int ndraw;

};


#endif //ENGINE_MESH_H

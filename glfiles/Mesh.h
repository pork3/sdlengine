#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>

/* data class represented by vertex with
 * a x, y, z  * [1 , 2 , 3] */
class Vertex{

public:
    Vertex(const glm::vec3& p, const glm::vec2& t){
        this->pos = p;
        this->tex = t;
    }

    glm::vec3* GetPos(){return &pos;}
    glm::vec2* GetTex(){return &tex;}



private:
    glm::vec3 pos;
    glm::vec2 tex;
};



class Mesh {

public:
    Mesh(Vertex* vert, unsigned int nvert);
    ~Mesh();

    void DrawMesh();

private:


    enum{
        POSITION_VB,
        TEXTURE_VB,
        NBUFF
    };

    /*vertex array requires at least version 3.0*/
    GLuint vertArr;
    GLuint vertArrBuf[NBUFF];

    /*tells opengl how much of the buffer want to draw
     * how many vertices to draw*/
    unsigned int ndraw;

};


#endif //ENGINE_MESH_H

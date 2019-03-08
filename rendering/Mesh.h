#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex{

public:

    Vertex(const glm::vec3& pos){
        this->pos = pos;
    };

    glm::vec3 GetPos(){ return this->pos; }

private:
    glm::vec3 pos;


};

class Mesh {

public:
    Mesh(Vertex* vert, unsigned int nvert);
    ~Mesh();

    void Draw();

private:

    enum{
        POSVERT,
        NBUFF
    };


    GLuint vertexarray;
    GLuint vertexarraybufer[NBUFF];

    /*keep track of how much want to draw*/
    unsigned int todraw;
};


#endif //ENGINE_MESH_H

#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex{

public:

    Vertex(const glm::vec3& pos, const glm::vec2& texture){
        this->pos = pos;
        this->text = texture;
    };

    glm::vec3* GetPos(){ return &pos; }
    glm::vec2* GetTexture(){return &text;}

private:
    glm::vec3 pos;
    glm::vec2 text;


};

class Mesh {

public:
    Mesh(Vertex* vert, unsigned int nvert);
    ~Mesh();

    void Draw();

private:

    enum{
        POSVERT,
        TEXTCOORD,
        NBUFF
    };


    GLuint vertexarray;
    GLuint vertexarraybufer[NBUFF];

    /*keep track of how much want to draw*/
    unsigned int todraw;
};


#endif //ENGINE_MESH_H

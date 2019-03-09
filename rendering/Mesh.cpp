#include "Mesh.h"
#include <iostream>
#include <vector>

Mesh::~Mesh() {
    glDeleteVertexArrays(1,&vertexarray);

}

void Mesh::Draw() {

    glBindVertexArray(vertexarray);
                /*draw mode, where to start, how much to read */
    glDrawArrays(GL_TRIANGLES,0, todraw);

    glBindVertexArray(0);
}

Mesh::Mesh(Vertex *vert, unsigned int nvert) {

    this->todraw = nvert;

    glGenVertexArrays(1, &vertexarray);
    /*bind the vertext array to begin drawing*/
    glBindVertexArray(vertexarray);


    std::vector<glm::vec3>positions;
    std::vector<glm::vec2>texturecoordinates;
    positions.reserve(nvert);
    texturecoordinates.reserve(nvert);

    for(unsigned int i = 0; i < nvert; i++){

        positions.push_back(*vert[i].GetPos());
        texturecoordinates.push_back(*vert[i].GetTexture());
    }

    glGenBuffers(NBUFF, vertexarraybufer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexarraybufer[POSVERT]);
    glBufferData( GL_ARRAY_BUFFER, nvert* sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, 0, nullptr);


    glBindBuffer(GL_ARRAY_BUFFER,vertexarraybufer[TEXTCOORD]);
    glBufferData( GL_ARRAY_BUFFER, nvert* sizeof(texturecoordinates[0]), &texturecoordinates[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT, GL_FALSE, 0, nullptr);


    glBindVertexArray(0);



}

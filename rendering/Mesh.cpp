#include "Mesh.h"
#include <iostream>

Mesh::~Mesh() {
    std::cout << "$$$$$$$$$$$$$" << std::endl;
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

    /*generate the buffers*/
    /*gives blocks of data on gpu*/
    glGenBuffers(NBUFF, vertexarraybufer);
    /*interpret bufer as an array*/
    glBindBuffer(GL_ARRAY_BUFFER, vertexarraybufer[POSVERT]);

    /*put data into the array*/
    /*moving from ram to gpu memory put all vertex data in    draw hint  static means it shouldnt be changed where to store data*/
    glBufferData( GL_ARRAY_BUFFER, nvert* sizeof(vert[0]), vert, GL_STATIC_DRAW);

    /*how to interpret data, divides data into attributes
     * all pieces*/
    /*gpu needs to look as a sequential array of data*/
    /*this is based on shader*/
    glEnableVertexAttribArray(0);

    /*how to look at the data, what it needs to do*/
    /*which part, how much data, type, normalize?, data to skip, how much to find next*/
    glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, 0, 0);


    glBindVertexArray(0);
}

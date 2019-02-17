#include "Mesh.h"
#include <vector>

Mesh::Mesh(Vertex* vert, unsigned int nvert) {

    ndraw = nvert;
    /*have opengl do the back end vertex buffer setup*/
    glGenVertexArrays(1, &vertArr);
    /*bind the objects with opengl... this ties the calls to draw/update to the
     * object passed in*/
    glBindVertexArray(vertArr);

    /*create vectors for the position coordinates and texture coordinates*/
    std::vector<glm::vec3> poscoord;
    std::vector<glm::vec2> texcoord;
    /*reserve the ammount of data needed*/
    poscoord.reserve(nvert);
    texcoord.reserve(nvert);
    int i;
    for( i = 0; i < nvert; i++){

        poscoord.push_back(*vert[i].GetPos());
        texcoord.push_back(*vert[i].GetTex());
    }

    /**POSITION DATA**/
    /*sets up space on graphics card and binds the space and sets opengl
     * interpretation of data as an array/buffer*/
    glGenBuffers(NBUFF, vertArrBuf);
    glBindBuffer(GL_ARRAY_BUFFER,vertArrBuf[POSITION_VB]);
    /*moving the data from ram to gpu*/
                /*interp as array, size of data to move, addr, glhints */
    glBufferData(GL_ARRAY_BUFFER, nvert*sizeof(poscoord[0]), &poscoord[0], GL_STATIC_DRAW );
    /*tell opengl how to interpret the data*/
        /*passes the attributes of the data, the order they should be read this ensures
        the data is read into the gpu in a sequential fashion*/
    glEnableVertexAttribArray(0);
                            /*3 pieces of float data*/
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindVertexArray(0);

    /** TEXTURE DATA ****/
    glGenBuffers(NBUFF, vertArrBuf);
    glBindBuffer(GL_ARRAY_BUFFER,vertArrBuf[TEXTURE_VB]);
    glBufferData(GL_ARRAY_BUFFER, nvert*sizeof(texcoord[0]), &texcoord[0], GL_STATIC_DRAW );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindVertexArray(1);

}

Mesh::~Mesh() {

    glDeleteVertexArrays(1, &vertArr);
}

void Mesh::DrawMesh() {
    /*bind*/
    glBindVertexArray(vertArr);

    glDrawArrays(GL_TRIANGLES, 0, this->ndraw);

    /*unbind*/
    glBindVertexArray(0);

}
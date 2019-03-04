#include "Mesh.h"
#include <vector>


Mesh::Mesh(const std::string& fname){
    /*loads mesh from file*/
    IndexedModel model = OBJModel(fname).ToIndexedModel();
    InitMesh(model);
}

Mesh::Mesh(Vertex* vert, unsigned int nvert,unsigned int* indeces, unsigned int nindeces) {

    IndexedModel model;

    unsigned  int i;
    for(i=0; i < nvert; i++){

        model.positions.push_back(*vert[i].GetPos());
        model.texCoords.push_back(*vert[i].GetTex());
        model.normals.push_back(*vert[i].GetNorm());
    }

    for( i = 0; i < nindeces; i++){
        model.indices.push_back(indeces[i]);
    }

    InitMesh(model);
}

void Mesh::InitMesh(const IndexedModel &model) {

    ndraw = model.indices.size();

    glGenVertexArrays(1, &vertArr);
    /*bind the objects with opengl... this ties the calls to draw/update to the
     * object passed in*/
    glBindVertexArray(vertArr);

    /**POSITION DATA**/
    /*sets up space on graphics card and binds the space and sets opengl
     * interpretation of data as an array/buffer*/
    glGenBuffers(NBUFF, vertArrBuf);
    glBindBuffer(GL_ARRAY_BUFFER,vertArrBuf[POSITION_VB]);
    /*moving the data from ram to gpu*/
    /*interp as array, size of data to move, addr, glhints */
    glBufferData(GL_ARRAY_BUFFER, model.positions.size()*sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW );
    /*tell opengl how to interpret the data*/
    /*passes the attributes of the data, the order they should be read this ensures
    the data is read into the gpu in a sequential fashion*/
    glEnableVertexAttribArray(0);
    /*3 pieces of float data*/
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0, nullptr);



    /** TEXTURE DATA ****/
    glGenBuffers(NBUFF, vertArrBuf);
    glBindBuffer(GL_ARRAY_BUFFER,vertArrBuf[TEXTURE_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size()*sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW );
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT, GL_FALSE, 0, nullptr);


    /** INDEX BUFFER DATA BEGINS **/
    /*array of access to other elements array*/
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vertArrBuf[INDEX]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW );


    /**NORMAL DATA BEGINS HERE**/
    glBindBuffer(GL_ARRAY_BUFFER,vertArrBuf[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.normals.size()*sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW );
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(1,2,GL_FLOAT, GL_FALSE, 0, nullptr);

    /*unbind, free*/
    glBindVertexArray(0);
}

Mesh::~Mesh() {

    glDeleteVertexArrays(1, &vertArr);
}

void Mesh::DrawMesh() {
    /*bind*/
    glBindVertexArray(vertArr);

    glDrawElements(GL_TRIANGLES, this->ndraw, GL_UNSIGNED_INT, 0 );
    //glDrawArrays(GL_TRIANGLES, 0, this->ndraw);

    /*unbind*/
    glBindVertexArray(0);

}
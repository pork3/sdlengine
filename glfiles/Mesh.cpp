#include "Mesh.h"
#include "../err/Error.hpp"
#include <vector>
#include <iostream>

extern int IGNORE_OPENGL_VERSION = 0;

Mesh::Mesh(const std::string& fname){
    /*loads mesh from file*/
    IndexedModel model = OBJModel(fname).ToIndexedModel();
    InitMesh(model);
}

Mesh::Mesh(Vertex* vert, unsigned int nvert,unsigned int* indeces, unsigned int nindeces) {

    IndexedModel model;

    /*the data from the vertices must be given to OpenGL in a specific manner. This creates arrays that go together
     * or the indeces inside the arrays match.
     * when OpenGL draws the data, it needs to draw it in this manner : pos1  pos2 pos3 text1 text2  , this sets up the arrays
        in that order*/
    unsigned  int i;
    for(i=0; i < nvert; i++){

        model.positions.push_back(*vert[i].GetPos());
        model.texCoords.push_back(*vert[i].GetTex());
    }
    /*now add the indeces*/
    for( i = 0; i < nindeces; i++){
        model.indices.push_back(indeces[i]);
    }
    /*and crate the model*/
    InitMesh(model);
}

void Mesh::InitMesh(const IndexedModel &model) {

    ndraw = model.indices.size();

    /*to allow for cross platfrom compatibility*/
	if(!GLEW_VERSION_3_0 && !GLEW_ARB_vertex_array_object && IGNORE_OPENGL_VERSION == 0){
		// Should be logged, however for the time being it will be printed to std err
		Error::WriteError("Potential Crash Warning: OpenGL version verification error, outdated OpenGL detected. Problems may occur");
		Error::WriteError("due to using future/experimental OpenGL functions. Expected error for crash, segfault 11.");
		Error::WriteError("To disable this warning, set the external int IGNORE_OPENGL_VERSION to 1 in your main.");
		std::cerr << "Potential Crash Warning: OpenGL version verification error, outdated OpenGL detected. Problems may occur" << std::endl;
		std::cerr<< " due to using future/experimental OpenGL functions. Expected error for crash, segfault 11."<<std::endl;
		std::cerr<< "	To disable this warning, set the external int IGNORE_OPENGL_VERSION to 1 in your main." << std::endl;
	}
	
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


    /*binding the data in a similar manner as the position data, but when the data is passed set 2 points and index 1
     * in the OpenGL function vertexattribpointer*/
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


    /*unbind, free*/
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    /*free all allocated memory*/
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
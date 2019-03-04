#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#define GLIBCXX_USE_CXX11_ABI 0
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h> 
#include <GL/glx.h>
#include <GL/glext.h>


// These two are for the obj file has "vt"(texture) and "vn"(normal)
// credit: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
// instruction of obj file; http://paulbourke.net/dataformats/obj/minobj.html


int main() {
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;

    bool loadOBJ(
    const char * path,
    std::vector < glm::vec3 > & out_vertices,
    std::vector < glm::vec2 > & out_uvs,
    std::vector < glm::vec3 > & out_normals
);

    // read the file
    FILE * file = fopen("VtVnCube.obj","r");
    if (file==NULL) {
        printf("Impossible to open the file!\n");
        return false;
    }
    // read line by line, and put into temp_vertices
    while (1) {
        char lineHeader[128];
        // read the first word. It's the flag of each line
        // "flag" indicate the function of the line
        int res = fscanf(file, "%s", lineHeader);
        // error handler
        if (res==EOF)
            break;

        // reading the actual data
        /*
        If the first word of the line is “v”, then the rest has to be 3 floats, 
        so create a glm::vec3 out of them, and add it to the vector.
        */
        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file,"%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader,"vt") == 0) {
            glm::vec2 uv;
            fscanf(file,"%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        }
        else if (strcmp( lineHeader, "vn" ) == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }
        else if (strcmp( lineHeader, "f" ) == 0) {
            std::string vertex1,vertex2,vetex3;
            unsigned int vertexIndex[3],uvIndex[3],normalIndex[3];
            int matches = fscanf(file,"%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            
            if (matches != 9) {
                printf ("File cannot beread by our simple parser\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    } // end of loading all the vertex, normal and texture library
    std::vector< glm::vec3 > out_vertices;
    std::vector< glm::vec2 > out_uvs;
    std::vector< glm::vec3 > out_normals;
    for (unsigned int i=0; i<vertexIndices.size();i++) {
        unsigned int real_vertexIndex = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[real_vertexIndex-1]; // because the index in "f" start from 1 not 0
        out_vertices.push_back(vertex);
        unsigned int real_uvIndex = uvIndices[i];
        glm::vec2 uv = temp_uvs[real_uvIndex-1];
        out_uvs.push_back(uv);
        unsigned int real_normalIndex = normalIndices[i];
        glm::vec3 normal = temp_normals[real_normalIndex-1];
        out_normals.push_back(normal);
    }
    /*
    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals; // Won't be used at the moment.
    //bool res = loadOBJ("cube.obj", vertices, uvs, normals);
    //glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    */
    glBegin(GL_TRIANGLES);
    for (unsigned int j=0; j<out_vertices.size();j++) {
        glVertex3f(out_vertices[j][0],out_vertices[j][1],out_vertices[j][2]);
    }
    glEnd();

}
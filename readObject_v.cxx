#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <GL/gl.h>

using namespace std;

// These two are for the obj file has "vt"(texture) and "vn"(normal)
// credit: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
// instruction of obj file; http://paulbourke.net/dataformats/obj/minobj.html


int main() {
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< GLdouble* > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;

    // read the file
    FILE * file = fopen("tinker.obj","r");
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
            GLdouble *vertex = new GLdouble [3];
            float *origin_vertex = new float [3];
            fscanf(file,"%f %f %f\n", &origin_vertex[0], &origin_vertex[1], &origin_vertex[2] );
            for (int i=0;i<3;i++) {
                vertex[i] = (double)origin_vertex[i];
            }
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

        // read the triangle data and draw it.
        else if (strcmp( lineHeader, "f" ) == 0) {
            unsigned int vertexIndex[3];
            fscanf(file,"%d %d %d\n", &vertexIndex[0],&vertexIndex[1],&vertexIndex[2]);
            glBegin(GL_TRIANGLES);
            glVertex3dv(temp_vertices[vertexIndex[0]]);
            glVertex3dv(temp_vertices[vertexIndex[1]]);
            glVertex3dv(temp_vertices[vertexIndex[2]]);
            glEnd();
        }
    }

}
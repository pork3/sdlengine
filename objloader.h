#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <GL/gl.h>


bool loadOBJ(
    const char * path,
    std::vector < glm::vec3 > & out_vertices,
    std::vector < glm::vec2 > & out_uvs,
    std::vector < glm::vec3 > & out_normals
)
#ifndef ENGINE_TEXTURES_H
#define ENGINE_TEXTURES_H

#include <string>
#include <GL/glew.h>

class Textures {

public:

    Textures(const std::string&fname);

    ~Textures();

    void Bind(unsigned int textnum);

private:

    GLuint texturehandle;

};


#endif //ENGINE_TEXTURES_H

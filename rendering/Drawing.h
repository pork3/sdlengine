//
// Created by zach on 3/8/19.
//

#ifndef ENGINE_DRAWING_H
#define ENGINE_DRAWING_H

#include "Window.hpp"
#include <SDL2/SDL.h>
#include <GL/glew.h>

class Drawing {

    /*drawing enum*/
   enum DrawType{

       TRIANGLE = GL_TRIANGLES,
       POINTS = GL_POINTS,
       LINE_STRIP = GL_LINE_STRIP,
       LINE_LOOP = GL_LINE_LOOP,
       LINES = GL_LINES,
       TRIANGLE_FAN = GL_TRIANGLE_FAN,
   };

   /*Set up culling 'hiding of back faces'*/
   enum CullingType{

       NONE = GL_NEVER,
       ALWAYS = GL_ALWAYS,
       LESS = GL_LESS,
       GREATER = GL_GREATER,


   };

public:

    Drawing(Window& window);





};


#endif //ENGINE_DRAWING_H

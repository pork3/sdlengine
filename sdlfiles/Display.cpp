//
// Created by zach on 2/15/19.
//

#include "Display.h"
#include <iostream>
#include <GL/glew.h>

Display::Display(std::string title, int w, int h){

    set_attr();
    this->window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            w,h, SDL_WINDOW_OPENGL );

        if( window == nullptr){
            std::cout << "Error creating window" << std::endl;
        }
        /*creates an openglcontext ... this allows open gl to have more control
         * over the graphics hardware*/
        this->glcontext = SDL_GL_CreateContext(this->window);

        /*set up open Glbackend*/
        GLenum glok = glewInit();
        if( glok != GLEW_OK){
            std::cout << "Failed to initialized openGL :(" << std::endl;
        }

        glClearColor(1.0f,1.0f,1.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SwapDisp();
}

void Display::set_attr(){

    /*explicitly request open gl for at least 2^8 bits of data for
     * red,green,blue and alpha data*/
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    /*request at least a buffer size of 8*4 for the above data*/
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    /*use double bufffer if available, with double buffer drawing a 'staging'
     * window and swapping what the user sees*/
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

}

void Display::SwapDisp(){

    SDL_GL_SwapWindow(this->window);
}


Display::~Display(){

    SDL_GL_DeleteContext(this->glcontext);
    SDL_DestroyWindow(this->window);

}

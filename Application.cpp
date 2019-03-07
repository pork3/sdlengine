//
// Created by zach on 3/5/19.
//
#include <iostream>
#include <SDL2/SDL.h>
#include "Application.h"


Application::Application() : running(true) {

    SDL_Init(SDL_INIT_EVERYTHING);
    if( SDL_INIT_VIDEO < 0 ) {
        std::cout << "Error creating video " << SDL_GetError() << std::endl;
    }

}

Application::~Application() {

    SDL_Quit();
}

void Application::Process(InputHandler &ih) {

    SDL_Event e;

    while( SDL_PollEvent(&e) ){
        switch(e.type){
            case SDL_KEYDOWN:
                ih.OnKeyDown(e.key.keysym.scancode, e.key.repeat != 0);
                break;
            case SDL_KEYUP:
                ih.OnKeyUp(e.key.keysym.scancode, e.key.repeat != 0);
                break;
            case SDL_MOUSEMOTION:
                ih.OnMouseMotion(e.motion.x , e.motion.y, e.motion.xrel, e.motion.yrel);
                break;
            case SDL_MOUSEBUTTONDOWN:
                ih.OnMouseDown(e.button.button, e.button.clicks);
                break;
            case SDL_MOUSEBUTTONUP:
                ih.OnMouseUp(e.button.button, e.button.clicks);
                break;
            case SDL_QUIT:
                this->running = false;
                break;
            default:
                break;

        }
    }
}

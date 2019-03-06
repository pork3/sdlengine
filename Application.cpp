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
                break;
            case SDL_KEYUP:
                break;
            case SDL_MOUSEMOTION:
                break;
            case SDL_MOUSEBUTTONDOWN:
                break;
            case SDL_MOUSEBUTTONUP:
                break;
            case SDL_QUIT:
                this->running = false;
                break;
            default:
                break;

        }
    }
}


#include <iostream>
#include "RenderedApplication.hpp"
#include "../error/ErrorLog.hpp"

RenderedApplication *RenderedApplication::CreateApplication() {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        ErrorLog::WriteError("Error Initializing SDL");
        return nullptr;
    }
    return new RenderedApplication();

}

RenderedApplication::~RenderedApplication(){

    /*maybe allow for multiple instances*/
    SDL_QUIT;
}

bool RenderedApplication::IsRunning() {

    return this->running;
}

RenderedApplication::RenderedApplication() {

    this->running = true;
}
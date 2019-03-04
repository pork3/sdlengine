//
// Created by zach on 3/3/19.
//

#include "InputEvent.h"

InputEvent::InputEvent() {

}


void InputEvent::ProcessInput(double d) {

    while( SDL_PollEvent( this->event ) ){
            switch(this->event->type){

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
                    break;
                default:
                    break;

            }
    }
}


//
// Created by zach on 2/16/19.
//

#include "Event.h"

Event::Event(){
    evnt = new SDL_Event;
}

Event::~Event(){
    delete evnt;
}
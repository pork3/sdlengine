#ifndef ENGINE_INPUTEVENT_H
#define ENGINE_INPUTEVENT_H
// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 *
 *	Last updated by: Zachary Bower
 *	Last updated on: Mar 03 2019
 *
 *	Purpose:
 *		This header class is to provide base classes for managing the game.
 *
 *
 *
 *
 */

#include <SDL2/SDL.h>
#include "InputHandler.hpp"
#include "Listeners.hpp"

class InputEvent : virtual public Listener::GameTickListener {

public:
    InputEvent();

    void ProcessInput(double d);


private:
    SDL_Event* event;


};


#endif //ENGINE_INPUTEVENT_H

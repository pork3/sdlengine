#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H
// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 *
 *	Last updated by: Zachary Bower
 *	Last updated on: Mar 2, 2019
 *
 *	Purpose:
 *		This class is the main entry point for an application. The application will initialize SDL
 *		communicating between an application and the engine
 *
 *  This file creates a window for the user, the main interface between the game and
 *  the end user of the game
 */
#include "./events/InputHandler.hpp"

class Application {

public:
    Application();
    ~Application();

    bool IsRunning(){ return this->running ;}

    void Process(InputHandler& ih );

private:
    bool running;



};


#endif //ENGINE_APPLICATION_H
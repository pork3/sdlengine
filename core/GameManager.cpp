// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 
 	Last updated by: Chase Craig
 	Last updated on: Mar. 11, 2019
 
 	Purpose:
        This header file is to outline the functions available for controlling the logic for handling the
			game engine. This serves as the main controller interface for managing the game state, as well as
			running the main game loop and dispatching rendering and logic events.
   
	Notes:
		See GameManager.h for usage of this object.
 */

// Required Headers
#include "GameManager.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <GL/glew.h>
#include <chrono>

// Headers referencing the rest of the project
#include "../glfiles/Textures.h"
#include "../glfiles/Shader.h"
#include "../Transform.h"
#include "../Camera.h"
#include "../events/EventDispatcher.hpp"
#include "../math/EngineMath.hpp"

// Although bad practice, include the entire Engine namespace.
using namespace Engine;

// Constructor implementation, sets the starting and last tick time points
// NOTE: Can exit due to failure to initialize the back end rendering.
Engine::GameManager::GameManager() : startingTime(std::chrono::high_resolution_clock::now()), lastTick(std::chrono::high_resolution_clock::now()){
    options = new Management::GameOptions(60); // Initializes the game loop too tick at 60 ticks per second
    initback(); // Initialize the backend
}

// Deconstructor
Engine::GameManager::~GameManager(){

    delete this->display;
    SDL_Quit(); // Forces SDL to close the windows.
}

// Initialize the backend
void Engine::GameManager::initback(){

    // Initialize SDL with everything (as per protocol from their website).
    SDL_Init(SDL_INIT_EVERYTHING);
	if( SDL_INIT_VIDEO < 0 ) {
		std::cout << "Error creating video " << SDL_GetError() << std::endl;
		throw SDL_GetError();
		// Exit due to error.
	}

}

// Creates a window
void Engine::GameManager::CreateWindow(std::string title, int w, int h){
	// If the width and height are 0, set width/height to their defaults.
    (w == 0) ?w=800: w;
    (h == 0) ?h=600: h;
	// Create a new display object
    this->display = new Display(this, title,w,h);
	// Start with the display hidden.
    this->display->HideWindow();
}


// The main logic loop, this function will not return until the game ends. 
void Engine::GameManager::Run(){
	// A SDL_Event, for capturing key, mouse, and other window/peripheral events.
    SDL_Event e;
    
    while(this->gameRunning){ 
        // Grab the event dispatcher object
        Events::EventDispatcher* ed = Events::EventDispatcher::instance();
		
		// Get the current time_point object (for starting tick time)
        std::chrono::high_resolution_clock::time_point startTickTime = high_resolution_clock::now();

        if (this->gamePaused) {
			// If the game isn't paused, check to see if the time between the last tick time and now 
			// 		is longer than the required time (in milliseconds) to achieve a specific rate.
            auto tickDelta = Engine::Utilities::instance()->getMillisFrom(&this->lastTick, &startTickTime);
            if (tickDelta >= Engine::Utilities::instance()->getMillisWaitTime(this->options->getTickRateTarget())) {
				// Create a new tick event detail, it is not cancellable.
                Events::TimedEventDetails eventD(this, "Tick", 3, false, startTickTime, this->startingTime, tickDelta,
                                                 tickDelta);
				// Call the event dispatcher and notify tick event listeners
                ed->ExecuteTickEvent(&eventD);
				// Update the last tick to now.
                this->lastTick = high_resolution_clock::now();
            }
        } else {
            // If the game is paused, the last tick is always now.
            this->lastTick = high_resolution_clock::now();
        }

        // Get the next SDL event
        int isEvent = SDL_PollEvent(&e);
		// Get the current time_point object
		std::chrono::high_resolution_clock::time_point startSDLTime = high_resolution_clock::now();
		// If isEvent is 0, then no event was captured, otherwise e contains a new event.
		if(isEvent) {
            switch (e.type) { // Switch the type of the event.
                case SDL_KEYDOWN: {
					// A key was pressed down (could be repeated)
					// This event is cancellable
                    Events::KeyboardEventDetails eventD(this, "KeyDown", 4, true, startSDLTime, this->startingTime,
                                                        e.key.keysym.sym,
                                                        e.key.repeat, SDL_GetModState());
					// Call the event dispatcher and notify Key Down event listeners
                    ed->ExecuteKeyEvent(&eventD);
                    break;
                }
                case SDL_KEYUP: {
					// A key was released
					// This event is cancellable
                    Events::KeyboardEventDetails eventD(this, "KeyDown", 5, true, startSDLTime, this->startingTime,
                                                        e.key.keysym.sym,
                                                        e.key.repeat, SDL_GetModState());
					// Call the event dispatcher and notify key up event listeners
                    ed->ExecuteKeyEvent(&eventD);
                    break;
                }
                case SDL_MOUSEMOTION: {
					// The mouse pointer has moved on the display
					// This event is cancellable
                    Events::MouseButtonEventDetails eventD(this, "MouseMove", 8, true, startSDLTime, this->startingTime,
                                                           SDL_GetMouseState(NULL,NULL),
                                                           Math::Vector2Int(static_cast<int>(e.motion.x),
                                                                            static_cast<int>(e.motion.y)),
                                                           Math::Vector2Int(static_cast<int>(e.motion.xrel),
                                                                            static_cast<int>(e.motion.yrel)), 0,
                                                           SDL_GetModState());
					// Calls the event dispatcher and notify mouse motion event listeners
                    ed->ExecuteMouseEvent(&eventD);

                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
					// The mouse has pressed a button
					// The event is cancellable
                    Events::MouseButtonEventDetails eventD(this, "MouseDown", 6, true, startSDLTime, this->startingTime,
                                                           e.button.state,
                                                           Math::Vector2Int(static_cast<int>(e.button.x),
                                                                            static_cast<int>(e.button.y)),
                                                           Math::Vector2Int(0, 0), e.button.clicks, SDL_GetModState());
					// Calls the event dispatcher and notify mouse pressed event listeners
                    ed->ExecuteMouseEvent(&eventD);

                    break;
                }
                case SDL_MOUSEBUTTONUP: {
					// The mouse has released a button
					// The event is cancellable
                    Events::MouseButtonEventDetails eventD(this, "MouseUp", 7, true, startSDLTime, this->startingTime,
                                                           e.button.state,
                                                           Math::Vector2Int(static_cast<int>(e.button.x),
                                                                            static_cast<int>(e.button.y)),
                                                           Math::Vector2Int(0, 0), e.button.clicks, SDL_GetModState());
					// Calls the event dispatcher and notify mouse released event listeners
                    ed->ExecuteMouseEvent(&eventD);
                    break;
                }
                case SDL_QUIT: {
					// Technically it calls event listeners for game stopping, but it defers this behavior
					// 		to the implementation in the stop game function.
                    this->StopGame(false);
                    break;
                }
                default:
                    break;
            }
        }

		// Handles refreshing the window. Start by getting the current time point
        high_resolution_clock::time_point startFrameTime = high_resolution_clock::now();
        auto vpntr = this->display; // Get a pointer to the display object.
        if(!((vpntr)->isShown)) {  
			// If the frame is not displaying, the last frame was "now". (Listeners are not called).
            (vpntr)->lastFrame = high_resolution_clock::now();
        }else {
			// Determine the amount of time in milliseconds that have passed since the last frame "tick".
            auto frameDelta = Engine::Utilities::instance()->getMillisFrom(&((vpntr)->lastFrame),
                                                                           &startFrameTime);
            if ((vpntr)->isDirty || frameDelta >= Engine::Utilities::instance()->getMillisWaitTime((vpntr)->windOpts->getFrameRateTarget())){
				// If the frame is dirty (and hence is requested to be redrawn), or enough time has passed
				//		redraw the frame after requesting all renderers to re-draw.
                
                // Call the frame listeners registered to this window, may include world renderers
                Events::WindowEventDetails eventD(this, "Frame", 2, false, startFrameTime, this->startingTime, frameDelta, frameDelta, vpntr);
                (vpntr)->ExecuteGUIEvent(&eventD);
                (vpntr)->SwapDisp();

                (vpntr)->lastFrame = high_resolution_clock::now();
            }
        }
    }
}

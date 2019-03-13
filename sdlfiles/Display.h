#ifndef ENGINE_DISPLAY_H
#define ENGINE_DISPLAY_H

// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*

 	Last updated by: Zachary Bower
 	Last updated on: Mar. 11, 2019

 	Purpose:
		This file creates a SDL2 window to display to the third party user. The file handles the creation of
		an OpenGL context (a communication point between the program and the graphics hardware). OpenGL options
		are set, including buffer sizes, and double buffering. Double buffering avoids artifacts on the screen, by
		drawing a screen the user cannot see then swapping them

	Notes:
		See Transform.h for usage of this object.
 */

/*
	Citation: Due to a bug where apple products could not run, we are attempting the 
		below to give the user a last chance to run our code.
*/
#ifdef __APPLE__
#undef glGenVertexArrays
#undef glBindVertexArray
#undef glDeleteVertexArrays
#define glGenVertexArrays glGenVertexArraysAPPLE
#define glBindVertexArray glBindVertexArrayAPPLE
#define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#endif

#include <string>
#include <SDL2/SDL.h>
#include "../events/Listeners.hpp"
#include "../utils/GameOptions.hpp"
#include <map>
#include <unordered_set>
namespace Engine{
    class GameManager;
}
class Display {

public:
    /*constructor to bind a game manager, title width and height*/
    Display(Engine::GameManager* g, std::string title, int w, int h);
    ~Display();

    /*function used to swap between the double buffers*/
    void SwapDisp();
    /*function to clear the screen and redraw to red green blue alpha*/
    void Clear(float r, float g, float b, float a);

    float GetHeightf(){return static_cast<float>(this->sheight);}
    float GetWidthf(){return static_cast<float>(this->swithd);}
    /*
        Function used to make the frame as "dirty" and hence needs to be redrawn.
        This is automatically called if the window has a non-negative frame rate.
        If the window has a negative frame rate, it only refreshes (redraws) the window
            if this function is called. This function will be called if an interaction
            (such as left-clicking on the window) happens.
    */
    void markDirty(){this->isDirty = true;};

    /*
        Function that shows the window to the user.
     */
    void ShowWindow();

    /*
        Function that hides the window from the user (does not destroy it).
     */
    void HideWindow();

    /*
        Registers a window listener to receive window events (render and window changed).
     */
    void RegisterWindowListener(Listener::GameGUIListener* list, Events::Priority p);

    /*
        Unregisters a window listener, unsubscribing it from receiving window events.
     */
    void UnregisterWindowListener(Listener::GameGUIListener* list);

    /*Events relating to the Display*/
    void ExecuteGUIEvent(Events::WindowEventDetails* details);
    /*window options*/
    Management::WindowOptions* GetWindowOptions(){return this->windOpts;}
    std::map<Events::Priority, std::unordered_set<Listener::GameGUIListener*>* > gameGUIListeners{};
    bool isShown;
    /*frame rate timer*/
    high_resolution_clock::time_point lastFrame;
    high_resolution_clock::time_point startingTime;
    bool isDirty;
     Management::WindowOptions* windOpts;

private:

    int swithd;
    int sheight;
    std::string title;
    Engine::GameManager* game;

    /*function used to set OpenGl attributes when creating window*/
    void set_attr();
    /*SDL pointers */
    SDL_Window* window;
    SDL_GLContext glcontext;


};


#endif //ENGINE_DISPLAY_H

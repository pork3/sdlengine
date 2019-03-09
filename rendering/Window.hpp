#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H
// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 *
 *	Last updated by: Chase Craig
 *	Last updated on: Mar 7, 2019
 *
 *	Purpose:
 *		This class provides interaction for creating a display window
 *      The class takes a string width and height uses this information to create a window
 *  Update 2/29:
 *      Added ability to fullscreen window
 *      Added aspect ratio support
 *  Update 3/2
 *      Renamed ambiguous function names to be more specific
 *  Update 3/7
 *      Added window options (settings) and added a mark dirty function.
 *      Modified comments.
 *
 */

#include <string>
#include <SDL2/SDL.h>
#include "../utils/GameOptions.hpp"
#include "../events/Listeners.hpp"
#include <map>
#include <unordered_set>
#include <chrono>

namespace Engine{
    class GameManager;
}

class Window {

public:
    friend class Engine::GameManager;
    Window(std::string title, int w, int h);
    ~Window();

    /*
        Used to update the double buffer
    */
    void Update();

    /*
        Function used to clear the screen... takes a red, green, blue and alpha
            value, sets the screen color to value passed in

        This function will mark the window as dirty.
    */
    void Clear(float r, float g, float b, float a);

    /*
        Function used to set fullscreen or to remove fullscreen
    */
    void SetFullscreen();

    /*
        Function used to set up opengl preferences
    */
    void set_attr();

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



    /** GETTERS**/
    float GetAspectRatio();
    SDL_Window* GetWindow(){return this->window ;}
    SDL_GLContext*  GetContext() {return &(this->glcontext);}
    int GetHeight() {return this->sheight; }
    int GetWidth() {return this->swidth; }
    Management::WindowOptions* GetWindowOptions(){return this->windOpts;}


    /**SETTERS**/
    void SetHeight(int h){this->sheight = h; }
    void SetWidth(int w){this->swidth = w; }
    void SetTitle(std::string s){this->title = s; }
protected:

    void ExecuteGUIEvent(Events::WindowEventDetails* details);

    std::map<Events::Priority, std::unordered_set<Listener::GameGUIListener*>* > gameGUIListeners{};
    bool isDirty;
    bool isShown;
    high_resolution_clock::time_point lastFrame;
    high_resolution_clock::time_point startingTime;
    Management::WindowOptions* windOpts;
private:

    SDL_GLContext  glcontext;
    SDL_Window* window;
    int swidth;
    int sheight;
    std::string title;
    bool isfullscreen;

    /*handle sdlquit event with a close request from event manager*/
    bool closerequested;

};


#endif //ENGINE_WINDOW_H

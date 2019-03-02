#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H
// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 *
 *	Last updated by: Zachary Bower
 *	Last updated on: Mar 2, 2019
 *
 *	Purpose:
 *		This class provides interaction for creating a display window
 *      The class takes a string width and height uses this information to create a window
 *  Update 2/29:
 *      Added ability to fullscreen window
 *      Added aspect ratio support
 *  Update 3/2
 *      Renamed ambiguous function names to be more specific
 *
 *  This file creates a window for the user, the main interface between the game and
 *  the end user of the game
 */

#include <string>
#include <SDL2/SDL.h>

class Window {

public:
    Window(std::string title, int w, int h);
    ~Window();

    /*used to update the double buffer*/
    void Update();
    /*function used to clear the screen... takes a red, green, blue and alpha
     * value, sets the screen color to value passed in*/
    void Clear(float r, float g, float b, float a);

    /*function used to set fullscreen or to remove fullscreen*/
    void SetFullscreen();

    /** GETTERS**/
    float GetAspectRatio();
    SDL_Window* GetWindow(){return this->window ;}
    int GetHeight() {return this->sheight; }
    int GetWidth() {return this->swidth; }

    /**SETTERS**/
    void SetHeight(int h){this->sheight = h; }
    void SetWidth(int w){this->swidth = w; }
    void SetTitle(std::string s){this->title = s; }

private:

    SDL_GLContext  glcontext;
    SDL_Window* window;
    int swidth;
    int sheight;
    std::string title;
    bool isfullscreen;

};


#endif //ENGINE_WINDOW_H

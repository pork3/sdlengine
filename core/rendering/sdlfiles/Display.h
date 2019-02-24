#ifndef ENGINE_DISPLAY_H
#define ENGINE_DISPLAY_H
// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 *
 *	Last updated by: Zachary Bower
 *	Last updated on: Feb. 23, 2019
 *
 *	Purpose:
 *		This class provides interaction for creating a display window
 *      The class takes a string width and height uses this information to create a window
 *  Update:
 *      Added ability to fullscreen window
 *      Added aspect ratio support
 *
 *
 */
#include <string>
#include <SDL2/SDL.h>

class Display {

public:
    Display(std::string title, int w, int h);
    ~Display();

    /*function used to swap between the double buffers*/
    void SwapDisp();
    /*function to clear the screen and redraw to red green blue alpha*/
    void Clear(float r, float g, float b, float a);

    void GetAspectRadio();

    int GetHeight(){ return this->sheight;}
    int GetWidth(){ return this->swithd;}

    void SetFullscreen();


private:

    int swithd;
    int sheight;
    std::string title;
    bool isfullscreen;

    /*function used to set OpenGl attributes when creating window*/
    void set_attr();

    SDL_Window* window;
    SDL_GLContext glcontext;


};


#endif //ENGINE_DISPLAY_H

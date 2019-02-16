/*Class to handle all the display data, the class should first initialize all
 * back end items: InitSDL, OPENGL
 *
 * */

#ifndef ENGINE_DISPLAY_H
#define ENGINE_DISPLAY_H

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

private:

    int swithd;
    int sheight;
    std::string title;

    /*function used to set OpenGl attributes when creating window*/
    void set_attr();

    SDL_Window* window;
    SDL_GLContext glcontext;


};


#endif //ENGINE_DISPLAY_H

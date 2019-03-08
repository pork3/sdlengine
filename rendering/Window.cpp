#include "Window.hpp"

#include <iostream>
#include <GL/glew.h>
#include "../utils/GameOptions.hpp"
#include "../events/Listeners.hpp"
#include <map>
#include <unordered_set>



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
 *  Update 3/7
 *      Added window options (settings) and added a mark dirty function.
 *      Modified comments.
 *      Added this header comment to this file.
 *  See companion file Window.hpp for function comments.
 */



Window::Window(std::string title, int w, int h) : swidth(w), sheight(h), closerequested(false){
    // Initialize the isDirty variable
    this->isDirty = false;
    // Create a new window options object
    this->windOpts = new Management::WindowOptions();

    // Initialize the frame listeners
    for(int i = 5; i > 0; i--){
        this->gameGUIListeners.insert(pair<Events::Priority, std::unordered_set<Listener::GameGUIListener*>* >
        {static_cast<Events::Priority>(i), new std::unordered_set<Listener::GameGUIListener*>{}});
    }

    // Set the window attributes
    set_attr();

    // Create the physical window
    this->window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    w,h, SDL_WINDOW_OPENGL );

    if( window == nullptr){
        std::cout << "Error creating window" << std::endl;
    }
    this->HideWindow();
    /*
        Creates an openglcontext ... this allows open gl to have more control
            over the graphics hardware
    */
    this->glcontext = SDL_GL_CreateContext(this->window);

    /*
        Set up open Glbackend
    */
    GLenum glok = glewInit();
    if( glok != GLEW_OK){
        std::cout << "Failed to initialized openGL. Please verify your installation details." << std::endl;
    }

    isfullscreen = false;
    /*
        Enable z (depth) buffering
    */
    glEnable(GL_DEPTH_TEST);
    /*
        Enable back face culling open gl assistance in 'creating the illusion of 3d by not drawing
            items out of camera view
    */
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    /*
        Sets up a default white background
    */
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Update();
}


void Window::ExecuteGUIEvent(Events::WindowEventDetails* eventDetails){
    // Do nothing...well actually...
    std::cout << eventDetails->getEventTimeDelta() <<" "<< eventDetails->getStartGameTime()<< std::endl;
}

void Window::ShowWindow() {
    this->isDirty = true; // Need to re-draw the window
    SDL_ShowWindow(this->window);
    this->isShown = true;
}

void Window::HideWindow() {
    SDL_HideWindow(this->window);
    this->isShown = false;
}


void Window::Clear(float r, float g, float b, float a){
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->isDirty = true;
}

/*
    Called by camera class to help with rendering, returns the aspect ratio
*/
float Window::GetAspectRatio() {
    return ( static_cast<float>(this->swidth)/ static_cast<float>(this->sheight) );
}

void Window::set_attr(){
    /*
        Explicitly request open gl for at least 2^8 bits of data for
            red,green,blue and alpha data
    */
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    /*
        Request at least a buffer size of 8*4 for the above data
    */
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    /*
        Set up z (depth) buffer
    */
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    /*
        Use double bufffer (two images) if available, with double buffer drawing a 'staging'
            window and swapping what the user sees, tries to prevent tearing
    */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void Window::Update(){
    /*
        Displays the image in the buffer, sets the window's "dirty-ness" to "clean".
    */
    SDL_GL_SwapWindow(this->window);
    this->isDirty = false;
}

void Window::SetFullscreen() {
    SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}


Window::~Window(){
    delete this->windOpts;
    SDL_GL_DeleteContext(this->glcontext);
    SDL_DestroyWindow(this->window);

}

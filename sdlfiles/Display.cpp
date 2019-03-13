#include "Display.h"
#include "../err/Error.hpp"
#include <iostream>
#include <GL/glew.h>


Display::Display(Engine::GameManager* g, std::string title, int w, int h) : swithd(w), sheight(h), game(g){
    /*sets the initial window as not dirty 'dont swap' and set up gui listeners*/
    this->isDirty = false;
    for(int i = 5; i > 0; i--){
        this->gameGUIListeners.insert(pair<Events::Priority, std::unordered_set<Listener::GameGUIListener*>* >
        {static_cast<Events::Priority>(i), new std::unordered_set<Listener::GameGUIListener*>{}});
    }
    /*create window options*/
    this->windOpts = new Management::WindowOptions();
    /* initialize the openGL attributes*/
    set_attr();
    this->window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            w,h, SDL_WINDOW_OPENGL );

    if( window == nullptr){
        Error::WriteError("Error unable to crate the SDL window ");
    }
    /*creates an openglcontext ... this allows open gl to have more control
     * over the graphics hardware*/
    this->glcontext = SDL_GL_CreateContext(this->window);
    /*helps cross platform support*/
    glewExperimental = GL_TRUE;
    /*set up open Glbackend*/
    GLenum glok = glewInit();
    if( glok != GLEW_OK){
        Error::WriteError("Failed to initialize OpenGL" );
        exit(1);
    }
    //SDL_SetRelativeMouseMode(SDL_TRUE);
    /*enable z/depth buffer*/
    glEnable(GL_DEPTH_TEST);
    /*enable back face culling open gl assistance in 'creating the illusion of 3d by not drawing
     * items out of camera view*/
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    /*sets up a default white background*/
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SwapDisp();
}

void Display::Clear(float r, float g, float b, float a){
    /*sets all color bits to input value, then clears the current values*/
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::set_attr(){

    /*explicitly request open gl for at least 2^8 bits of data for
     * red,green,blue and alpha data*/
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    /*request at least a buffer size of 8*4 for the above data*/
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    /*set up zbuffer 'depth buffer*/
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    /*use double bufffer if available, with double buffer drawing a 'staging'
     * window and swapping what the user sees*/
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

}

void Display::SwapDisp(){
    /*swap the double buffer*/
    SDL_GL_SwapWindow(this->window);
    this->isDirty = false;
}
/*
 * clear up all alocated memory
 */

Display::~Display(){

    SDL_GL_DeleteContext(this->glcontext);
    SDL_DestroyWindow(this->window);

}

/*look up the GUI events and execute them*/

void Display::ExecuteGUIEvent(Events::WindowEventDetails* eventDetails){
    auto utilRef = Engine::Utilities::instance();
    for(int i = 5; i > 0; i--){
        std::unordered_set<Listener::GameGUIListener*>* uuo =  this->gameGUIListeners.at(static_cast<Events::Priority>(i));
        auto start= uuo->begin();
        auto ends = uuo->end();
        for(; ends != start; start++){
            (*start)->gameGUI(eventDetails);
            //std::chrono::high_resolution_clock::time_point new_time = high_resolution_clock::now();
            //eventDetails->eventTimeDeltaExact = utilRef->getMillisFrom(&new_time, &eventDetails->currentGameTime);
        }
    }
}

void Display::UnregisterWindowListener(Listener::GameGUIListener* list){
    for(int i = 5; i > 0; i--){
        if(this->gameGUIListeners.at(static_cast<Events::Priority>(i))->find(list) != this->gameGUIListeners.at(static_cast<Events::Priority>(i))->end()){
            this->gameGUIListeners.at(static_cast<Events::Priority>(i))->erase(list);
        }
    }

}

void Display::RegisterWindowListener(Listener::GameGUIListener* list, Events::Priority p) {
    std::unordered_set<Listener::GameGUIListener*>* uuo = this->gameGUIListeners.at(p);
    uuo->insert(list);
}

void Display::ShowWindow() {
    this->isDirty = true; // Need to re-draw the window
    /*
     * To prevent the screen from being black due to being a new window, request rendering before showing the window.
     */
    high_resolution_clock::time_point startFrameTime = high_resolution_clock::now();
    auto frameDelta = Engine::Utilities::instance()->getMillisFrom(&(this->lastFrame),
                                                                   &startFrameTime);
    Events::WindowEventDetails eventD(game, "Frame", 2, false, startFrameTime, this->startingTime, frameDelta, frameDelta,this);
    this->ExecuteGUIEvent(&eventD);
    this->lastFrame = high_resolution_clock::now();
    SDL_ShowWindow(this->window);
    this->SwapDisp();
    this->isShown = true; // Need to re-draw the window
}

void Display::HideWindow() {
    SDL_HideWindow(this->window);
    this->isShown = false;
}





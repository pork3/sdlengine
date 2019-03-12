//
// Created by zach on 2/15/19.
//
#include "GameManager.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <GL/glew.h>

#include "../glfiles/Textures.h"
#include "../glfiles/Shader.h"
#include "../Transform.h"
#include "../Camera.h"
#include <chrono>
#include "../events/EventDispatcher.hpp"
#include "../math/EngineMath.hpp"
using namespace Engine;
Engine::GameLoop::GameLoop() : startingTime(std::chrono::high_resolution_clock::now()), lastTick(std::chrono::high_resolution_clock::now()){
    options = new Management::GameOptions(60);
    initback();
}

Engine::GameLoop::~GameLoop(){

    delete this->display;
    SDL_Quit();
}

void Engine::GameLoop::initback(){

    /*initialize SDL with everything, maybe change to select items*/
    SDL_Init(SDL_INIT_EVERYTHING);
        if( SDL_INIT_VIDEO < 0 ) {
            std::cout << "Error creating video " << SDL_GetError() << std::endl;
        }

}


void Engine::GameLoop::CreateWindow(std::string title, int w, int h){
    /* TODO define defaults width and height */
    (w == 0) ?w=800: w;
    (h == 0) ?h=600: h;
    this->display = new Display(this, title,w,h);
    this->display->HideWindow();
}



void Engine::GameLoop::Run(){

    //Event e = Event();
    SDL_Event e;
    /*
                    /*position                        texture*/
    //Vertex v[] = { Vertex(glm::vec3(-0.5, -0.5, 0) , glm::vec2(0.0,0.0)),
        //            Vertex(glm::vec3(0.0, 0.5, 0) , glm::vec2(1.0,1.0)),
      //              Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0,0.0))
    //};

    /*create index buffer*/
    //unsigned int ind[] = {0 , 1 , 2};

    //Transform transform( glm::vec3(0.0,.3,0.5), /*pos*/
     //                    glm::vec3(0,0,0), /*rot*/
     //                    glm::vec3(0,0,0));/*scl*/
    /*
    float s = 0.0f;
    float aspectratio = (display->GetWidthf()/display->GetHeightf());
    std::cout << aspectratio << "aspect ratio " <<std::endl;

    Camera camera(glm::vec3(1,0,5), 70.0f, aspectratio, 0.01f, 1000.0f);

    Shader shader("../glfiles/shaders/testshader");

    Textures texture("../glfiles/textures/illuminati.jpg");

    Mesh m(v, sizeof(v)/sizeof(v[0]), ind, sizeof(ind)/sizeof(ind[0]));
    Mesh m2("../glfiles/obj/Crate1.obj");*/
    while(this->gameRunning){
        // Fire tick events
        Events::EventDispatcher* ed = Events::EventDispatcher::instance();
        bool runTick = this->gamePaused;
        std::chrono::high_resolution_clock::time_point startTickTime = high_resolution_clock::now();

        if (runTick) {
            auto tickDelta = Engine::Utilities::instance()->getMillisFrom(&this->lastTick, &startTickTime);
            if (tickDelta >= Engine::Utilities::instance()->getMillisWaitTime(this->options->getTickRateTarget())) {
                Events::TimedEventDetails eventD(this, "Tick", 3, false, startTickTime, this->startingTime, tickDelta,
                                                 tickDelta);
                ed->ExecuteTickEvent(&eventD);
                this->lastTick = high_resolution_clock::now();
            }
        } else {
            //Always set the lastTick
            this->lastTick = high_resolution_clock::now();
        }

        // Key event is cancellable, along with mouse button down/up
        // Fire SDL events
        int isEvent = SDL_PollEvent(&e);
		std::chrono::high_resolution_clock::time_point startSDLTime = high_resolution_clock::now();
		if(isEvent) {
            switch (e.type) {
                case SDL_KEYDOWN: {
                    Events::KeyboardEventDetails eventD(this, "KeyDown", 4, true, startSDLTime, this->startingTime,
                                                        e.key.keysym.sym,
                                                        e.key.repeat, SDL_GetModState());
                    ed->ExecuteKeyEvent(&eventD);
                    break;
                }
                case SDL_KEYUP: {
                    Events::KeyboardEventDetails eventD(this, "KeyDown", 5, true, startSDLTime, this->startingTime,
                                                        e.key.keysym.sym,
                                                        e.key.repeat, SDL_GetModState());
                    ed->ExecuteKeyEvent(&eventD);
                    break;
                }
                case SDL_MOUSEMOTION: {
                    Events::MouseButtonEventDetails eventD(this, "MouseMove", 8, true, startSDLTime, this->startingTime,
                                                           e.button.state,
                                                           Math::Vector2Int(static_cast<int>(e.motion.x),
                                                                            static_cast<int>(e.motion.y)),
                                                           Math::Vector2Int(static_cast<int>(e.motion.xrel),
                                                                            static_cast<int>(e.motion.yrel)), 0,
                                                           SDL_GetModState());
                    ed->ExecuteMouseEvent(&eventD);

                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    Events::MouseButtonEventDetails eventD(this, "MouseDown", 6, true, startSDLTime, this->startingTime,
                                                           e.button.state,
                                                           Math::Vector2Int(static_cast<int>(e.button.x),
                                                                            static_cast<int>(e.button.y)),
                                                           Math::Vector2Int(0, 0), e.button.clicks, SDL_GetModState());
                    ed->ExecuteMouseEvent(&eventD);

                    break;
                }
                case SDL_MOUSEBUTTONUP: {
                    Events::MouseButtonEventDetails eventD(this, "MouseUp", 7, true, startSDLTime, this->startingTime,
                                                           e.button.state,
                                                           Math::Vector2Int(static_cast<int>(e.button.x),
                                                                            static_cast<int>(e.button.y)),
                                                           Math::Vector2Int(0, 0), e.button.clicks, SDL_GetModState());
                    ed->ExecuteMouseEvent(&eventD);
                    break;
                }
                case SDL_QUIT: {
                    this->StopGame(false);
                    break;
                }
                default:
                    break;
            }
        }














        high_resolution_clock::time_point startFrameTime = high_resolution_clock::now();
        auto vpntr = this->display;
        if(!((vpntr)->isShown)) {
            (vpntr)->lastFrame = high_resolution_clock::now();
        }else {
            auto frameDelta = Engine::Utilities::instance()->getMillisFrom(&((vpntr)->lastFrame),
                                                                           &startFrameTime);
            if ((vpntr)->isDirty || frameDelta >= Engine::Utilities::instance()->getMillisWaitTime((vpntr)->windOpts->getFrameRateTarget())){
                // The frame has requested to render.
                // Call the frame listeners registered to this window, may include world renderers
                Events::WindowEventDetails eventD(this, "Frame", 2, false, startFrameTime, this->startingTime, frameDelta, frameDelta, vpntr);
                (vpntr)->ExecuteGUIEvent(&eventD);
                (vpntr)->SwapDisp();

                (vpntr)->lastFrame = high_resolution_clock::now();
            }
        }
    }
}

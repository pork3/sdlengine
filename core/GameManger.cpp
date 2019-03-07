// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 *
 *	Last updated by: Zachary Bower
 *	Last updated on: Mar 6, 2019
 *
 *	Purpose:
 *		This header class is to provide base classes for managing the game, added support for initializing
 *      libraries used, and access to n number of windows
 *
 *
 *
 */

 // Standard includes
#include "../events/Listeners.hpp"
#include "GameManager.hpp"
#include <vector>
#include <unordered_set>
#include <chrono>
#include <thread>
#include <iostream>
#include "../utils/Utils.hpp"
#include "../utils/GameOptions.hpp"
#include "../events/EventDispatcher.hpp"




// A function to request stopping of the game. A stopping event will be dispatched, however it is
// 		cancellable based on if this was not forced.
void Engine::GameManager::StopGame(bool forced){
    //if forced, just stop
    if(forced){
        this->gameRunning = false;
    }
    //technically run through all event listeners.
}

// A function to pause the execution of tick events for the game.
void Engine::GameManager::PauseGame(){
    this->gamePaused = false;
}

// A function to resume the execution of tick events for the game.
void Engine::GameManager::ResumeGame(){
    this->gamePaused = true;
}

// A function to handle aborting the game (critical error), a reason to be logged should be supplied.
void Engine::GameManager::Abort(std::string reason){

}
std::mutex* Engine::GameManager::io_mutex = new std::mutex; // Cheating?

void Engine::GameManager::Run(void){
    Events::EventDispatcher* ed = Events::EventDispatcher::instance();
    while(this->gameRunning){
        bool runTick = false;
        Engine::GameManager::io_mutex->lock();
        runTick = this->gamePaused;
        this->io_mutex->unlock();
        std::chrono::high_resolution_clock::time_point startTickTime = high_resolution_clock::now();

        if(runTick){
            auto tickDelta = Engine::Utilities::instance()->getMillisFrom(&this->lastTick, &startTickTime);
            if(tickDelta >= Engine::Utilities::instance()->getMillisWaitTime(Management::GameOptions::instance()->getTickRateTarget())){
                Events::TimedEventDetails evd("Tick", 3, false, startTickTime, this->startingTime, tickDelta, tickDelta);
                //std::cout << "Tick Tick! Delta: " << tickDelta << std::endl;
                ed->ExecuteTickEvent(&evd);
                this->lastTick = high_resolution_clock::now();
            }
        }else{
            //Always set the lastTick
            this->lastTick = high_resolution_clock::now();
        }

        // Secondly run the GUI if enough time has passed.
        high_resolution_clock::time_point startFrameTime = high_resolution_clock::now();
        auto frameDelta =Engine::Utilities::instance()->getMillisFrom(&this->lastFrame, &startFrameTime);
        if(frameDelta >=
           Engine::Utilities::instance()->getMillisWaitTime(Management::GameOptions::instance()->getFrameRateTarget())){
            std::cout << "Frame Tick! Delta: " << frameDelta <<std::endl;
            Events::TimedEventDetails evd("Frame", 2, false, startTickTime, this->startingTime, frameDelta, frameDelta);

            this->lastFrame = high_resolution_clock::now();

        }

        // Actually dispatch rendering to the window...


    }

}
void Engine::jumperThread(Engine::GameManager* gm){
    //PURELY AS A FIX
    if(!gm->gameSetup || gm->gameRunning){
        return;
    }
    gm->gameRunning = true;
    gm->Run();
}
// A function to request the starting of the game. The game can start paused if the argument is true.
void Engine::GameManager::StartGame(bool startPaused){
    if(this->gameRunning){
        //TODO log it here!
    }else{
        this->gameSetup = true;
        this->gamePaused = !startPaused;
        this->options = Management::GameOptions::instance();
        this->startingTime = high_resolution_clock::now();
        this->mainGameThread = new std::thread(jumperThread, Engine::GameManager::instance());
    }
}

bool Engine::GameManager::CreateWindow(std::string title, int height, int width) {

    this->window = new Window(title, height, width);
    if( this-> window == nullptr) {
        std::cout << "Error creating window named" << title << std::endl;
        return false;
    }
    return true;

}

void Engine::GameManager::InitSystems(){

    SDL_Init(SDL_INIT_EVERYTHING);
    if( SDL_INIT_VIDEO < 0 ) {
        std::cout << "Error creating video " << SDL_GetError() << std::endl;
    }

}

Engine::GameManager::~GameManager(){

    delete this->window;

    SDL_Quit();
}


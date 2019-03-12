#ifndef ENGINE_GAMEMANAGER_H
#define ENGINE_GAMEMANAGER_H

// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
  
  	Last updated by: Chase Craig
  	Last updated on: Mar. 11, 2019
  
  	Purpose:
        This header file is to outline the functions available for controlling the logic for handling the
			game engine. This serves as the main controller interface for managing the game state, as well as
			running the main game loop and dispatching rendering and logic events.

	Usage:
		To create and bind a window to this object, 

 */




#include "../sdlfiles/Event.h"
#include "../sdlfiles/Display.h"
#include "../glfiles/Mesh.h"
#include "../events/EventDispatcher.hpp"

namespace Engine {
    class GameManager {


    public:
		
        GameManager();

        ~GameManager();

        /*called to create the window*/
        void CreateWindow(std::string title, int w, int h);

        void StartGame(bool startPaused){
            // TODO: GO THROUGH ALL LISTENERS
            Events::EventDispatcher* ed = Events::EventDispatcher::instance();
            std::chrono::high_resolution_clock::time_point startTickTime = high_resolution_clock::now();
            Events::EventDetails eventD(this, "START", 0, true, startTickTime, this->startingTime);
            if(startPaused){eventD.cancel();} // Immediately cancel it (which means the game is pausing...)
            ed->ExecuteGameEvent(Events::GameEvent::STOP,&eventD);
            this->gameRunning = true;
            this->gamePaused = !eventD.isCancelled();
            this->Run();
        }

        void PauseGame(){
            this->gamePaused = false;
        }
        void ResumeGame(){
            this->gamePaused = true;
        }
        void StopGame(bool forced){
            Events::EventDispatcher* ed = Events::EventDispatcher::instance();
            std::chrono::high_resolution_clock::time_point startTickTime = high_resolution_clock::now();
            Events::EventDetails eventD(this, "STOP", 1, forced, startTickTime, this->startingTime);
            ed->ExecuteGameEvent(Events::GameEvent::STOP,&eventD);
            this->gameRunning = false;
        }

        void AbortGame(std::string reason){
            // TODO: LOG ERROR!
            this->gameRunning = false;
        }



        Management::GameOptions* getOptions(){return this->options;}

        Display* getWindow(){return this->display;}
    private:
        void Run();
        /*function called by constructor to initialize the back end*/
        void initback();

        Display *display = nullptr;
        bool gameRunning;
        std::chrono::high_resolution_clock::time_point startingTime;
        bool gamePaused;
        high_resolution_clock::time_point lastTick;
        Management::GameOptions *options;


    };
}

#endif //ENGINE_GAMEMANAGER_H

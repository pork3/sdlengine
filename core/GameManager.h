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
		CreateWindow creates a window with a given title, width and height.
		
		StartGame signals the game manager to start running the game loop. However, this method WILL RUN ON
			THE THREAD THAT CALLED IT, AND HENCE WILL BLOCK ALL FURTHER EXECUTION UNTIL THE GAME HAS STOPPED.
			If the startPaused argument is true, it acts as if the caller had executed a pause game request 
			immediately after calling StartGame.
		
		PauseGame will stop executing game tick events, however all other events will be executed. 
		
		ResumeGame will resume execution of game ticks in the game loop.
		
		StopGame will attempt to halt execution of the game loop. This will call all listeners registered
			to recieve this event and will see if they cancel this event (which results in an ignored
			close request). If the "forced" argument is true, the event can not be cancelled.
		
		AbortGame will attempt to immediately halt the execution of the game loop and does not alert any
			listeners for game stopping. The argument is for logging purposes, as it will be logged.
			
		GetOptions will return a pointer to the gameOptions object that stores the "tick" rate for the
			game logic loop.
		
		GetWindow will return a pointer to the display (window) object attached to this object.
		
		Although hidden: 
			Run is the internal function responsible for running the game loop.
			Initback is the function responsible for setting up the back end SDL and OpenGL calls.
			
 */




#include "../sdlfiles/Display.h"
#include "../glfiles/Mesh.h"
#include "../events/EventDispatcher.hpp"

namespace Engine {
    class GameManager {


    public:
		
        GameManager();

        ~GameManager();

        // Called to create the window
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
        void initback();

		// Variables attached to this object.
        Display *display = nullptr;
        bool gameRunning;
        std::chrono::high_resolution_clock::time_point startingTime;
        bool gamePaused;
        high_resolution_clock::time_point lastTick;
        Management::GameOptions *options;


    };
}

#endif //ENGINE_GAMEMANAGER_H

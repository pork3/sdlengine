#include "GameLoop.h"
#include <iostream>

GameLoop::GameLoop(){
	Event e = Event();

}

GameLoop::~GameLoop(){
	delete this->gamewindow;
}

void GameLoop::Start(){

	init_req();
	run();
}

void GameLoop::run(){

	this->gamewindow = new Window_SDL("Test");
	if( this->gamewindow != nullptr){
		SDL_Delay(2000);

		/*poll events*/
		while( e.GetState() != EXIT){
			parse_input();
		}

	} else {
		std::cout << "Error creating game" <<std::endl;
	}
}

void GameLoop::parse_input(){

	/*use sdl to get user input*/
	while(SDL_PollEvent(e.GetEvent())){
		switch(e.GetEvent()->type){
			/*user hits the X buttons*/
			case SDL_QUIT:
				e.SetState(EXIT);
				break;
			/*sdl detects mouse motion*/
			case SDL_MOUSEMOTION:
				std::cout << "X: " << e.GetEvent()->motion.x << " Y: " << e.GetEvent()->motion.y << std::endl;
				break;

		}
	}
}


void GameLoop::init_req(){
	/*create sdl instance*/
		SDL_Init( SDL_INIT_EVERYTHING);
		if( SDL_INIT_VIDEO  < 0)
			printf( "SDL could not be initialized: %s\n", SDL_GetError() );
}
#include "GameLoop.h"
#include <iostream>

GameLoop::GameLoop(){


}

GameLoop::~GameLoop(){
	delete this->gamewindow;
}

void GameLoop::Start(){

	InitReq();
	this->gamewindow = new Window_SDL("Test");
	if( this->gamewindow != nullptr){
		SDL_Delay(2000);

	} else {
		std::cout << "Error creating game" <<std::endl;
	}

}


void GameLoop::InitReq(){
	/*create sdl instance*/
		SDL_Init( SDL_INIT_EVERYTHING);
		if( SDL_INIT_VIDEO  < 0)
			printf( "SDL could not be initialized: %s\n", SDL_GetError() );
}
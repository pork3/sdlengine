#ifndef _INCLUDED_EVENT_H
#define _INCLUDED_EVENT_H

/*This class handles user input including the current
state the game is in and any keyboard/mouse movements*/
extern "C"{

	#include <SDL2/SDL.h>
}

enum EventStates_e{
	RUNNING = 1,
	EXIT = 0
};

class Event{

	public:
		Event();
		~Event();
		
		EventStates_e GetState(){return current_state;}
		void SetState(EventStates_e e){this->current_state = e;}
		SDL_Event* GetEvent(){return this->evnt;}

	
	private:
		EventStates_e current_state;
		SDL_Event* evnt;



};

#endif
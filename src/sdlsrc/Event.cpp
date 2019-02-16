#include "Event.h"


Event::Event(): current_state(RUNNING){
	evnt = new SDL_Event;
}

Event::~Event(){
	delete evnt;
}
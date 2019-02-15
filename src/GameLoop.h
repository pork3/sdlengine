#ifndef _INCLUDED_GAMELOOP_H
#define _INCLUDED_GAMELOOP_H

#include "./sdlsrc/window.h"
#include "./sdlsrc/Event.h"

/*Main class to set up all requirements for the system, should be called
by the entry point
tasks: 
- initialized requirements
- free game resources not self freed

*/
class GameLoop{

	public:
		GameLoop();
		~GameLoop();

		/*main game loop called in main*/
		void Start();

		

	private:

		Window_SDL* gamewindow;
		/*Initializes all requirements used by the system
		including SDL, Graphics lib, etc*/
		void init_req();
		void run();
		void parse_input();
		Event e;

};


#endif
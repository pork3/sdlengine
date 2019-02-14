#ifndef _INCLUDED_WINDOW_H
#define _INCLUDED_WINDOW_H
#include <SDL2/SDL>
#include <string>

/*class to set up a display window using SDL, called by the main game loop
	

*/

class Window_SDL{

	public:
		/*get width and height from the defaults*/
		Window_SDL(std::string t);
		/*constructor for user defined width, and height*/
		Window_SDL(std::string t,int sw, int sh);

		~Window_SDL();


	private:
		int screen_width;
		int screen_height;
		std::string title;
		SDL_Window* window;

		SDL_Window* create_window();
};



#endif
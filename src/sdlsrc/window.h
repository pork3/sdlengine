#ifndef _INCLUDED_WINDOW_H
#define _INCLUDED_WINDOW_H

/*SDL is a C library so add as extern C*/
extern "C"{

	#include <SDL2/SDL.h>
}
#include<GL/glew.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
#include <string>

/*class to set up a display window using SDL, called by the main game loop
	

*/

class Window_SDL{

	public:
		/*get width and height from the defaults*/
		Window_SDL(std::string t);
		/*constructor for user defined width, and height*/
		Window_SDL(std::string t,int sw, int sh);

		SDL_Window* GetWindow(){return this->window;}

		~Window_SDL();


	private:

		int screen_width;
		int screen_height;
		std::string title;

		SDL_Window* window;
		SDL_GLContext context;

		SDL_Window* create_window();

		bool set_opengl_attr();

};



#endif
#include "window.h"
#include <iostream>


												/*hardcoded defaults change with settings namespace*/
Window_SDL::Window_SDL(std::string t): title(t), screen_width(800), screen_height(600){
		this->window = create_window();

		this->context = SDL_GL_CreateContext(this->window);
		SDL_GL_SetSwapInterval(1);
			glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
}

Window_SDL::Window_SDL(std::string t, int sw, int sh): title(t), screen_width(sw),screen_height(sh){
		this->window = create_window();
		this->context = SDL_GL_CreateContext(this->window);
		SDL_GL_SetSwapInterval(1);
			glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(this->window);

}

Window_SDL::~Window_SDL(){
	SDL_DestroyWindow(window);
	/* destroy the surface and set to null
	DESTROY CONTEXT*/
	window = nullptr;
}

SDL_Window* Window_SDL::create_window(){

	SDL_Window* sw = SDL_CreateWindow(this->title.c_str(),SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
									this->screen_width, this->screen_height, SDL_WINDOW_OPENGL);
	if(sw == nullptr){
		std::cout << "Error creating window " << SDL_GetError() << std::endl;
	}
	


	return sw;
}

bool Window_SDL::set_opengl_attr(){
	/*TODO set up error checiking */
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	// Turn on double buffering with a 24bit Z buffer.
	// You may need to change this to 16 or 32 for your system
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	return true;
}


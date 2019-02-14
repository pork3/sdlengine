#include "window.h"


												/*hardcoded defaults change with settings namespace*/
Window_SDL::Window_SDL(std::string t): title(t), screen_width(800), screen_height(600){
		this->window = create_window();
}

Window_SDL::Window_SDL(std::string t, int sw, int sh): title(t), screen_width(sw),screen_height(sh){
		this->window = create_window();
}

Window_SDL::~Window_SDL(){
	SDL_FreeSurface(window);
	window = null;
}

SDL_Window* Window_SDL::create_window(){

	SDL_Window* sw = SDL_CreateWindow(this->title,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
									this->screen_width, this->screen_height, SDL_WINDOW_SHOWN);
	return sw;
}
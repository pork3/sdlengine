#include "Window.hpp"

Window::Window(const RenderedApplication &application, int width, int height, const std::string &title) : width(width), height(height), title(title){

    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

}

void Window::Update() {

    SDL_GL_SwapWindow(this->window);
}

Window::~Window() {

    SDL_DestroyWindow(this->window);
}

bool Window::IsFullScreen() {
    return false;
}

void Window::SetFullScreen() {

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

}

void Window::SetWidth(int width) {
    if( width > 0) {
        this->width = width;
    }
    ChangeWindow();

}

void Window::SetHeight(int height) {
    if( height > 0){
        this->height = height;
    }
    ChangeWindow();
}

void Window::ChangeWindow(){
    SDL_SetWindowSize(this->window, this->width, this->height);
}

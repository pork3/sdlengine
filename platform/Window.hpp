#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#include <SDL2/SDL.h>
#include <string>
#include "RenderedApplication.hpp"


class Window {

public:

    Window(const RenderedApplication& application, int width, int height, const std::string& title );
    virtual ~Window();
    void Update();

    bool IsFullScreen();
    int GetWidth()const { return this->width; }
    int GetHeight()const { return  this->height;}
    float GetAspectRatio()const { return static_cast<float >(width) / static_cast<float>(height); }

    void SetWidth(int width);
    void SetHeight(int height);
    void SetFullScreen();

private:
    int width;
    int height;
    std::string title;
    SDL_Window* window;
    bool fullscreen;
    void ChangeWindow();
};


#endif //ENGINE_WINDOW_H

#ifndef ENGINE_RENDEREDAPPLICATION_H
#define ENGINE_RENDEREDAPPLICATION_H

#include<SDL2/SDL.h>



class RenderedApplication {

public:

    static RenderedApplication* CreateApplication();

    virtual ~RenderedApplication();

    virtual bool IsRunning();

private:
    bool running;
    RenderedApplication();

};


#endif //ENGINE_RENDEREDAPPLICATION_H

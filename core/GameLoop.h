#ifndef ENGINE_GAMELOOP_H
#define ENGINE_GAMELOOP_H
/*This class contains the main game loop...
  current flow:
  init sdl

*/
#include "./sdlfiles/Event.h"
#include "./sdlfiles/Display.h"
#include "./glfiles/Mesh.h"


class GameLoop {


public:
    GameLoop();
    ~GameLoop();
    /*called to create the window*/
    void CreateWindow(std::string title, int w, int h);
    void Run();

private:
    /*function called by constructor to initialize the back end*/
    void initback();
    void parseinput(Event& ev);
    Display* display = nullptr;
    bool running;


};


#endif //ENGINE_GAMELOOP_H

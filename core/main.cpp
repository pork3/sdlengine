#include <iostream>
#include "GameLoop.h"


int main() {

    GameLoop gl = GameLoop();
    gl.CreateWindow("Test2", 1000, 600);

    gl.Run();

}
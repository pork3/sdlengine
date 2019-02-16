#include <iostream>
#include "GameLoop.h"

int main() {

    GameLoop gl = GameLoop();
    gl.CreateWindow("Test", 800, 600);

    gl.Run();

}
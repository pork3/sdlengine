//
// Created by zach on 3/3/19.
//

#include "rendering/Window.hpp"
#include "Application.h"
#include <iostream>

int main(int argc, char** argv){

    Application a;
    int r;

    Window w = Window("test", 800,600);
    while(a.IsRunning()){

        a.Process();

    }

    return 0;
}

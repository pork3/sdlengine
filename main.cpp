#include "./core/GameManager.hpp"
#include "./rendering/Window.hpp"
#include "./events/InputHandler.hpp"
#include "Application.h"
#include <iostream>

class test : public InputHandler{
public:
    test(){
        down = false;
    };

    virtual void OnKeyDown( uint32_t key , bool repeated ){
        down = true;
    }
    virtual void OnKeyUp(uint32_t key , bool repeated ){
        down = false;
    }
    virtual void OnMouseDown(uint32_t key , uint8_t clicks ){
        down = true;
    };
    virtual void OnMouseUp(uint32_t key , uint8_t clicks ){
        down = false;
    }
    virtual void OnMouseMotion(int32_t x , int32_t y, int32_t dx , int32_t dy ){
        std::cout << "x : " << x  << " " << "y : " << y << std::endl;
    };

    bool GetDown(){return this->down;}
private:
    bool down;
};


int main(int argc , char** argv){


    Application a = Application();
    test t = test();
    Window w = Window("tttt", 600, 600);
    while( a.IsRunning() ){
        if(t.GetDown())
            std::cout << "swag" << std::endl;
        a.Process(t);
    }

    return 0;
}
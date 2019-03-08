#include "./core/GameManager.hpp"
#include "./rendering/Window.hpp"
#include "./events/InputHandler.hpp"
#include "./rendering/Mesh.h"
#include "Application.h"
#include "rendering/RenderCore.hpp"
#include "./rendering/Shader.h"
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

    Vertex ve[] = {
            glm::vec3(-.5, .5, 0),
            glm::vec3(0, .5, 0),
            glm::vec3(.5, -.5, 0), };


    Application a = Application();
    test t = test();

    Window w = Window("tttt", 800, 800);
   //hader s = Shader("res/shaders/shader");
    RenderCore r = RenderCore(w);
    r.SetVert(ve);


    while( a.IsRunning() ){

        a.Process(t);
        if(t.GetDown()){
            std::cout << "swag" << std::endl;
            r.Render();
        }

    }

    return 0;
}
//
// Created by zach on 2/15/19.
//
#include "GameLoop.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <GL/glew.h>

#include "./glfiles/Textures.h"
#include "./glfiles/Shader.h"
#include "Transform.h"
#include "Camera.h"

GameLoop::GameLoop(){

    initback();
}

GameLoop::~GameLoop(){

    delete this->display;
    SDL_Quit();
}

void GameLoop::initback(){

    /*initialize SDL with everything, maybe change to select items*/
    SDL_Init(SDL_INIT_EVERYTHING);
        if( SDL_INIT_VIDEO < 0 ) {
            std::cout << "Error creating video " << SDL_GetError() << std::endl;
        }

}

void GameLoop::CreateWindow(std::string title, int w, int h){
    /* TODO define defaults width and height */
    (w == 0) ?w=800: w;
    (h == 0) ?h=600: h;
    this->display = new Display(title,w,h);
}

void GameLoop::parseinput(Event &ev){

    while(SDL_PollEvent(ev.GetEvent())){

        switch(ev.GetEvent()->type){
            /*User hits the x button on window*/
                case SDL_QUIT:
                    this->running = false;
                    break;
                case SDL_MOUSEMOTION:
                    std::cout << "X: " << ev.GetEvent()->motion.x << " Y: " << ev.GetEvent()->motion.y << std::endl;
                    break;

        }

    }

}


void GameLoop::Run(){

    Event e = Event();
                    /*position                        texture*/
    Vertex v[] = { Vertex(glm::vec3(-0.5, -0.5, 0) , glm::vec2(0.0,0.0)),
                    Vertex(glm::vec3(0.0, 0.5, 0) , glm::vec2(1.0,1.0)),
                    Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0,0.0))
    };

    /*create index buffer*/
    unsigned int ind[] = {0 , 1 , 2};

    Transform transform( glm::vec3(0.0,.3,0.5), /*pos*/
                         glm::vec3(0,0,0), /*rot*/
                         glm::vec3(0,0,0));/*scl*/

    float s = 0.0f;
    float aspectratio = (display->GetWidthf()/display->GetHeightf());
    std::cout << aspectratio << "aspect ratio " <<std::endl;

    Camera camera(glm::vec3(1,0,5), 70.0f, aspectratio, 0.01f, 1000.0f);

    Shader shader("../glfiles/shaders/testshader");

    Textures texture("../glfiles/textures/illuminati.jpg");

    Mesh m(v, sizeof(v)/sizeof(v[0]), ind, sizeof(ind)/sizeof(ind[0]));
    Mesh m2("../glfiles/obj/Crate1.obj");
    while(this->running){

        this->display->Clear(0.0f,1.0f,0.5f,1.0f);


        transform.GetPos().x = sinf(s);
        transform.SetRot(glm::vec3(cosf(s),cosf(s),cosf(s) ));


        m2.DrawMesh();
        shader.Bind();
        shader.Update(transform, camera);
        texture.Bind(0);
        this->display->SwapDisp();
        parseinput(e);
        s+= .01;
    }
}

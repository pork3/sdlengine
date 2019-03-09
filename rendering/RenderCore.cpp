#include "RenderCore.hpp"
#include <iostream>


RenderCore::RenderCore(Window &w) : window(w ) , texture(Textures("../res/textures/pizza.jpg")){

    this->context = SDL_GL_CreateContext(w.GetContext());
    this->defshader = new Shader("../res/shaders/shader");

    //this->transform = Transform();


}

void RenderCore::Render() {

    this->window.Clear(.0f,.15f,.3f,1.0f);

    m->Draw();
    defshader->Bind();
    texture.Bind(0);

    this->window.Update();

}

RenderCore::~RenderCore() {

    delete m;
    delete defshader;
}

void RenderCore::SetVert(Vertex v[]) {

    m = new Mesh(v , 3 );
}


/*changes the current window the user is using*/
bool RenderCore::ChangeWindow(Window &w) {

    delete this->context;

    this->window = w;
    this->context = SDL_GL_CreateContext(w.GetContext());
    return true;
}


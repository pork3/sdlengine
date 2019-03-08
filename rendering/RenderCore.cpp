#include "RenderCore.hpp"
#include <iostream>


RenderCore::RenderCore(Window &w) : window(w) {

    this->context = SDL_GL_CreateContext(w.GetContext());
    this->defshader = new Shader("../res/shaders/shader");
    //this->transform = Transform();


}

void RenderCore::Render() {

    this->window.Clear(.0f,.15f,.3f,1.0f);

    m->Draw();
    defshader->Bind();

    this->window.Update();

}

RenderCore::~RenderCore() {

    delete m;
    delete defshader;
}

void RenderCore::SetVert(Vertex v[]) {

    int r = sizeof(*v);
    int l = sizeof(v[0]);

    m = new Mesh(v , 3);
}


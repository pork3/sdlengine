#include "RenderCore.hpp"
#include <iostream>


RenderCore::RenderCore(Window &w) : window(w ) , texture(Textures("../res/textures/pizza.jpg")),
defshader("../res/shaders/shader"), transform( glm::vec3(0.0,.3,0.5), //pos
        glm::vec3(0,0,0), //rot
        glm::vec3(0,0,0))//scl
{


    //this->transform = Transform();


}

void RenderCore::Render() {

    this->window.Clear(.0f,.15f,.3f,1.0f);

    transform.GetPos().x = sinf(count);
    transform.GetRot().z = count * 44;

    defshader.Bind();
    defshader.Update(transform);
    texture.Bind(0);
    m->Draw();

    this->window.Update();

}

RenderCore::~RenderCore() {

    delete m;

}

void RenderCore::SetVert(Vertex v[], unsigned int size) {

    m = new Mesh(v , size );
}


/*changes the current window the user is using*/
bool RenderCore::ChangeWindow(Window &w) {

    this->window = w;
    return true;
}


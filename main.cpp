#include <iostream>
#include "core/GameManager.h"
#include "sdlfiles/Display.h"
#include "events/Listeners.hpp"
#include "Transform.h"
#include "Camera.h"
#include "glfiles/Mesh.h"
#include "glfiles/Shader.h"
#include "glfiles/Textures.h"
#include "glfiles/ObjLoader.h"

class L : public Listener::GameGUIListener, public Listener::GameTickListener, public Listener::GameMouseListener, public Listener::GameKeyboardListener{
public:
    Vertex** v;
    unsigned int* ind;
    Transform* t;
    Camera* cam;
    Shader* s;
    Textures* te;
    Textures* t1;
    Mesh* m1;
    Mesh* m2;
    float rotx;
    float roty;
    float rotz;
    float posx;
    float posy;
    float posz;
    float ff;
    L(Display* d){
        ff = 0;
        rotx = 0;
        roty = 0;
        rotz = 0;
        posx = 1;
        posy = 0;
        posz = 5;
        v = new Vertex*[3];
                            /*position                        texture*/
        v[0] = new Vertex(glm::vec3(-0.5, -0.5, 0) , glm::vec2(0.0,0.0));
        v[1] = new Vertex(glm::vec3(0.0, 0.5, 0) , glm::vec2(1.0,1.0));
        v[2] = new Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0,0.0));

        /*create index buffer*/
        ind = new unsigned int[3];
        ind[0] = 0;
        ind[1] = 1;
        ind[2] = 2;


        t = new Transform( glm::vec3(0.0,.3,0.5), /*pos*/
                             glm::vec3(0,0,0), /*rot*/
                             glm::vec3(0,0,0));/*scl*/

        float aspectratio = (d->GetWidthf()/d->GetHeightf());
        std::cout << aspectratio << "aspect ratio " <<std::endl;

        cam = new Camera(glm::vec3(1,0,5), 70.0f, aspectratio, 0.01f, 1000.0f);

        s = new Shader("./glfiles/shaders/testshader");

        te = new Textures("./glfiles/textures/illuminati.jpg");
        t1 = new Textures("./glfiles/textures/pizza.jpg");
        m1 = new Mesh("./glfiles/obj/s.obj");
        m2 = new Mesh("./glfiles/obj/Crate1.obj");

    }
    void gameMouseButtonPressed(Events::MouseButtonEventDetails* event){
        std::cout << "Mouse P" << std::endl;
    }
    void gameMouseButtonReleased(Events::MouseButtonEventDetails* e){
        std::cout << "Mouse R" << std::endl;

    }
    void gameMouseMoved(Events::MouseButtonEventDetails* e){
        std::cout << "Mouse M " << e->getMousePosition() << " " << e->getDeltaMousePosition()<< std::endl;
        if(e->isButtonLDown()) {
            roty += e->getDeltaMousePosition().getX() / 100.0f;
            //rotx -= glm::cos(roty) * e->getDeltaMousePosition().getY() / 120.0f;
            //rotz += glm::sin(roty) * e->getDeltaMousePosition().getY() / 120.0f;
            this->cam->SetEulerRotation(glm::vec3(rotx, roty, rotz));
        }

    }
    void gameKeyPressed(Events::KeyboardEventDetails* e){
        std::cout << "Key P " << e->getKey() << std::endl;
        if(e->getKey() == 103){ // G
            rotx += 0.01f;
            this->cam->SetEulerRotation(glm::vec3(rotx, roty, rotz));
        }
        if(e->getKey() == 104){ // H
            roty += 0.01f;
            this->cam->SetEulerRotation(glm::vec3(rotx, roty, rotz));
        }
        if(e->getKey() == 105){ // I
            rotz += 0.01f;
            this->cam->SetEulerRotation(glm::vec3(rotx, roty, rotz));
        }
        if(e->getKey() == 1073741906){ // Up
            //posz -= 0.1f;
            this->cam->MoveRelativeToView(glm::vec3(0, 0, -0.1f));
        }
        if(e->getKey() == 1073741905){ // Down
            //posz += 0.1f;
            this->cam->MoveRelativeToView(glm::vec3(0, 0, +0.1f));
        }
        if(e->getKey() == 1073741904){ // Left
            //posx -= 0.1f;
            this->cam->MoveRelativeToView(glm::vec3(-0.1f,0,0));
        }
        if(e->getKey() == 1073741903){ // Right
            //posx += 0.1f;
            this->cam->MoveRelativeToView(glm::vec3(0.1f,0,0));
        }
        if(e->getKey() == 1073741899){ // PageUp
            //posy += 0.1f;
            this->cam->MoveRelativeToView(glm::vec3(0, 0.1f,0));
        }
        if(e->getKey() == 1073741902){ // Right
            //posy -= 0.1f;
            this->cam->MoveRelativeToView(glm::vec3(0, -0.1f,0));
        }
    }
    void gameKeyReleased(Events::KeyboardEventDetails* e){
        std::cout << "Key R " << e->getKey() << std::endl;
        if(e->getKey() == 100){
            e->getGame()->PauseGame();
        }
        if(e->getKey() == 101){
            e->getGame()->ResumeGame();
        }
        if(e->getKey() == 113){
            e->getGame()->StopGame(true);
        }
        if(e->getKey() == 102){ // F
            this->cam->SetEulerRotation(glm::vec3(0.0f, 0.0f, 0.0f));
            rotx = 0;
            roty = 0;
            rotz = 0;
        }



    }
    void gameGUI(Events::WindowEventDetails* events){
        //std::cout << "Rend  1!" << std::endl;
        events->getDisplay()->Clear(0.0f,1.0f,0.5f,1.0f);


        t->GetPos().x = sinf(ff);
        t->SetRot(glm::vec3(cosf(ff),cosf(ff),cosf(ff) ));

        te->Bind(0);
        s->Bind();
        s->Update(*t, *cam);
        m2->DrawMesh();



        t->GetPos().x += 3;
        t->GetPos().z += 50;
        t1->Bind(0);
        s->Bind();
        s->Update(*t, *cam);
        m1->DrawMesh();


        t->GetPos().x -= 3;
        t->GetPos().z -= 50;


    }
    void gameTick(Events::TimedEventDetails* e){
        //std::cout << "Tick  1!" << std::endl;
        //ff += 0.01f;
    }

};

extern int IGNORE_OPENGL_VERSION;
int main() {
	IGNORE_OPENGL_VERSION = 1;
    Engine::GameManager gl = Engine::GameManager();
    Events::EventDispatcher* ee = Events::EventDispatcher::instance();
    gl.CreateWindow("Test2", 1000, 600);
    Display* aa = gl.getWindow();
    L l(aa);
    aa->RegisterWindowListener(&l, Events::Priority::MEDIUM);
    ee->RegisterTickListener(&l, Events::Priority::HIGH);
    ee->RegisterMouseListener(&l, Events::Priority::MEDIUM);
    ee->RegisterKeyListener(&l, Events::Priority::MEDIUM);
    gl.getOptions()->setTickRateTarget(30);
    aa->GetWindowOptions()->setFrameRateTarget(20);
    aa->ShowWindow();
    gl.StartGame(false); // Set game unpaused

}

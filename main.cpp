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
/*
	This file shall serve as a "demo" to how to use the engine.
	
	This shows how to use the event listener, and how to interact with the
	game manager.


*/


class L : public Listener::GameGUIListener, public Listener::GameTickListener, public Listener::GameMouseListener, public Listener::GameKeyboardListener{
public:
	// Required objects for rendering items
    Vertex** v;
    unsigned int* ind;
    Transform* t; // Rendering offset for models, change before everytime you render a model
    Camera* cam; // Camera, global transformation for models, change before rendering at all
    Shader* s; // Shader, changes how the textures are applied to models.
    Textures* te; // Texture 1
    Textures* t1; // Texture 2
    Mesh* m1; // Mesh 1 (object 1)
    Mesh* m2; // Mesh 2 (object 2)
    // Floats representing the camera rotation and position vectors
	float rotx;
    float roty;
    float rotz;
    float posx;
    float posy;
    float posz;
	// A time float for making the meshes rotate/move over time
    float ff;
	
    L(Display* d){
        ff = 0;
        rotx = 0;
        roty = 0;
        rotz = 0;
        posx = 1;
        posy = 0;
        posz = 5;
		// Creating a mesh from verticies
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

		// Creating a new transform
        t = new Transform( glm::vec3(0.0,.3,0.5), /*pos*/
                             glm::vec3(0,0,0), /*rot*/
                             glm::vec3(0,0,0));/*scl*/

        float aspectratio = (d->GetWidthf()/d->GetHeightf());
        std::cout << aspectratio << "aspect ratio " <<std::endl;
		// Creating the camera
        cam = new Camera(glm::vec3(1,0,5), 70.0f, aspectratio, 0.01f, 1000.0f);
		// Creating the shader, will compile the passed shader scripts on runtime
        s = new Shader("./glfiles/shaders/testshader");
		// Load the given textures and object files.
        te = new Textures("./glfiles/textures/illuminati.jpg");
        t1 = new Textures("./glfiles/textures/pizza.jpg");
        m1 = new Mesh("./glfiles/obj/s.obj");
        m2 = new Mesh("./glfiles/obj/Crate1.obj");

    }
	// Event Listener callback functions.
    void gameMouseButtonPressed(Events::MouseButtonEventDetails* event){
        std::cout << "Mouse P" << std::endl;
    }
    void gameMouseButtonReleased(Events::MouseButtonEventDetails* e){
        std::cout << "Mouse R" << std::endl;

    }
    void gameMouseMoved(Events::MouseButtonEventDetails* e){
        std::cout << "Mouse M " << e->getMousePosition() << " " << e->getDeltaMousePosition()<< std::endl;
		// Allow the user to change the left-right rotation of the camera when the left
		// mouse button is pressed down
        if(e->isButtonLDown()) {
            roty += e->getDeltaMousePosition().getX() / 100.0f;
            //rotx -= glm::cos(roty) * e->getDeltaMousePosition().getY() / 120.0f;
            //rotz += glm::sin(roty) * e->getDeltaMousePosition().getY() / 120.0f;
            this->cam->SetEulerRotation(glm::vec3(rotx, roty, rotz));
        }

    }
    void gameKeyPressed(Events::KeyboardEventDetails* e){
        std::cout << "Key P " << e->getKey() << std::endl;
		// Perform some action when a key is pressed down/held down.
		// Namely either add some specific offset to rotation (G,H,I)
		// or move left/right/up/down/forward/back based on up down left right and page up/down
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
        if(e->getKey() == 1073741906){ // Up arrow
            //posz -= 0.1f;
            this->cam->MoveRelativeToView(glm::vec3(0, 0, -0.1f));
        }
        if(e->getKey() == 1073741905){ // Down arrow
            //posz += 0.1f;
            this->cam->MoveRelativeToView(glm::vec3(0, 0, +0.1f));
        }
        if(e->getKey() == 1073741904){ // Left arrow
            //posx -= 0.1f;
            this->cam->MoveRelativeToView(glm::vec3(-0.1f,0,0));
        }
        if(e->getKey() == 1073741903){ // Right arrow
            //posx += 0.1f;
            this->cam->MoveRelativeToView(glm::vec3(0.1f,0,0));
        }
        if(e->getKey() == 1073741899){ // PageUp
            //posy += 0.1f;
            this->cam->MoveRelativeToView(glm::vec3(0, 0.1f,0));
        }
        if(e->getKey() == 1073741902){ // PageDown
            //posy -= 0.1f;
            this->cam->MoveRelativeToView(glm::vec3(0, -0.1f,0));
        }
    }
	// Add key events here if you want them to fire once on release.
    void gameKeyReleased(Events::KeyboardEventDetails* e){
        std::cout << "Key R " << e->getKey() << std::endl;
        if(e->getKey() == 100){
			// This pauses the tick events for the game
            e->getGame()->PauseGame();
        }
        if(e->getKey() == 101){
			// This resumes the tick events for the game.
            e->getGame()->ResumeGame();
        }
        if(e->getKey() == 113){
			// This stops the game, causing it to quit.
            e->getGame()->StopGame(true);
        }
        if(e->getKey() == 102){ // F
			// This resets the rotation of the camera.
            this->cam->SetEulerRotation(glm::vec3(0.0f, 0.0f, 0.0f));
            rotx = 0;
            roty = 0;
            rotz = 0;
        }



    }
	// Events here happen every time a frame is being rendered, make sure
	// to render models here.
    void gameGUI(Events::WindowEventDetails* events){
        //std::cout << "Rend  1!" << std::endl;
        events->getDisplay()->Clear(0.0f,1.0f,0.5f,1.0f);

		// Do some transformations to the model to make them dynamic
        t->GetPos().x = sinf(ff);
        t->SetRot(glm::vec3(cosf(ff),cosf(ff),cosf(ff) ));

		// Draw the first model (the box)
        te->Bind(0);
        s->Bind();
        s->Update(*t, *cam);
        m2->DrawMesh();



        t->GetPos().x += 3;
        t->GetPos().z += 50;
		// Draw the second model behind the user, (the pizza person)
        t1->Bind(0);
        s->Bind();
        s->Update(*t, *cam);
        m1->DrawMesh();


        t->GetPos().x -= 3;
        t->GetPos().z -= 50;
		// Ensure that the position isn't modified after the funtion ends.

    }
    void gameTick(Events::TimedEventDetails* e){
        //std::cout << "Tick  1!" << std::endl;
        //ff += 0.01f;
    }

};
// For apple users, use the below to silence a warning that may 
// be due to outdated (and yet functional) opengl version.
extern int IGNORE_OPENGL_VERSION;
int main() {
	IGNORE_OPENGL_VERSION = 1;
	
	// Create a new gamemanager
    Engine::GameManager gl = Engine::GameManager();
	// Get the event dispatcher class
    Events::EventDispatcher* ee = Events::EventDispatcher::instance();
	// Create a new window (it is hidden by default)
    gl.CreateWindow("Test2", 1000, 600);
	// Get the display pointer for the window
    Display* aa = gl.getWindow();
	// Create our new event listener class
    L l(aa);
	// Register the event for almost every event (missing game events)
    aa->RegisterWindowListener(&l, Events::Priority::MEDIUM);
    ee->RegisterTickListener(&l, Events::Priority::HIGH);
    ee->RegisterMouseListener(&l, Events::Priority::MEDIUM);
    ee->RegisterKeyListener(&l, Events::Priority::MEDIUM);
	// Set the tick rate and frame rate of the game&window
    gl.getOptions()->setTickRateTarget(30);
    aa->GetWindowOptions()->setFrameRateTarget(20);
	// Show the window, starting rendering events
    aa->ShowWindow();
	// Start the game, leave it unpaused.
    gl.StartGame(false); 
	// This thread will block (managing the game loop) until the game ends, then 
	// you can do deconstructor things down here after calling start Game.

}

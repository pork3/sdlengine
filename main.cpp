#include "./core/GameManager.hpp"
#include "./rendering/Window.hpp"
#include <chrono>
#include <thread>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "./events/Listeners.hpp"



class windHand : public Listener::GameGUIListener {
public:
    int fc = 0;
    void gameGUI(Events::WindowEventDetails* e){
        fc++;
        cout << fc << endl;
        Window* ww = e->getWindow();
        //ww->Clear(1.0f,1.0f,1.0f,1.0f);
        ww->Clear((static_cast<float>(fc % 10)+1.0f)/10.0f,0.2f,1.0f,1.0f);
        /*glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_TRIANGLES);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 0.0f);
        glEnd();*/
    }

};




int main(int argc , char** argv){

    Engine::GameManager* t = Engine::GameManager::instance();

    Window* w = t->CreateWindow("Test", 800, 600); // Window IS INITIALLY HIDDEN
    std::cout << w << endl;
    windHand ww;
    w->RegisterWindowListener(&ww, Events::Priority::HIGHEST);
    Management::WindowOptions* windOpts = w->GetWindowOptions();
    windOpts->setFrameRateTarget(60);
    t->StartGame(false);
    w->ShowWindow();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    w->HideWindow();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    w->ShowWindow();
    windOpts->setFrameRateTarget(60);
    std::this_thread::sleep_for(std::chrono::milliseconds(200000));
    t->StopGame(true);
    t->WaitForGameEnd();
    return 0;
}

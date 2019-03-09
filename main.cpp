#include "./core/GameManager.hpp"
#include "./rendering/Window.hpp"
#include <chrono>
#include <thread>
#include <iostream>

int main(int argc , char** argv){

    Engine::GameManager* t = Engine::GameManager::instance();

    Window* w = t->CreateWindow("Test", 800, 600); // Window IS INITIALLY HIDDEN

    Management::WindowOptions* windOpts = w->GetWindowOptions();
    windOpts->setFrameRateTarget(2);
    t->StartGame(false);
    w->ShowWindow();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    w->HideWindow();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    w->ShowWindow();
    windOpts->setFrameRateTarget(5);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    t->StopGame(true);
    t->WaitForGameEnd();
    return 0;
}

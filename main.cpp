#include "./core/GameManager.hpp"
#include "./rendering/Window.hpp"
#include <chrono>
#include <thread>
#include <iostream>

int main(int argc , char** argv){

    Engine::GameManager* t = Engine::GameManager::instance();
    Window* w = t->CreateWindow("Test", 800, 600); // Window IS INITIALLY HIDDEN
    w->ShowWindow();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    w->HideWindow();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    w->ShowWindow();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    return 0;
}

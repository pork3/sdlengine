#include "./core/GameManager.hpp"
#include "./rendering/Window.hpp"

#include <iostream>
class test : public  Engine::GameManager{
public:
    test(){};

};


int main(int argc , char** argv){

    test t = test();
    t.CreateWindow("Test", 800, 600);

    int r;
    std::cin >> r ;

    return 0;
}
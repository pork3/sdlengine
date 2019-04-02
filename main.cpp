#include <iostream>
#include "./platform/RenderedApplication.hpp"
#include "platform/Window.hpp"

// For apple users, use the below to silence a warning that may
// be due to outdated (and yet functional) opengl version.
extern int IGNORE_OPENGL_VERSION;

int main() {

    RenderedApplication* ra = RenderedApplication::CreateApplication();
    Window w(*ra,600,800, "test");

    while(1){

    }

}

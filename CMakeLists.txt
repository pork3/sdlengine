cmake_minimum_required(VERSION 3.13)
project(sdlengine)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/opengl)
include_directories(src/sdlsrc)

add_executable(sdlengine
        src/opengl/render.cpp
        src/opengl/render.h
        src/sdlsrc/Event.cpp
        src/sdlsrc/Event.h
        src/sdlsrc/window.cpp
        src/sdlsrc/window.h
        src/GameLoop.cpp
        src/GameLoop.h
        src/main.cpp
        makefile
        README.md)

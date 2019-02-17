cmake_minimum_required(VERSION 3.13)
#project name
project(engine)

#c++ 14 and debugsymbols
set(CMAKE_CXX_STANDARD 14)
add_definitions("-g -Wall")

#create the executable
add_executable(${PROJECT_NAME} main.cpp sdlfiles/Display.cpp sdlfiles/Display.h GameLoop.cpp GameLoop.h err/Error.cpp err/Error.h sdlfiles/Event.cpp sdlfiles/Event.h glfiles/Mesh.cpp glfiles/Mesh.h glfiles/Shader.cpp glfiles/Shader.h glfiles/Textures.cpp glfiles/Textures.h
        lib/stb_image.c lib/stb_image.h)

target_link_libraries(${PROJECT_NAME} "-lSDL2 -lGL -lGLEW")

#sdl2 opengl glm





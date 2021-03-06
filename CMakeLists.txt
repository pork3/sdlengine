#use the minimum most compatible version
cmake_minimum_required(VERSION 2.6)

#project name
project(engine)

#add compiler flags
add_definitions(
        -c
        -g
)
#find header files, for later distribution as library (.so)
file(GLOB_RECURSE HDRS ${engine_SOURCE_DIR}/*.h
        ${engine_SOURCE_DIR}/*.hpp)
#find source files
file(GLOB_RECURSE SRCS
        ${engine_SOURCE_DIR}/core/*.cpp
        ${engine_SOURCE_DIR}/events/*.cpp
        ${engine_SOURCE_DIR}/lib/*.cpp
        ${engine_SOURCE_DIR}/rendering/*.cpp
        ${engine_SOURCE_DIR}/utils/*.cpp
        ${engine_SOURCE_DIR}/math/*.cpp
        ${engine_SOURCE_DIR}/sdlfiles/*.cpp
        ${engine_SOURCE_DIR}/glfiles/*.cpp


        ${engine_SOURCE_DIR}/lib/*.c
        )

# Define the executable
add_executable(engine ${HDRS} ${SRCS} err/Error.hpp err/Error.cpp core/GameManager.cpp core/GameManager.h main.cpp Transform.cpp Transform.h Camera.cpp Camera.h)

# We need a CMAKE_DIR with some code to find external dependencies
SET(engine_CMAKE_DIR "${engine_SOURCE_DIR}/cmake")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

######################FIND REQUIRED PACKAGES

#set openglpreference to get newest it finds
set(OpenGL_GL_PREFERENCE GLVND)
# OpenGL
find_package(OpenGL REQUIRED)

# GLEW
INCLUDE(${engine_CMAKE_DIR}/FindGlew.cmake)

# SDL2
INCLUDE(${engine_CMAKE_DIR}/FindSDL2.cmake)

#pthread
find_package (Threads)


# Define the include DIRs
include_directories(
        ${engine_SOURCE_DIR}/headers
        ${engine_SOURCE_DIR}/sources
        ${OPENGL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIRS}
)

# Define the link libraries
target_link_libraries( engine
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${SDL2_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        )

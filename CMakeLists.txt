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
        ${engine_SOURCE_DIR}/*.CXX
        ${engine_SOURCE_DIR}/core/*.cpp
        ${engine_SOURCE_DIR}/err/*.cpp
        ${engine_SOURCE_DIR}/events/*.cpp
        ${engine_SOURCE_DIR}/lib/*.cpp
        ${engine_SOURCE_DIR}/rendering/*.cpp
        ${engine_SOURCE_DIR}/utils/*.cpp
        ${engine_SOURCE_DIR}/lib/*.c

        )

# Define the executable
add_executable(engine ${HDRS} ${SRCS} utils/Settings.cpp utils/Settings.hpp rendering/Window.cpp
 rendering/Window.hpp core/GameManger.cpp utils/GameOptions.hpp utils/Utils.hpp main.cpp events/InputHandler.cpp
  events/InputHandler.hpp events/InputEvent.cpp events/InputEvent.h rendering/RenderCore.cpp
   rendering/RenderCore.hpp core/EntityShared.hpp)

# We need a CMAKE_DIR with some code to find external dependencies
SET(engine_CMAKE_DIR "${engine_SOURCE_DIR}/cmake")

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


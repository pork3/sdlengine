# 422 - Panda Engine

Panda Engine is a 2D/3D game engine that is capable of managing most processes related to building a videogame.

### Panda offers many features such as:

- Create and Display a window

- Display the background

- Create an object in a specified location

- Assign textures to the object

- Runs internals in well under 500 ms 

- For more details, please check our project documentation: 

https://docs.google.com/document/d/1DK6dYiLc_Q-LdQCKlGzZRqJNqOuw3fx-PC_2qWnJovQ/edit#heading=h.ss2aglc4rymd

## Author 

- Zachary Bower

- Chase Craig

- Linshu Huang

- Benjamin Yin

- Luyao Wang


## Installation 

Our engine is runnable on MacOS and Windows.

It is implemented in C++ 11 and various libraries and systems such as:

- OpenGL 3.0 or newer*

- GCC 4.8 or newer

- SDL

\*:OpenGL 2.1 may work, however it is not officially supported.

For more detials, please check our user guide:

https://docs.google.com/document/d/1-DKFmecn8fAYTDddtEsXq87vIHSOzJVQIl15kWUTk1Y/edit

## Prototype 

- A Rotating Box

- A static pizza man and his box 

For more details, please check our demo guide:

https://docs.google.com/document/d/1YBW0K1uobM-jCOjjdg-o60lzdgbmaSe_dAnYDWog8oE/edit

## File Structure

Our engine is seperated into sections regarding each model, some classes are present in non-official locations, they are being migrated over in the next few updates.

sdlengine

  ->.gitignore
  
  ->README.md
  
  ->CMakeLists.txt
  
  ->main.cpp
  
  ->\*Camera.cpp
  
  ->\*Camera.h
  
  ->\*Transform.cpp
  
  ->\*Transform.h
  
  ->cmake    - Contains files for automated building and running of the project
  
   ->->FindGlew.cmake
    
   ->->FindSDL2.cmake
    
   ->->README.md
  
  ->core     - Contains files for managing the game engine, other non-specialized but still core files go here
  
  ->err      - Contains files for reporting/logging events/errors in the game. They are saved in this folder as error.log
  
  ->events   - Contains files for managing the event listeners and event dispatching.
  
  ->glfiles  - Contains files for handling the object, textures and shader
  
  ->lib      - Contains files for managing different public domain image loaders  
  
  ->sdlfiles - Contains files for creating a SDL2 window to display to the third party user.
  
  ->math     - Contains files for providing useful data structures for performing normal game calculations 
  
  ->utils    - Contians files for managing the useful utility objects that can perform quick and redundant calculations.
    

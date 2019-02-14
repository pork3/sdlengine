#Compiler flag
CC = g++
#linker flags LSDL2(sdl2)
LDFLAGS = -lSDL2 -lX11 -lGL -lGLU
#compiler flags
CCFLAGS = -g -Wall
#all object files needed
OBJECTS = GameLoop.o main.o Window.o

#g++ GameLoop.cpp GameLoop.h main.cpp sdlsrc/window.cpp sdlsrc/window.h -lSDL2 -lX11 -lGL -lGLEW

GameLoop.o: ./src/GameLoop.cpp ./src/GameLoop.h
	$(CC) -o GameLoop.o $^ 
Window.o: ./src/sdlsrc/window.cpp ./src/sdlsrc/window.h
	$(CC) -o Window.o  $^
main.o: ./src/main.cpp
	$(CC)  -o main.o $@ 

#name of binary to produce
BINNAME = swag

#Targets
all : $(OBJECTS)
		$(CC) $(OBJECTS) $(CCFLAGS) $(LDFLAGS) -o $(BINNAME)

#remove all objects
clean : 
	rm -f *~$(BINNAME) $(OBJECTS)
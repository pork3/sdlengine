#variable to hold all files wish to compile
objs = src/main.c src/window/window.h src/window/window.c src/settings.h

#compiler option
cc = gcc
#compiler flags g(debug symbols)
cc_flags = -g -W -Wall

#linker flags LSDL2(sdl2)
ld_flags = -lSDL2

#name of binary to produce
bin_name = swag

#Targets
all : $(objs)
		$(CC) $(objs) $(cc_flags) $(ld_flags) -o $(bin_name)

#remove all objects
clean : 
	rm -f *~$(bin_name)
# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/JetBrains/apps/CLion/ch-0/183.5429.37/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/JetBrains/apps/CLion/ch-0/183.5429.37/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zach/Desktop/cis422

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zach/Desktop/cis422/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/engine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/engine.dir/flags.make

CMakeFiles/engine.dir/main.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zach/Desktop/cis422/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/engine.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/main.cpp.o -c /home/zach/Desktop/cis422/main.cpp

CMakeFiles/engine.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zach/Desktop/cis422/main.cpp > CMakeFiles/engine.dir/main.cpp.i

CMakeFiles/engine.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zach/Desktop/cis422/main.cpp -o CMakeFiles/engine.dir/main.cpp.s

CMakeFiles/engine.dir/sdlfiles/Display.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/sdlfiles/Display.cpp.o: ../sdlfiles/Display.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zach/Desktop/cis422/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/engine.dir/sdlfiles/Display.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/sdlfiles/Display.cpp.o -c /home/zach/Desktop/cis422/sdlfiles/Display.cpp

CMakeFiles/engine.dir/sdlfiles/Display.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/sdlfiles/Display.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zach/Desktop/cis422/sdlfiles/Display.cpp > CMakeFiles/engine.dir/sdlfiles/Display.cpp.i

CMakeFiles/engine.dir/sdlfiles/Display.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/sdlfiles/Display.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zach/Desktop/cis422/sdlfiles/Display.cpp -o CMakeFiles/engine.dir/sdlfiles/Display.cpp.s

CMakeFiles/engine.dir/GameLoop.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/GameLoop.cpp.o: ../GameLoop.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zach/Desktop/cis422/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/engine.dir/GameLoop.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/GameLoop.cpp.o -c /home/zach/Desktop/cis422/GameLoop.cpp

CMakeFiles/engine.dir/GameLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/GameLoop.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zach/Desktop/cis422/GameLoop.cpp > CMakeFiles/engine.dir/GameLoop.cpp.i

CMakeFiles/engine.dir/GameLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/GameLoop.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zach/Desktop/cis422/GameLoop.cpp -o CMakeFiles/engine.dir/GameLoop.cpp.s

CMakeFiles/engine.dir/err/Error.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/err/Error.cpp.o: ../err/Error.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zach/Desktop/cis422/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/engine.dir/err/Error.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/err/Error.cpp.o -c /home/zach/Desktop/cis422/err/Error.cpp

CMakeFiles/engine.dir/err/Error.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/err/Error.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zach/Desktop/cis422/err/Error.cpp > CMakeFiles/engine.dir/err/Error.cpp.i

CMakeFiles/engine.dir/err/Error.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/err/Error.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zach/Desktop/cis422/err/Error.cpp -o CMakeFiles/engine.dir/err/Error.cpp.s

CMakeFiles/engine.dir/sdlfiles/Event.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/sdlfiles/Event.cpp.o: ../sdlfiles/Event.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zach/Desktop/cis422/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/engine.dir/sdlfiles/Event.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/sdlfiles/Event.cpp.o -c /home/zach/Desktop/cis422/sdlfiles/Event.cpp

CMakeFiles/engine.dir/sdlfiles/Event.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/sdlfiles/Event.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zach/Desktop/cis422/sdlfiles/Event.cpp > CMakeFiles/engine.dir/sdlfiles/Event.cpp.i

CMakeFiles/engine.dir/sdlfiles/Event.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/sdlfiles/Event.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zach/Desktop/cis422/sdlfiles/Event.cpp -o CMakeFiles/engine.dir/sdlfiles/Event.cpp.s

# Object files for target engine
engine_OBJECTS = \
"CMakeFiles/engine.dir/main.cpp.o" \
"CMakeFiles/engine.dir/sdlfiles/Display.cpp.o" \
"CMakeFiles/engine.dir/GameLoop.cpp.o" \
"CMakeFiles/engine.dir/err/Error.cpp.o" \
"CMakeFiles/engine.dir/sdlfiles/Event.cpp.o"

# External object files for target engine
engine_EXTERNAL_OBJECTS =

engine: CMakeFiles/engine.dir/main.cpp.o
engine: CMakeFiles/engine.dir/sdlfiles/Display.cpp.o
engine: CMakeFiles/engine.dir/GameLoop.cpp.o
engine: CMakeFiles/engine.dir/err/Error.cpp.o
engine: CMakeFiles/engine.dir/sdlfiles/Event.cpp.o
engine: CMakeFiles/engine.dir/build.make
engine: CMakeFiles/engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zach/Desktop/cis422/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable engine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/engine.dir/build: engine

.PHONY : CMakeFiles/engine.dir/build

CMakeFiles/engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/engine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/engine.dir/clean

CMakeFiles/engine.dir/depend:
	cd /home/zach/Desktop/cis422/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zach/Desktop/cis422 /home/zach/Desktop/cis422 /home/zach/Desktop/cis422/cmake-build-debug /home/zach/Desktop/cis422/cmake-build-debug /home/zach/Desktop/cis422/cmake-build-debug/CMakeFiles/engine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/engine.dir/depend

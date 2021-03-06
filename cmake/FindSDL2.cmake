SET( SDL2_SEARCH_PATHS
        ${SDL2_ROOT_DIR}					# SDL2!
        ./lib/SDL2
        $ENV{PROGRAMFILES}/SDL2				# WINDOWS
        ~/Library/Frameworks				# MAC
        /Library/Frameworks					# MAC
        /usr/local							# LINUX/MAC/UNIX
        /usr								# LINUX/MAC/UNIX
        /opt								# LINUX/MAC/UNIX
        )

FIND_PATH( SDL2_INCLUDE_DIRS
        NAMES
        SDL.h SDL2/SDL.h
        PATHS
        ${SDL2_SEARCH_PATHS}
        PATH_SUFFIXES
        include
        DOC
        "The directory where SDL.h resides"
        )

FIND_LIBRARY( SDL2_LIBRARIES
        NAMES
        SDL2 SDL2main
        PATHS
        ${SDL2_SEARCH_PATHS}
        PATH_SUFFIXES
        lib
        lib64
        lib/x86
        lib/x64
        DOC
        "The SDL2 library"
        )

# Check if we found it!
IF ( SDL2_INCLUDE_DIRS AND SDL2_LIBRARIES )
    SET( SDL2_FOUND TRUE )
    MESSAGE(STATUS "FOUND SDL2")
ELSE ( SDL2_INCLUDE_DIRS AND SDL2_LIBRARIES )
    SET( SDL2_FOUND FALSE )
    MESSAGE(STATUS "DID NOT FIND SDL2")
ENDIF ( SDL2_INCLUDE_DIRS AND SDL2_LIBRARIES )
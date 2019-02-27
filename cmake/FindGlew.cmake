SET( GLEW_SEARCH_PATHS
        ${GLEW_ROOT_DIR}
        ./lib/glew
        ~/Library/Frameworks				# MAC
        /Library/Frameworks					# MAC
        /usr/local							# LINUX/MAC/UNIX
        /usr								# LINUX/MAC/UNIX
        /opt								# LINUX/MAC/UNIX
        )

FIND_PATH( GLEW_INCLUDE_DIRS
        NAMES
        GL/glew.h
        PATHS
        ${GLEW_SEARCH_PATHS}
        PATH_SUFFIXES
        include
        DOC
        )

FIND_LIBRARY( GLEW_LIBRARIES
        NAMES
        glew GLEW libGLEW.a glew32 glew32s
        PATHS
        ${GLEW_SEARCH_PATHS}
        PATH_SUFFIXES
        lib
        lib64
        lib/Release/Win32
        lib/Release/x64
        DOC
        )

# Check if we found it!
IF ( GLEW_INCLUDE_DIRS AND GLEW_LIBRARIES )
    SET( GLEW_FOUND TRUE )
    MESSAGE( STATUS "GLEW FOUND" )
ELSE ( GLEW_INCLUDE_DIRS AND GLEW_LIBRARIES )
    SET( GLEW_FOUND FALSE )
    MESSAGE( STATUS "GLEW NOT FOUND" )
ENDIF ( GLEW_INCLUDE_DIRS AND GLEW_LIBRARIES )
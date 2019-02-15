#ifndef _INCLUDED_RENDER_H
#define _INCLUDED_RENDER_H

/*SDL is a C library so add as extern C*/
extern "C"{

	#include <SDL2/SDL.h>
}
#include<GL/glew.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
#include <string>

/*class to sets up the 'background' window to be dislayed
and draws on it
	

*/

class Render{

	public:
		Render();


	private:
		float red;
		float green;
		float blue;
		float alpha;
	

};



#endif
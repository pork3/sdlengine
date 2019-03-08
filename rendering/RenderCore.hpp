#ifndef ENGINE_RENDERCORE_H
#define ENGINE_RENDERCORE_H
// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 *
 *	Last updated by: Zachary Bower
 *	Last updated on: Mar 3, 2019
 *
 *	Purpose:
 *		This class contains the main logic to render everything on screen. This class
 *		is where shaders, lighting, models, the camera all come together.
 *
 *     TODO:
 *     ADD options to toggle FPS
 *     Test shader location and texture location
 *     ADD lighting
 *
 *
 */
#include "Window.hpp"
#include "Camera.h"
#include "../core/Transform.h"
#include "Mesh.h"
#include "Shader.h"
#include <SDL2/SDL.h>

class RenderCore {

public:
                /*the main window we wish to draw on*/
    RenderCore(Window& w);

    ~RenderCore();

    /*Note this will take an entity * later on*/
    void Render();

    void SetVert(Vertex v[]);

    void SetCamer(const Camera& camera);

private:

    /*matrix used during lighting and texture mapping to change -1 and 1 values to
     * 0 and 1 values used by opengl
     * http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping/#using-the-shadow-map*/
    const glm::mat4 biasMatrix = glm::mat4(0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0);

    Camera* camera;
    Window& window;

    Shader*  defshader = nullptr;

    Mesh* m;
    SDL_GLContext context;

    Transform* transform;

};


#endif //ENGINE_RENDERCORE_H

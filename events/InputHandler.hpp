#ifndef ENGINE_INPUTHANDLER_H
#define ENGINE_INPUTHANDLER_H


#include <tiff.h>

class InputHandler {

public:
    InputHandler();
    virtual ~InputHandler();

    virtual void OnKeyDown( uint32 key , bool repeated );
    virtual  void OnKeyUp(uint32 key , bool repeated );
    virtual void OnMouseDown(uint32 key , uint8 clicks );
    virtual void OnMouseUp(uint32 key , uint8 clicks );
    virtual void OnMouseMotion(int32 x , int32 y, int32 dx , int32 dy );

};


#endif //ENGINE_INPUTHANDLER_H

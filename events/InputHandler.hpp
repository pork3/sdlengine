#ifndef ENGINE_INPUTHANDLER_H
#define ENGINE_INPUTHANDLER_H

#include <cstdint>

class InputHandler {

public:
    InputHandler();
    virtual ~InputHandler();

    virtual void OnKeyDown( uint32_t key , bool repeated );
    virtual  void OnKeyUp(uint32_t key , bool repeated );
    virtual void OnMouseDown(uint32_t key , uint8_t clicks );
    virtual void OnMouseUp(uint32_t key , uint8_t clicks );
    virtual void OnMouseMotion(int32_t x , int32_t y, int32_t dx , int32_t dy );

};


#endif //ENGINE_INPUTHANDLER_H

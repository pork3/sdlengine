#ifndef ENGINE_INPUTHANDLER_H
#define ENGINE_INPUTHANDLER_H

#include <cstdint>

class InputHandler {

public:

    virtual void OnKeyDown( uint32_t key , bool repeated ) = 0;
    virtual  void OnKeyUp(uint32_t key , bool repeated ) = 0;
    virtual void OnMouseDown(uint32_t key , uint8_t clicks ) = 0;
    virtual void OnMouseUp(uint32_t key , uint8_t clicks ) = 0;
    virtual void OnMouseMotion(int32_t x , int32_t y, int32_t dx , int32_t dy ) = 0;



};


#endif //ENGINE_INPUTHANDLER_H

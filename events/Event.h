#ifndef ENGINE_EVENT_H
#define ENGINE_EVENT_H
/*class to handle events*/


#include <SDL2/SDL.h>


class Event{

        public:
        Event();
        ~Event();

        SDL_Event* GetEvent(){return this->evnt;}


        private:

        SDL_Event* evnt;

};


#endif //ENGINE_EVENT_H

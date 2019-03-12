
#ifndef GAME_LISTENERS_H_
#define GAME_LISTENERS_H_

// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 	Last updated by: Chase Craig
 	Last updated on: Mar. 11, 2019
 
 	Purpose:
 		This header class is to provide base classes for a game script to register event handlers/
 			intercepters for game events executed by the game engine.
 
 	Conventions:
 		Classes and Namespaces should have every word Capitalized with no _
 		Functions should have their first word lowercase, all other words are Capitalized, no _
 			Exceptions: Constructors and Destructors must match the class name exactly.
 		Parameters should be all lowercase with _ seperating words
 
   	Functions without comments are assumed to be a single line, set or get a single variable, and the
 		comment is to be found next to the respective variable definition.
 
	Notes:
		The known event ID's:
			0: Game starting event
			1: Game stopping event
			2: Game logic/computation event
			3: Window rendering event
			4: Keyboard key pressed event
			5: Keyboard key released event
			6: Mouse button pressed event
			7: Mouse button released event
			8: Mouse moved event
 */

// General includes
#include <string>
#include <chrono>
#include <SDL2/SDL.h>
#include <iostream>
#include <GL/glew.h>

#include "../math/EngineMath.hpp"
// Forward declare the GameManager class.
namespace Engine{class GameManager;}

// Use the Engine namespace.
using namespace Engine;

// Forward declare the Display class.
class Display;
namespace Events{
    class EventDispatcher;
    enum Priority {HIGHEST=5, HIGH=4, MEDIUM=3, LOW=2, LOWEST=1};
    class EventDetails{
    protected:
        // Note: Sections below are redundant as the events are seperated into group
        Engine::GameManager* game;
        bool is_cancelled; // Is the event cancelled
        std::string event_name; // Name of event (semi-redundant)
        int event_id; // The ID of the event (semi-redundant)
        bool is_cancellable; // Can the event be cancelled
        std::chrono::high_resolution_clock::time_point currentGameTime; // The current game time
        std::chrono::high_resolution_clock::time_point startGameTime; // The
    public:
        EventDetails(GameManager* g, std::string event_n, int id, bool is_canc,std::chrono::high_resolution_clock::time_point currentTime,
                std::chrono::high_resolution_clock::time_point startTime ) : game(g),is_cancelled(false),  event_name(event_n),
                event_id(id),is_cancellable(is_canc), currentGameTime(currentTime), startGameTime(startTime) {}

        friend class Events::EventDispatcher;
        GameManager* getGame(){return game;}
        bool isCancelled(){return this->is_cancelled;}
        bool isCancellable(){return this->is_cancellable;}

        std::string getName(){return this->event_name;}
        int getID(){return this->event_id;}

        std::chrono::high_resolution_clock::time_point getCurrentGameTime(){return this->currentGameTime;}
        std::chrono::high_resolution_clock::time_point getStartGameTime(){return this->startGameTime;}

        // Tries to cancel the event, returns success, fails if not cancellable
        bool cancel(){
            if(this->is_cancellable){
                this->is_cancelled = true;
                return true;
            }else{
                return false;
            }
        }

        // Uncancels the event.
        // NOTE: Events cancelled will not execute beyond the current event's priority
        // 	level. Hence, it must be uncancelled by an event in the same priority
        // 	level as the event that cancelled it.
        void uncancel(){
            this->is_cancelled = false;

        }

    };

    class TimedEventDetails : public EventDetails{
    protected:
        long long eventTimeDelta;
        long long eventTimeDeltaExact;
    public:
        TimedEventDetails(GameManager* g, std::string event_n, int id, bool is_canc,std::chrono::high_resolution_clock::time_point currentTime, std::chrono::high_resolution_clock::time_point startTime,
                          long long timeDelta,long long timeDeltaNow): EventDetails(g, event_n, id, is_canc, currentTime, startTime), eventTimeDelta(timeDelta),
                                                                       eventTimeDeltaExact(timeDeltaNow){}

        friend class EventDispatcher;
        long long getEventTimeDeltaExact(){return this->eventTimeDeltaExact;}
        long long getEventTimeDelta(){return this->eventTimeDelta;}


    };

    class WindowEventDetails : public TimedEventDetails{
    protected:
        Display* win;
    public:
        WindowEventDetails(GameManager* g, std::string event_n, int id, bool is_canc,std::chrono::high_resolution_clock::time_point currentTime, std::chrono::high_resolution_clock::time_point startTime,
        long long timeDelta,long long timeDeltaNow, Display* w): TimedEventDetails(g, event_n, id, is_canc, currentTime, startTime, timeDelta,timeDeltaNow), win(w){}


        Display* getDisplay(){return this->win;}

    };

    class MouseButtonEventDetails : public EventDetails {
    protected:
        /*
            Mouse Button ID:
                0 = No button (mouse moved event)
                1 = Button Left
                2 = Button Right
                3 = Button Middle
                4 = Button X1
                5 = Button X2
        */
        int mouseButton;
        Math::Vector2Int mousePos;
        Math::Vector2Int deltaMousePos;
        SDL_Keymod keyMods;
        int numClicks;
    public:
        MouseButtonEventDetails(GameManager* g, std::string event_n, int id, bool is_canc,std::chrono::high_resolution_clock::time_point currentTime, std::chrono::high_resolution_clock::time_point startTime,
            int mouseB, Math::Vector2Int mouseP, Math::Vector2Int deltaMP, int numcl, SDL_Keymod keym) : EventDetails(g, event_n,id, is_canc, currentTime, startTime),mouseButton(mouseB),
            mousePos(mouseP), deltaMousePos(deltaMP), keyMods(keym), numClicks(numcl){}

        bool isButtonLDown(){return mouseButton & SDL_BUTTON_LMASK;}
        bool isButtonRDown(){return mouseButton & SDL_BUTTON_RMASK;}
        bool isButtonMDown(){return mouseButton & SDL_BUTTON_MMASK;}
        bool isButtonX1Down(){return mouseButton & SDL_BUTTON_X1MASK;}
        bool isButtonX2Down(){return mouseButton & SDL_BUTTON_X2MASK;}
        int getAllMouseButtons(){return mouseButton;}
        Math::Vector2Int getMousePosition(){return mousePos;}
        Math::Vector2Int getPreviousMousePosition(){return Math::Vector2Int(mousePos - deltaMousePos);}
        Math::Vector2Int getDeltaMousePosition(){return deltaMousePos;}
        SDL_Keymod getKeymod(){return this->keyMods;}
        bool isModifiedBy(SDL_Keymod modifier){return this->keyMods & modifier;}
        int getNumClicks(){return this->numClicks;}
    };

    class KeyboardEventDetails : public EventDetails {
    protected:
        SDL_Keycode key;
        bool isRepeated;
        SDL_Keymod keyMods;
    public:
        KeyboardEventDetails(GameManager* g, std::string event_n, int id, bool is_canc,std::chrono::high_resolution_clock::time_point currentTime, std::chrono::high_resolution_clock::time_point startTime,
            SDL_Keycode key, bool isRep, SDL_Keymod keym) : EventDetails(g, event_n,id, is_canc, currentTime, startTime), key(key), isRepeated(isRep), keyMods(keym){}

        int getKey(){return key;}
        bool getIsRepeated(){return isRepeated;}
        SDL_Keymod getKeymod(){return this->keyMods;}
        bool isModifiedBy(SDL_Keymod modifier){return this->keyMods & modifier;}
    };
}

namespace Listener{
    class GameListener{
    public:
        // This function exists purely for allowing for casting checks. Has to be
        // 	public.
        virtual void __notcalled(){}

        // Deconstructor for listener, default listener
        virtual ~GameListener(){}
    };
    class GenericEventListener : virtual public GameListener {
    public:
        /*
            This function will be called whenever a user-defined event is told to execute.
        */
        virtual void eventExecuted(Events::EventDetails* events)=0;
    };


    class GameEventsListener : virtual public GameListener{
    public:
        // An event for when the game engine starts the game (window is created)
        // Guarenteed that this is called after the window is created and peripherals are
        // 	existant.
        virtual void gameStart(Events::EventDetails* events)=0;

        // An event for when the game engine is ending the game (window is closed) Use for
        // 	cleaning up the listener.
        virtual void gameEnd(Events::EventDetails* events)=0;
    };

    class GameTickListener : virtual public GameListener{
    public:
        // An event for when the game engine performs a "tick" (an internal computation of
        // 	the game world). Defaults to being called every 1/60th of a second.
        // 	Be careful doing major computations here.
        // 	Useful for game physics/game state checks.
        //
        //
        // 	ms_delay is the number of milliseconds between the current and previous call
        // 		to this function.
        virtual void gameTick(Events::TimedEventDetails* events)=0;
    };

    class GameGUIListener : virtual public GameListener {
    public:
        // An event for when the game engine performs a "draw" (an internal computation
        // 	of the screen to display to the user). Defaults to being called every
        // 	1/60th of a second. Be careful doing major computations here.
        //	Useful for graphical user interface (GUI) operations.
        //
        //	NOTE: Drawing to the screen must occur in this function!
        //
        //	ms_delay is the number of milliseconds between the current and previous
        //		call to this function.
        virtual void gameGUI(Events::WindowEventDetails* events)=0;
    };

    class GameKeyboardListener : virtual public GameListener {
    public:

        virtual void gameKeyPressed(Events::KeyboardEventDetails* event)=0;

        virtual void gameKeyReleased(Events::KeyboardEventDetails* event)=0;
    };

    class GameMouseListener : virtual public GameListener {
    public:
        virtual void gameMouseButtonPressed(Events::MouseButtonEventDetails* event)=0;

        virtual void gameMouseButtonReleased(Events::MouseButtonEventDetails* event)=0;

        virtual void gameMouseMoved(Events::MouseButtonEventDetails* event)=0;


    };


}



#endif //GAME_LISTENERS_H_

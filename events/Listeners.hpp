
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
	// Forward Declaration of EventDispatcher.
    class EventDispatcher;
	// A priority enum to present the priority of events.
    enum Priority {HIGHEST=5, HIGH=4, MEDIUM=3, LOW=2, LOWEST=1};
	
	// Base class for event details.
    class EventDetails{
    protected:
        // Note: Sections below are redundant as the events are separated into group
        Engine::GameManager* game;
        bool is_cancelled; // Is the event cancelled
        std::string event_name; // Name of event (semi-redundant)
        int event_id; // The ID of the event (semi-redundant)
        bool is_cancellable; // Can the event be cancelled
        std::chrono::high_resolution_clock::time_point currentGameTime; // The current game time
        std::chrono::high_resolution_clock::time_point startGameTime; // The starting time point in the game
    public:
        
		/*
			Constructor, takes:
					A pointer to the GameManager object
					A string representing the event's locale name
					An event id
					A bool representing if the event is cancellable
					A time point representing the current time when the event was created
					A time point representing the time of which the game was started.
					
					Is cancelled defaults to false (as the event has yet to be cancelled).
		*/
        EventDetails(GameManager* g, std::string event_n, int id, bool is_canc,std::chrono::high_resolution_clock::time_point currentTime,
                std::chrono::high_resolution_clock::time_point startTime ) : game(g),is_cancelled(false),  event_name(event_n),
                event_id(id),is_cancellable(is_canc), currentGameTime(currentTime), startGameTime(startTime) {}

		// The event dispatcher is a friend of this class, allowing access to protected/private variables.
        friend class Events::EventDispatcher;
		
		// Getters
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
	// A timed event details, contains information on the delta time between the last call to this event
	// 		and this call.
    class TimedEventDetails : public EventDetails{
    protected:
        long long eventTimeDelta;
        long long eventTimeDeltaExact;
    public:
		// Constructor, same arguments as in parent's class, except timeDelta (the time [in ms] between
		// 		the last time this event was called and when the event was dispatched) and timeDeltaExact
		//		(similar to timeDelta except it is with the current time the listener is receiving).
        TimedEventDetails(GameManager* g, std::string event_n, int id, bool is_canc,std::chrono::high_resolution_clock::time_point currentTime, std::chrono::high_resolution_clock::time_point startTime,
                          long long timeDelta,long long timeDeltaNow): EventDetails(g, event_n, id, is_canc, currentTime, startTime), eventTimeDelta(timeDelta),
                                                                       eventTimeDeltaExact(timeDeltaNow){}
		// EventDispatcher is a friend of this class
        friend class EventDispatcher;
		// Getters
        long long getEventTimeDeltaExact(){return this->eventTimeDeltaExact;}
        long long getEventTimeDelta(){return this->eventTimeDelta;}


    };
	// A timed event, except it also contains a reference to the display object to render with.
    class WindowEventDetails : public TimedEventDetails{
    protected:
		// A pointer to the display object.
        Display* win;
    public:
		// Constructor, same arguments as in parent's class except additionally a display reference
		// 		is passed as the last argument.
        WindowEventDetails(GameManager* g, std::string event_n, int id, bool is_canc,std::chrono::high_resolution_clock::time_point currentTime, std::chrono::high_resolution_clock::time_point startTime,
        long long timeDelta,long long timeDeltaNow, Display* w): TimedEventDetails(g, event_n, id, is_canc, currentTime, startTime, timeDelta,timeDeltaNow), win(w){}

		// Getter
        Display* getDisplay(){return this->win;}

    };

	// A mouse button event details, keeps tracks of details about mouse clicks or movement
    class MouseButtonEventDetails : public EventDetails {
    protected:
        int mouseButton;
		
		// Mouse position location
        Math::Vector2Int mousePos;
		// Mouse position delta
        Math::Vector2Int deltaMousePos;
		// The key modifiers
        SDL_Keymod keyMods;
		// The number of clicks before the click event was pulled.
        int numClicks;
    public:
		/*
			Constructor, same arguments as in parent's class except additionally:
				an int representing the mouse button pressed 
					(0 if a mouse moved event)
				a vector2 representing the position of the mouse on the screen
				a vector2 representing the change in the position of the mouse on the screen 
					(0,0 if mouse button event)
				SDL_Keymod object holding all modifying keys pressed while the event was polled
				An int representing the number of clicks performed before the event was polled
					(0 if a mouse moved event)
		*/
        MouseButtonEventDetails(GameManager* g, std::string event_n, int id, bool is_canc,std::chrono::high_resolution_clock::time_point currentTime, std::chrono::high_resolution_clock::time_point startTime,
            int mouseB, Math::Vector2Int mouseP, Math::Vector2Int deltaMP, int numcl, SDL_Keymod keym) : EventDetails(g, event_n,id, is_canc, currentTime, startTime),mouseButton(mouseB),
            mousePos(mouseP), deltaMousePos(deltaMP), keyMods(keym), numClicks(numcl){}

		// A group of functions for quickly determining which buttons were pressed.
        bool isButtonLDown(){return mouseButton & SDL_BUTTON_LMASK;}
        bool isButtonRDown(){return mouseButton & SDL_BUTTON_RMASK;}
        bool isButtonMDown(){return mouseButton & SDL_BUTTON_MMASK;}
        bool isButtonX1Down(){return mouseButton & SDL_BUTTON_X1MASK;}
        bool isButtonX2Down(){return mouseButton & SDL_BUTTON_X2MASK;}
        
		// Getters
		int getAllMouseButtons(){return mouseButton;}
        Math::Vector2Int getMousePosition(){return mousePos;}
        Math::Vector2Int getDeltaMousePosition(){return deltaMousePos;}
        SDL_Keymod getKeymod(){return this->keyMods;}
        int getNumClicks(){return this->numClicks;}
		
		// A function to determine if a modifying key is held down in this event
		bool isModifiedBy(SDL_Keymod modifier){return this->keyMods & modifier;}
		// A function to get the mouse's previous position
		Math::Vector2Int getPreviousMousePosition(){return Math::Vector2Int(mousePos - deltaMousePos);}
    };

	// A keyboard event details, keeps track of all key press events
    class KeyboardEventDetails : public EventDetails {
    protected:
		// The key pressed/released
        SDL_Keycode key;
		// If the key was held and thus the key pressed event is repeated
        bool isRepeated;
		// The key modifiers
        SDL_Keymod keyMods;
    public:
		/*
			Constructor, same arguments as parent's class except additionally:
				A SDL_Keycode representing the key pressed/released
				A bool representing if the event is being repeated due to the key being held down
				A SDL_Keymod representing all key modifiers present during this event
		*/
        KeyboardEventDetails(GameManager* g, std::string event_n, int id, bool is_canc,std::chrono::high_resolution_clock::time_point currentTime, std::chrono::high_resolution_clock::time_point startTime,
            SDL_Keycode key, bool isRep, SDL_Keymod keym) : EventDetails(g, event_n,id, is_canc, currentTime, startTime), key(key), isRepeated(isRep), keyMods(keym){}

		// Getters
        int getKey(){return key;}
        bool getIsRepeated(){return isRepeated;}
        SDL_Keymod getKeymod(){return this->keyMods;}
		
		// A function to determine if a modifying key is held down in the event
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
		/*
			An event for when a key on the keyboard changes states (pressed<->released)
			or if the key is held in the pressed state long enough.
		*/
        virtual void gameKeyPressed(Events::KeyboardEventDetails* event)=0;

        virtual void gameKeyReleased(Events::KeyboardEventDetails* event)=0;
    };

    class GameMouseListener : virtual public GameListener {
    public:
		/*
			An event for when the mouse buttons change state (pressed<->released)
			or if the mouse has moved on screen.
		*/
        virtual void gameMouseButtonPressed(Events::MouseButtonEventDetails* event)=0;

        virtual void gameMouseButtonReleased(Events::MouseButtonEventDetails* event)=0;

        virtual void gameMouseMoved(Events::MouseButtonEventDetails* event)=0;


    };


}



#endif //GAME_LISTENERS_H_

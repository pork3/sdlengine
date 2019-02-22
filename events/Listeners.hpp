#ifndef GAME_LISTENERS_H_
#define GAME_LISTeNERS_H_

// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 *	Last updated by: Chase Craig
 *	Last updated on: Feb. 19, 2019
 *
 *	Purpose:
 *		This header class is to provide base classes for a game script to register event handlers/
 *			intercepters for game events executed by the game engine.
 *
 *	Conventions:
 *		Classes and Namespaces should have every word Capitalized with no _
 *		Functions should have their first word lowercase, all other words are Capitalized, no _
 *			Exceptions: Constructors and Destructors must match the class name exactly.
 *		Parameters should be all lowercase with _ seperating words
 *
 *	Functions without comments are assumed to be a single line, set or get a single variable, and the
 *		comment is to be found next to the respective variable definition.
 */

// General includes
#include <string>

namespace Events{
    enum Priority {HIGHEST, HIGH, MEDIUM, LOW, LOWEST};
    class EventDetails{
    protected:
        // Note: Sections below are redundant as the events are seperated into group
        bool is_cancelled; // Is the event cancelled
        std::string event_name; // Name of event (semi-redundant)
        int event_id; // The ID of the event (semi-redundant)
        bool is_cancellable; // Can the event be cancelled
    public:
        bool isCancelled(){return this->is_cancelled;}
        bool isCancellable(){return this->is_cancellable;}

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
        bool uncancel(){
            this->is_cancelled = false;
        }

    }
}

namespace Listener{
    class GameListener{
    public:
        /*
         *	This function will be called upon this class either:
         *		being register to an event (registered = true)
         *		(or)
         *		being removed from an event (registered = false)
         *
         *	The eventID is the event in question, below is a list of ID's possible
         *		(may be updated in future revisions)
         */
        virtual void debugRegistry(int eventID, bool registered)=0;

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
        virtual void eventExecuted(const ListenerEvent::EventDetails& events)=0;
    };


    class GameEventsListener : virtual public GameListener{
    public:
        // An event for when the listener is registered. Useful for loading essential
        //  	resources.
        virtual void gameInit(const ListenerEvent::EventDetails& events)=0;

        // An event for when the game engine starts the game (window is created)
        // Guarenteed that this is called after the window is created and peripherals are
        // 	existant.
        virtual void gameStart(const ListenerEvent::EventDetails& events)=0;

        // An event for when the game engine is ending the game (window is closed) Use for
        // 	cleaning up the listener.
        virtual void gameEnd(const ListenerEvent::EventDetails& events)=0;
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
        virtual void gameTick(long ms_delay, const ListenerEvent::EventDetails& events)=0;
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
        virtual void gameGUI(long ms_delay, const ListenerEvent::EventDetails& events)=0;
    };


}



#endif //GAME_LISTENERS_H_

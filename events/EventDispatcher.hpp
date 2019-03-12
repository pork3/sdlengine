#ifndef ENGINE_EVENT_DISPATCHER_HPP
#define ENGINE_EVENT_DISPATCHER_HPP

// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
  
  	
 	Last updated by: Chase Craig
 	Last updated on: Mar. 11, 2019
 
 	Purpose:
		To handle the registration, management and execution of event listeners. Has a priority system to 
			allow for some sort of ordering of importance in event execution.
			
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
			
		This will implement executors, registers and unregisters, to save on typing, the basic rundown
			on the logic implemented in each function is as follows (slightly changed based on the 
			function themselves)
			
		All events are stored in map object, which map priorities to unordered sets of pointers. 
		Exception is user defined events, which then has an outermost map that maps strings to 
			maps of unordered sets of pointers.
		
		For registration:
			Find the map (priority -> set) that corresponds to the given register.
			Get the set for the provided priority, insert the pointer into the set.
			
		For unregistration:
			Find the map (priority -> set) that corresponds to the given unregister.
			Goes through all possible priorities, test to see if "finding" the pointer is equal to the 
				end pointer of the set (representing not found), if not, then remove the pointer.
		
		For execution:
			Find the map (priority -> set) the corresponds to the given execution event.
			Go through all possible priorities from HIGHEST to LOWEST, looping through all listeners
				in the given set given by the map for the current priority and calling their respective 
				functions. 
			If the current priority set is finished and the event is cancelled*, stop looping throught the
				priorities and return. 
			Exception to the above is with the game starting event, it is cancellable to represent starting
				paused or not. Thus, it will continue with execution through all priorities.
 
 
 
 */



#include "Listeners.hpp"
#include <string>
#include <map>
#include <unordered_set>
#include <iostream>

// Use the Listener and standard namespace.
using namespace Listener;
using namespace std;
// Forward declare the GameManager class
namespace Engine{
    class GameManager;
}
namespace Events{
	// Creates an enum to represent the Start and Stop game event
    enum GameEvent {START, STOP};
	
	// The EventDispatcher class
    class EventDispatcher{
	
    public:
		// GameManager is a friend of this class, and hence can see/modify/call protected/private fields.
        friend class Engine::GameManager;
        // An instance function that ensures that only one copy of event dispatcher is ever created.
		static EventDispatcher* &instance(){static EventDispatcher* e_d = new EventDispatcher(); return e_d;}

		// Register and unregister functions for given listeners.
        void RegisterEventListener( GameEventsListener* l,Priority p);
        void UnregisterEventListener( GameEventsListener* listener);

        void RegisterTickListener(GameTickListener* l,Priority p);
        void UnregisterTickListener( GameTickListener* listener);

        void RegisterKeyListener(GameKeyboardListener* l,Priority p);
        void UnregisterKeyListener( GameKeyboardListener* listener);


        void RegisterMouseListener(GameMouseListener* l,Priority p);
        void UnregisterMouseListener( GameMouseListener* listener);

		// Register for user defined events (not listeners). Returns true/false based on success of creating
		//		an event with the given name.
        bool RegisterUserDefinedEvent(const string eventName);

		// Register for register user defined event listeners.
        void RegisterUserDefinedListener( GenericEventListener* lis, string eventName, Priority p);

		// Unregister for user defined event listeners.
        void UnregisterUserdefinedListener(GenericEventListener* lis, string eventName);




		// A (public) executor for executing user defined events. Returns true/false based on if the event
		// 		was not cancelled (cancelled = false).
        bool ExecuteUserDefinedEvents( string eventName, EventDetails* details);
    protected:
		// Protected/private events for executing game events.
        void ExecuteGameEvent(GameEvent event, EventDetails* details);
        void ExecuteTickEvent(TimedEventDetails* details);
        void ExecuteKeyEvent(KeyboardEventDetails* details);
        void ExecuteMouseEvent(MouseButtonEventDetails* details);


    private:
		// These variables are maps of priorities to sets of pointers of class objects to be called back
		//		when an event occurs.
        std::map<Priority, std::unordered_set<GameEventsListener*>* > gameEventListeners{};
        std::map<Priority, std::unordered_set<GameTickListener*>* > gameTickListeners{};
        std::map<Priority, std::unordered_set<GameKeyboardListener*>* > gameKeyListeners{};
        std::map<Priority, std::unordered_set<GameMouseListener*>* > gameMouseListeners{};
		
		// An unordered set of string for the names of user defined events registered in the system.
        std::unordered_set<std::string> userEventNames{};
		// A map object that maps a user defined event name (string) to a pointer of another map that
		// takes a priority and maps that to a set of generic event listener pointers.
        std::map<std::string, std::map<Priority, std::unordered_set<GenericEventListener*>* >* > userEventListeners;
        
		// The constructor for the event dispatcher...it goes through all priorities and initializes the
		//		maps with new blank set.
		EventDispatcher(){
            for(int i = 5; i > 0; i--){
                gameEventListeners.insert(pair<Priority, std::unordered_set<GameEventsListener*>* >{static_cast<Priority>(i), new std::unordered_set<GameEventsListener*>{}});
                gameTickListeners.insert(pair<Priority, std::unordered_set<GameTickListener*>* >{static_cast<Priority>(i), new std::unordered_set<GameTickListener*>{}});
                gameKeyListeners.insert(pair<Priority, std::unordered_set<GameKeyboardListener*>* >{static_cast<Priority>(i), new std::unordered_set<GameKeyboardListener*>{}});
                gameMouseListeners.insert(pair<Priority, std::unordered_set<GameMouseListener*>* >{static_cast<Priority>(i), new std::unordered_set<GameMouseListener*>{}});
            }
        }
    };

}


#endif // ENGINE_EVENT_DISPATCHER_HPP

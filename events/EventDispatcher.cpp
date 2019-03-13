#include "Listeners.hpp"
#include "EventDispatcher.hpp"
#include <iostream>
#include <chrono>
#include "../utils/Utils.hpp"
#include "../err/Error.hpp"


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

// Use the Listener namespace
using namespace Listener;

// Registers a GameEvent (start/stop) listener with a given priority
void Events::EventDispatcher::RegisterEventListener( GameEventsListener* l,Priority p){
    std::unordered_set<GameEventsListener*>* uuo = gameEventListeners.at(p);
    uuo->insert(l);
}

// Registers a keyboard listener with a given priority
void Events::EventDispatcher::RegisterKeyListener( GameKeyboardListener* l,Priority p){
    std::unordered_set<GameKeyboardListener*>* uuo = gameKeyListeners.at(p);
    uuo->insert(l);
}

// Registers a mouse listener with a given priority
void Events::EventDispatcher::RegisterMouseListener( GameMouseListener* l,Priority p){
    std::unordered_set<GameMouseListener*>* uuo = gameMouseListeners.at(p);
    uuo->insert(l);
}

// Registers a game logic tick listener with a given priority
void Events::EventDispatcher::RegisterTickListener(GameTickListener* l,Priority p){
    std::unordered_set<GameTickListener*>* uuo = gameTickListeners.at(p);
    uuo->insert(l);
}



// Unregisters: All 4 act the same by trying to remove the given pointer from the respective group
// 		However, this means that if it was registered twice (to the same event), it will be removed twice
// 		These will continue silently if the listener is not found. O(1) on average for all functions.

void Events::EventDispatcher::UnregisterTickListener(GameTickListener *list) {
    for(int i = 5; i > 0; i--){
        if(this->gameTickListeners.at(static_cast<Events::Priority>(i))->find(list) != this->gameTickListeners.at(static_cast<Events::Priority>(i))->end()){
            this->gameTickListeners.at(static_cast<Events::Priority>(i))->erase(list);
        }
    }
}

void Events::EventDispatcher::UnregisterMouseListener(GameMouseListener *list) {
    for(int i = 5; i > 0; i--){
        if(this->gameMouseListeners.at(static_cast<Events::Priority>(i))->find(list) != this->gameMouseListeners.at(static_cast<Events::Priority>(i))->end()){
            this->gameMouseListeners.at(static_cast<Events::Priority>(i))->erase(list);
        }
    }
}

void Events::EventDispatcher::UnregisterKeyListener(GameKeyboardListener *list) {
    for(int i = 5; i > 0; i--){
        if(this->gameKeyListeners.at(static_cast<Events::Priority>(i))->find(list) != this->gameKeyListeners.at(static_cast<Events::Priority>(i))->end()){
            this->gameKeyListeners.at(static_cast<Events::Priority>(i))->erase(list);
        }
    }
}

void Events::EventDispatcher::UnregisterEventListener(GameEventsListener *list) {

    for(int i = 5; i > 0; i--){
        if(this->gameEventListeners.at(static_cast<Events::Priority>(i))->find(list) != this->gameEventListeners.at(static_cast<Events::Priority>(i))->end()){
            this->gameEventListeners.at(static_cast<Events::Priority>(i))->erase(list);
        }
    }
}

// This function will execute a user defined event. It will return false if the event was cancelled or was
// 		not found. It will return true if the event was not cancelled. 

// Note: If the event is cancelled, it can be uncancelled by an event in the same priority.
bool Events::EventDispatcher::ExecuteUserDefinedEvents(string eventName, Events::EventDetails* e){
    // If the event does not exist, return false and log an error.
    if(this->userEventNames.find(eventName) == this->userEventNames.end()){return false;}

    auto utilRef = Engine::Utilities::instance();
    for(int i = 5; i > 0; i--){
        std::unordered_set<GenericEventListener*>* uuo = this->userEventListeners.at(eventName)->at(static_cast<Events::Priority>(i));
        auto start= uuo->begin();
        auto ends = uuo->end();
        for(; ends != start; start++){
            (*start)->eventExecuted(e);
        }
        if(e->isCancelled()){
            Error::WriteError("Event " + eventName + " does not exits");
            return false;
        }
    }


    return true;
}

// Unregister a user defined event listener. Silently* ignores if the event does not exist.
// 		*: Planned is to add logging into to log the event if it does not exist.
void Events::EventDispatcher::UnregisterUserdefinedListener(GenericEventListener* lis, string eventName){
    if(this->userEventNames.find(eventName) != this->userEventNames.end()){
        for(int i = 5; i > 0; i--){
            if(this->userEventListeners.at(eventName)->at(static_cast<Priority>(i))->find(lis) != this->userEventListeners.at(eventName)->at(static_cast<Priority>(i))->end()){
                this->userEventListeners.at(eventName)->at(static_cast<Priority>(i))->erase(lis);
            }
        }
    }else {

        // Silently ignore the call if the event does not exist.
        Error::WriteError("Error: unable to register event : " + eventName);
    }
}

// Registers a user defined event listener (silently* (see above) ignoring the request if the event does
// 		not exist) to the given event name given its priority.
void Events::EventDispatcher::RegisterUserDefinedListener( GenericEventListener* lis, string eventName, Priority p){
    auto enamePointer = this->userEventNames.find(eventName);
    if(enamePointer != this->userEventNames.end()){
        this->userEventListeners.at(eventName)->at(p)->insert(lis);
    }else {
        Error::WriteError("Error event " + eventName + " does not exist");
    }
}

// Registers a user defined event. Returns false if the event already exists, true if it was created 
//		successfully.
bool Events::EventDispatcher::RegisterUserDefinedEvent(const string eventName){
    auto enamePointer = this->userEventNames.find(eventName);
    if(enamePointer == this->userEventNames.end()){
        this->userEventNames.insert(eventName);
        this->userEventListeners.insert(pair<std::string, std::map<Priority, std::unordered_set<GenericEventListener*>*>*>{
           eventName, new std::map<Priority, std::unordered_set<GenericEventListener*>*>{}
        });
        for(int i = 5; i > 0; i--){
            this->userEventListeners.at(eventName)->insert(pair<Priority, std::unordered_set<GenericEventListener*>* >{static_cast<Priority>(i),
                        new std::unordered_set<GenericEventListener*>{}});

        }
		return true;
    }
    Error::WriteError("Error event "+ eventName + " already exists");
    return false;
}

// Executes the gameTick function on tick event listeners.
void Events::EventDispatcher::ExecuteTickEvent(TimedEventDetails* details){
    auto utilRef = Engine::Utilities::instance();
    for(int i = 5; i > 0; i--){
        std::unordered_set<GameTickListener*>* uuo = gameTickListeners.at(static_cast<Events::Priority>(i));
        auto start= uuo->begin();
        auto ends = uuo->end();
        for(; ends != start; start++){
            (*start)->gameTick(details);
            std::chrono::high_resolution_clock::time_point new_time = high_resolution_clock::now();
            details->eventTimeDeltaExact = utilRef->getMillisFrom(&new_time, &details->currentGameTime);
        }
        if(details->isCancelled()){
            break;
        }
    }
}

// Executes a mouse function on mouse event listeners.
void Events::EventDispatcher::ExecuteMouseEvent(MouseButtonEventDetails* details){
    auto utilRef = Engine::Utilities::instance();
    for(int i = 5; i > 0; i--){
        std::unordered_set<GameMouseListener*>* uuo = gameMouseListeners.at(static_cast<Events::Priority>(i));
        auto start= uuo->begin();
        auto ends = uuo->end();
        for(; ends != start; start++){
            switch(details->getID()){
            case 6:
                    (*start)->gameMouseButtonPressed(details);
                    break;
            case 7:
                    (*start)->gameMouseButtonReleased(details);
                    break;
            case 8:
                    (*start)->gameMouseMoved(details);
                    break;
            default:
                Error::WriteError("Unknown id in mouse handler : " + std::to_string(details->getID()) + " does not exist");
            }
        }
        if(details->isCancelled()){
            break;
        }
    }
}

// Executes a key function on key event listeners.
void Events::EventDispatcher::ExecuteKeyEvent(KeyboardEventDetails* details){
    auto utilRef = Engine::Utilities::instance();
    for(int i = 5; i > 0; i--){
        std::unordered_set<GameKeyboardListener*>* uuo = gameKeyListeners.at(static_cast<Events::Priority>(i));
        auto start= uuo->begin();
        auto ends = uuo->end();
        for(; ends != start; start++){
            switch(details->getID()){
            case 4:
                    (*start)->gameKeyPressed(details);
                    break;
            case 5:
                    (*start)->gameKeyReleased(details);
                    break;
            default:
                Error::WriteError("Unknown id in key event" + std::to_string(details->getID()) + " does not exist");
            }
        }
        if(details->isCancelled()){
            break;
        }
    }
}

// Executes a game event function on game event listeners, requires an event identifier
void Events::EventDispatcher::ExecuteGameEvent( GameEvent event,EventDetails* details){
    auto utilRef = Engine::Utilities::instance();
    for(int i = 5; i > 0; i--){
        std::unordered_set<GameEventsListener*>* uuo = gameEventListeners.at(static_cast<Events::Priority>(i));
        auto start= uuo->begin();
        auto ends = uuo->end();
        for(; ends != start; start++){
            switch(event) {
                case GameEvent::START:
                    (*start)->gameStart(details);
                    break;
                case GameEvent::STOP:
                    (*start)->gameEnd(details);
                    break;
                default:
                    break;
            }
        }
        if(details->isCancelled() && event != GameEvent::START){
            break;
        }
    }
}



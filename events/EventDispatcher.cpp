#include "Listeners.hpp"
#include "EventDispatcher.hpp"
#include <iostream>
#include <chrono>
#include "../utils/Utils.hpp"


// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 
 	Last updated by: Chase Craig
 	Last updated on: Mar. 11, 2019
 
 	Purpose:
		
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


using namespace Listener;
void Events::EventDispatcher::RegisterEventListener( GameEventsListener* l,Priority p){
    std::unordered_set<GameEventsListener*>* uuo = gameEventListeners.at(p);
    uuo->insert(l);
}
void Events::EventDispatcher::RegisterKeyListener( GameKeyboardListener* l,Priority p){
    std::unordered_set<GameKeyboardListener*>* uuo = gameKeyListeners.at(p);
    uuo->insert(l);
}
void Events::EventDispatcher::RegisterMouseListener( GameMouseListener* l,Priority p){
    std::unordered_set<GameMouseListener*>* uuo = gameMouseListeners.at(p);
    uuo->insert(l);
}

void Events::EventDispatcher::RegisterTickListener(GameTickListener* l,Priority p){
    std::unordered_set<GameTickListener*>* uuo = gameTickListeners.at(p);
    uuo->insert(l);
}

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


bool Events::EventDispatcher::ExecuteUserDefinedEvents(string eventName, bool cancellable, Events::EventDetails* e){
    // If the event does not exist, return false and log an error.
    // TODO: LOG ERROR!
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
            return false;
        }
    }


    return true;
}

void Events::EventDispatcher::UnregisterUserdefinedListener(GenericEventListener* lis, string eventName){
    if(this->userEventNames.find(eventName) != this->userEventNames.end()){
        for(int i = 5; i > 0; i--){
            if(this->userEventListeners.at(eventName)->at(static_cast<Priority>(i))->find(lis) != this->userEventListeners.at(eventName)->at(static_cast<Priority>(i))->end()){
                this->userEventListeners.at(eventName)->at(static_cast<Priority>(i))->erase(lis);
            }
        }
    }else {
        // Silently ignore the call if the event does not exist.
        // TODO: NEED TO LOG ERROR, EVENT DOES NOT EXIST
    }
}

void Events::EventDispatcher::RegisterUserDefinedListener( GenericEventListener* lis, string eventName, Priority p){
    auto enamePointer = this->userEventNames.find(eventName);
    if(enamePointer != this->userEventNames.end()){
        this->userEventListeners.at(eventName)->at(p)->insert(lis);
    }else {
        // Silently ignore the call if the event does not exist.
        // TODO: NEED TO LOG ERROR, EVENT DOES NOT EXIST
    }
}

// Returns an int based upon the success of the function
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
    }
    return false;
}

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
                std::cerr << "Unknown id" << details->getID() << std::endl;
            }
        }
        if(details->isCancelled()){
            break;
        }
    }
}

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
                std::cerr << "Unknown id" << details->getID() << std::endl;
            }
        }
        if(details->isCancelled()){
            break;
        }
    }
}


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



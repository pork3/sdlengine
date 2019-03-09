#include "Listeners.hpp"
#include "EventDispatcher.hpp"
#include <iostream>
#include <chrono>
#include "../utils/Utils.hpp"


using namespace Listener;
void Events::EventDispatcher::RegisterEventListener( GameEventsListener* l,Priority p){
    std::unordered_set<GameEventsListener*>* uuo = gameEventListeners.at(p);
    uuo->insert(l);
}

void Events::EventDispatcher::RegisterTickListener(GameTickListener* l,Priority p){
    std::unordered_set<GameTickListener*>* uuo = gameTickListeners.at(p);
    uuo->insert(l);
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
    auto enamePointer = this->userEventNames.find(eventName);
    if(enamePointer != this->userEventNames.end()){
        for(int i = 5; i > 0; i--){
            this->userEventListeners.at(eventName)->at(static_cast<Priority>(i))->erase(lis);
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
    }
}



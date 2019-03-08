#include "Listeners.hpp"
#include "EventDispatcher.hpp"
#include <iostream>
#include <chrono>
#include "../utils/Utils.hpp"


using namespace Listener;
void Events::EventDispatcher::RegisterEventListener( GameEventsListener* l,Priority p){

}

void Events::EventDispatcher::RegisterTickListener(GameTickListener* l,Priority p){
    std::unordered_set<GameTickListener*>* uuo = gameTickListeners.at(p);
    uuo->insert(l);
}

bool Events::EventDispatcher::ExecuteUserDefinedEvents(string eventName, bool cancellable, Events::EventDetails* e){
    return false;
}

void Events::EventDispatcher::UnregisterUserdefinedListener(GenericEventListener* lis, string eventName){

}

void Events::EventDispatcher::RegisterUserDefinedListener( GenericEventListener* lis, string eventName, Priority p){

}

int Events::EventDispatcher::RegisterUserDefinedEvent( string eventName){
    return 0;
}

void Events::EventDispatcher::ExecuteTickEvent(TimedEventDetails* details){
    auto utilRef = Engine::Utilities::instance();
    std::cout << "Ticked!" << std::endl;
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
}



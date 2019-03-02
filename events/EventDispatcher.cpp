

#include "Listeners.hpp"
#include "EventDispatcher.hpp"
#include <iostream>
using namespace Listener;
void Events::EventDispatcher::RegisterEventListener(GameEventsListener* l,Priority p){

}

void Events::EventDispatcher::RegisterGUIListener(GameGUIListener* l,Priority p){

}

void Events::EventDispatcher::RegisterTickListener(GameTickListener* l,Priority p){
    std::unordered_set<GameTickListener*>* uuo = gameTickListeners.at(p);
    uuo->insert(l);
    Events::TimedEventDetails evd("Tick", 3, false, startTickTime, this->startingTime, tickDelta, tickDelta);
    l->listenerInit()
}

bool Events::EventDispatcher::ExecuteUserDefinedEvents(string eventName, bool cancellable, Events::EventDetails* e){
    return false;
}

void Events::EventDispatcher::UnregisterUserdefinedListener(GenericEventListener* lis, string eventName){

}

void Events::EventDispatcher::RegisterUserDefinedListener(GenericEventListener* lis, string eventName, Priority p){

}

int Events::EventDispatcher::RegisterUserDefinedEvent(string eventName){
    return 0;
}

void Events::EventDispatcher::RegisterListener(GameListener* listener, Priority p){

    GameEventsListener* EL = dynamic_cast<GameEventsListener*>(listener);
    if(EL){
        this->RegisterEventListener(EL,p);
    }
    GameGUIListener* GL = dynamic_cast<GameGUIListener*>(listener);
    if(GL){
        this->RegisterGUIListener(GL,p);
    }
    GameTickListener* TL = dynamic_cast<GameTickListener*>(listener);
    if(TL){
        this->RegisterTickListener(TL,p);
    }
}

void Events::EventDispatcher::ExecuteTickEvent(TimedEventDetails* details){
    std::cout << "Ticked!" << std::endl;
    for(int i = 5; i > 0; i--){
        std::unordered_set<GameTickListener*>* uuo = gameTickListeners.at(static_cast<Events::Priority>(i));
        auto start= uuo->begin();
        auto ends = uuo->end();
        for(; ends != start; start++){
            (*start)->gameTick(details);
        }
    }
}

void Events::EventDispatcher::ExecuteGUIEvent(TimedEventDetails* details){
    std::cout << "Framed!" << std::endl;
    for(int i = 5; i > 0; i--){
        std::unordered_set<GameGUIListener*>* uuo = gameGUIListeners.at(static_cast<Events::Priority>(i));
        auto start= uuo->begin();
        auto ends = uuo->end();
        for(; ends != start; start++){
            (*start)->gameGUI(details);
        }
    }
}

void Events::EventDispatcher::ExecuteGameEvent(GameEvent event,EventDetails* details){
}



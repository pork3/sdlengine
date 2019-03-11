#ifndef ENGINE_EVENT_DISPATCHER_HPP
#define ENGINE_EVENT_DISPATCHER_HPP

// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 *
 *	Last updated by: Chase Craig
 *	Last updated on: Feb. 23, 2019
 *
 *	Purpose:
 *		This header class is to provide base classes for managing the game.
 *  Notes:
 *      The known event ID's:
            0: Game INIT
            1: Game START
            2: Game STOP
            3: Game TICK
            4: Game GUI
 *
 *
 */



#include "Listeners.hpp"
#include <string>
#include <map>
#include <unordered_set>
#include <iostream>

using namespace Listener;
using namespace std;
namespace Engine{
    class GameLoop;
}
namespace Events{
    enum GameEvent {START, STOP};
    class EventDispatcher{

    public:
        friend class Engine::GameLoop;
        static EventDispatcher* &instance(){static EventDispatcher* e_d = new EventDispatcher(); return e_d;}

        void RegisterEventListener( GameEventsListener* l,Priority p);
        void UnregisterEventListener( GameEventsListener* listener);

        void RegisterTickListener(GameTickListener* l,Priority p);
        void UnregisterTickListener( GameTickListener* listener);

        void RegisterKeyListener(GameKeyboardListener* l,Priority p);
        void UnregisterKeyListener( GameKeyboardListener* listener);


        void RegisterMouseListener(GameMouseListener* l,Priority p);
        void UnregisterMouseListener( GameMouseListener* listener);

        bool RegisterUserDefinedEvent(const string eventName);

        void RegisterUserDefinedListener( GenericEventListener* lis, string eventName, Priority p);

        void UnregisterUserdefinedListener(GenericEventListener* lis, string eventName);





        bool ExecuteUserDefinedEvents( string eventName, bool cancellable, EventDetails* details);
    protected:
        void ExecuteGameEvent(GameEvent event, EventDetails* details);
        void ExecuteTickEvent(TimedEventDetails* details);
        void ExecuteKeyEvent(KeyboardEventDetails* details);
        void ExecuteMouseEvent(MouseButtonEventDetails* details);


    private:
        std::map<Priority, std::unordered_set<GameEventsListener*>* > gameEventListeners{};
        std::map<Priority, std::unordered_set<GameTickListener*>* > gameTickListeners{};
        std::map<Priority, std::unordered_set<GameKeyboardListener*>* > gameKeyListeners{};
        std::map<Priority, std::unordered_set<GameMouseListener*>* > gameMouseListeners{};
        std::unordered_set<std::string> userEventNames{};
        std::map<std::string, std::map<Priority, std::unordered_set<GenericEventListener*>* >* > userEventListeners;
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

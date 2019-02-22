#ifndef ENGINE_EVENT_DISPATCHER_HPP
#define ENGINE_EVENT_DISPATCHER_HPP

#include "Listeners.hpp"
namespace Events{
    class Event_Dispatcher{
    public:
        static Event_Dispatcher* &instance(){static Event_Dispatcher* e_d = new Event_Dispatcher; return e_d;}

        void RegisterListener(GameListener* listener, Priority p);

        void Unregister(GameListener* listener);

        int RegisterUserDefinedEvent(string eventName);

        void RegisterUserDefinedListener(GenericEventListener lis, string eventName, Priority p);

        void UnregisterUserdefinedListener(GenericEventListener lis, string eventName);

        bool ExecuteUserDefinedEvents(string eventName, bool cancellable);
    protected:
        void RegisterEventListener(GameEventsListener* l);
        void RegisterTickListener(GameTickListener* l);
        void RegisterGUIListener(GameGUIListener* l);
    private:
        std::map<Priority, std::unordered_set<GameEventsListener*> > gameEventListeners;
        std::map<Priority, std::unordered_set<GameTickListener*> > gameTickListeners;
        std::map<Priority, std::unordered_set<GameGUIListener*> > gameGUIListeners;

        Event_Dispatcher(){}
    };

}


#endif // ENGINE_EVENT_DISPATCHER_HPP

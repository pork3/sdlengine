#ifndef ENGINE_EVENT_DISPATCHER_HPP
#define ENGINE_EVENT_DISPATCHER_HPP

namespace Event_Dispatcher{
    class Event_Dispatcher{
    public:
        static Event_Dispatcher* &instance(){static Event_Dispatcher* e_d = new Event_Dispatcher; return e_d;}
    };

}


#endif // ENGINE_EVENT_DISPATCHER_HPP

#include "Event.hpp"

namespace wdm
{

    Event::Event(EventSource* source)
        :_source(source)
    {
        _eventFlag = 0;
    }


    Event::Event(EventSource* source, uint32_t eventFlag)
        :_source(source)
        , _eventFlag(eventFlag)
    {
    }


    Event::~Event()
    {
    
    }

    void Event::SetEventFlag(uint32_t eventFlag)
    {
        _eventFlag = eventFlag;
    }


    bool Event::haveEventFlag(EventFlag flag)
    {
        if ((_eventFlag & flag) != 0)
        {
            return true;
        }
        return false;
    }


    EventSource* Event::GetEventSource() const
    {
        return _source;
    }


    EventListener* EventListener::CreateEventListener(const std::string& type)
    {
        return new SelectEventListener();
    }

}

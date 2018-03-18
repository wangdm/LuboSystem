#include "Event.hpp"


namespace wdm
{

    EventSource::EventSource()
        :_hanedler(nullptr)
        , _eventFlag(0)
    {
    }


    void EventSource::SetEventData(void* const data)
    {
        _data = data;
    }


    void* EventSource::GetEventData() const
    {
        return _data;
    }


    void EventSource::SetEventHandler(EventHandler* handler)
    {
        _hanedler = handler;
    }


    void EventSource::SetEventFlag(uint32_t eventFlag)
    {
        _eventFlag = eventFlag;
    }


    bool EventSource::haveEventFlag(EventFlag flag)
    {
        if ((_eventFlag & flag) != 0)
        {
            return true;
        }
        return false;
    }


    void EventSource::OnEvent(Event* e)
    {
        if (_hanedler != nullptr)
        {
            _hanedler->handleEvent(e);
        }
    }

}

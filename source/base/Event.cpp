
#include "Event.hpp"


namespace wdm
{

    Event::Event()
    {
    }


    Event::~Event()
    {
    }


    void Event::Post()
    {
    }


    void Event::Get()
    {
    }


    //////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////
    EventListener::EventListener()
    {
    }


    EventListener::~EventListener()
    {
    }


    void EventListener::AddEvent(Event* e)
    {
    }


    void EventListener::DelEvent(Event* e)
    {
    }


    void EventListener::Run()
    {
        while (true)
        {
            if (IsStopping())
            {
                break;
            }

            Listen();

        }
    }


    bool EventListener::Listen()
    {
    }

}
#pragma once

#include <vector>
#include <string>

#include "Thread.hpp"

namespace wdm
{

    enum EventType
    {
        EVENT_TYPE_READ = 0,
        EVENT_TYPE_WRITE,
        EVENT_TYPE_EXCEPT,
        EVENT_TYPE_TIMER
    };


    class Event
    {
    public:
        Event();
        virtual ~Event();

        virtual void Post();
        virtual void Get();

        virtual EventType GetEventType();

    private:

    };


    class EventListener : public Thread
    {
    public:

        virtual void AddEvent(Event* e) = 0;
        virtual void DelEvent(Event* e) = 0;

        static EventListener* CreateEventListener(const std::string& type);

    protected:
        virtual void OnLoop() override;

    private:
        virtual bool Listen();

        std::vector<Event*> events;

    };

}
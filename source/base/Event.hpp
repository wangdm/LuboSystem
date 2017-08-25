#pragma once

#include <vector>

#include "Thread.hpp"

namespace wdm
{

    class Event
    {
    public:
        Event();
        virtual ~Event();

        virtual void Post();
        virtual void Get();

    private:

    };


    class EventListener : public Thread
    {
    public:
        EventListener();
        virtual ~EventListener();

        virtual void AddEvent(Event* e);
        virtual void DelEvent(Event* e);

    protected:
        virtual void Run() override;

    private:
        virtual bool Listen();

        std::vector<Event*> events;

    };

}
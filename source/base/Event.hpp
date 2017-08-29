#pragma once

#include <vector>
#include <string>

#include "Thread.hpp"

namespace wdm
{
    class EventHandler;

    enum EventFlag
    {
        EVENT_FLAG_READ   = 0x00000001,
        EVENT_FLAG_WRITE  = 0x00000002,
        EVENT_FLAG_EXCEPT = 0x00000004,
        EVENT_FLAG_TIMER  = 0x00000008
    };

    class Event
    {
    public:
        Event();
        Event(EventHandler* handler, uint32_t eventFlag);
        virtual ~Event();

        virtual void Post();
        virtual void Get();

        virtual int GetFD() = 0;

        virtual void SetEventHandler(EventHandler* handler);
        virtual void SetEventFlag(uint32_t eventFlag);
        virtual bool haveEventFlag(EventFlag flag);

        virtual void OnEvent(EventFlag flag);

    private:
        EventHandler* _hanedler;
        uint32_t _eventFlag;

    };


    class EventHandler
    {
    public:
        virtual void handleEvent(Event* e, EventFlag f) = 0;

    };


    class EventListener : public Thread
    {
    public:

        virtual void AddEvent(Event* e) = 0;
        virtual void DelEvent(Event* e) = 0;
        virtual void SetTimeout(uint32_t millisecond) = 0;

        static EventListener* CreateEventListener(const std::string& type);

    };

}
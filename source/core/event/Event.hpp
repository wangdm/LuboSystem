#ifndef _EVENT_H_
#define _EVENT_H_


#include "../Platform.hpp"
#include "../Log.hpp"

#include "../Mutex.hpp"
#include "../Thread.hpp"

namespace wdm
{
    class EventHandler;
    class EventSource;

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
        Event(EventSource* source);
        Event(EventSource* source, uint32_t eventFlag);
        virtual ~Event();

        virtual void SetEventFlag(uint32_t eventFlag);
        virtual bool haveEventFlag(EventFlag flag);
        virtual EventSource* GetEventSource() const;

    private:
        uint32_t _eventFlag;
        EventSource* _source;

    };


    class EventHandler
    {
    public:
        virtual void handleEvent(Event* e) = 0;

    };


    class EventSource
    {
    public:
        EventSource();
        virtual ~EventSource() {};

    public:
        virtual void SetEventData(void* const data);
        virtual void* GetEventData() const;

        virtual void SetEventHandler(EventHandler* handler);

        virtual void SetEventFlag(uint32_t eventFlag);
        virtual bool haveEventFlag(EventFlag flag);

        virtual void OnEvent(Event* e);
        virtual int GetFd() const = 0;

    private:
        EventHandler* _hanedler;
        uint32_t _eventFlag;

        void* _data;

    };


    class EventListener : public Thread
    {
    public:
        virtual ~EventListener() {};

        virtual void AddEventSource(EventSource* e) = 0;
        virtual void DelEventSource(EventSource* e) = 0;
        virtual void SetTimeout(uint64_t millisecond) = 0;

        static EventListener* CreateEventListener(const std::string& type);

    };


    class SelectEventListener : public EventListener
    {
    public:
        SelectEventListener();
        virtual ~SelectEventListener();

        virtual void AddEventSource(EventSource* e) override;
        virtual void DelEventSource(EventSource* e) override;
        virtual void SetTimeout(uint64_t millisecond) override;

        virtual void OnLoop() override;

    private:
        std::map<int, EventSource*> eventSource;
        Mutex sourceMtx;

        fd_set read_fds;
        fd_set write_fds;
        fd_set except_fds;

        uint64_t timeout;

    };

#ifdef LINUX
    class EpollEventListener : public EventListener
    {
    public:
        EpollEventListener();
        virtual ~EpollEventListener();

        virtual void AddEventSource(EventSource* e) override;
        virtual void DelEventSource(EventSource* e) override;
        virtual void SetTimeout(uint64_t millisecond) override;

        virtual void OnLoop() override;

    private:
        std::map<int, EventSource*> eventSource;
        Mutex sourceMtx;

        fd_set read_fds;
        fd_set write_fds;
        fd_set except_fds;

        uint64_t timeout;

    };
#endif

}

#endif
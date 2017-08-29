
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

#include "Event.hpp"


namespace wdm
{

    //////////////////////////////////////////////////////////////////////////
    // Event
    //////////////////////////////////////////////////////////////////////////
    Event::Event()
        :_hanedler(nullptr)
        , _eventFlag(0)
    {
    }


    Event::Event(EventHandler* handler, uint32_t eventFlag)
        :_hanedler(handler)
        ,_eventFlag(eventFlag)
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


    void Event::SetEventHandler(EventHandler* handler)
    {
        _hanedler = handler;
    }


    void Event::SetEventFlag(uint32_t eventFlag)
    {
        _eventFlag = eventFlag;
    }


    bool Event::haveEventFlag(EventFlag flag)
    {
        return (flag&_eventFlag) == flag;
    }


    void Event::OnEvent(EventFlag flag)
    {
        if (_hanedler != nullptr)
        {
            _hanedler->handleEvent(this, flag);
        }
    }


    //////////////////////////////////////////////////////////////////////////
    // SelectEventListener
    //////////////////////////////////////////////////////////////////////////
    class SelectEventListener : public EventListener
    {
    public:
        SelectEventListener();
        virtual ~SelectEventListener();

        virtual void AddEvent(Event* e);
        virtual void DelEvent(Event* e);
        virtual void SetTimeout(uint32_t millisecond);

    protected:
        virtual void OnLoop() override;

    private:

        std::vector<Event*> events;

        uint32_t timeout;

        fd_set readset;
        fd_set writeset;
        fd_set exceptset;

        int maxfd;

    };


    SelectEventListener::SelectEventListener()
    {
        FD_ZERO(&readset);
        FD_ZERO(&writeset);
        FD_ZERO(&exceptset);
    }


    SelectEventListener::~SelectEventListener()
    {
    }


    void SelectEventListener::AddEvent(Event* e)
    {
        if (e->haveEventFlag(EVENT_FLAG_READ))
        {
            FD_SET(e->GetFD(), &readset);
        }

        if (e->haveEventFlag(EVENT_FLAG_WRITE))
        {
            FD_SET(e->GetFD(), &writeset);
        }

        if (e->haveEventFlag(EVENT_FLAG_EXCEPT))
        {
            FD_SET(e->GetFD(), &exceptset);
        }

        if (maxfd<e->GetFD())
        {
            maxfd = e->GetFD();
        }

        events.push_back(e);
    }


    void SelectEventListener::DelEvent(Event* e)
    {
        if (e->haveEventFlag(EVENT_FLAG_READ))
        {
            FD_CLR(e->GetFD(), &readset);
        }

        if (e->haveEventFlag(EVENT_FLAG_WRITE))
        {
            FD_CLR(e->GetFD(), &writeset);
        }

        if (e->haveEventFlag(EVENT_FLAG_EXCEPT))
        {
            FD_CLR(e->GetFD(), &exceptset);
        }

        std::vector<Event*>::iterator iter = events.begin();
        for (; iter != events.end(); iter++)
        {
            if (*iter == e)
            {
                events.erase(iter);
            }
        }
    }


    void SelectEventListener::SetTimeout(uint32_t millisecond)
    {

    }


    void SelectEventListener::OnLoop()
    {
        while (true)
        {
            if (IsStopping())
            {
                break;
            }

            struct timeval tv = {};
            tv.tv_sec = timeout / 1000;
            tv.tv_usec = timeout % 1000 * 1000;

            int ret = select(maxfd, &readset, &writeset, &exceptset, &tv);
            if (ret < 0)
            {
                continue;
            }
            else if (ret == 0)
            {
                continue;
            }
            else
            {
                std::vector<Event*>::iterator iter = events.begin();
                for (; iter != events.end(); iter++)
                {
                    if (FD_ISSET((*iter)->GetFD(), &readset))
                    {
                        (*iter)->OnEvent(EVENT_FLAG_READ);
                    }

                    if (FD_ISSET((*iter)->GetFD(), &writeset))
                    {
                        (*iter)->OnEvent(EVENT_FLAG_WRITE);
                    }

                    if (FD_ISSET((*iter)->GetFD(), &exceptset))
                    {
                        (*iter)->OnEvent(EVENT_FLAG_EXCEPT);
                    }
                }
            }
        }
    }


    //////////////////////////////////////////////////////////////////////////
    // CreateEventListener
    //////////////////////////////////////////////////////////////////////////
    EventListener* EventListener::CreateEventListener(const std::string& type)
    {
        if (type=="select")
        {
            return new SelectEventListener();
        }

        return nullptr;
    }

}
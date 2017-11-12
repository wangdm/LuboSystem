#include "Event.hpp"

#include "Log.hpp"

namespace wdm
{

    Event::Event()
    {
        _eventFlag = 0;
    }


    Event::Event(uint32_t eventFlag) 
    {
        _eventFlag = eventFlag;
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


    EventSource::EventSource()
        :_hanedler(nullptr)
        , _eventFlag(0)
    {
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


    EventListener* EventListener::CreateEventListener(const std::string& type)
    {
        return new SelectEventListener();
    }


    SelectEventListener::SelectEventListener()
    {
        FD_ZERO(&read_fds);
        FD_ZERO(&write_fds);
        FD_ZERO(&except_fds);

        timeout = 1000;
    }


    SelectEventListener::~SelectEventListener()
    {
    }


    void SelectEventListener::AddEventSource(EventSource* e)
    {
        if (e == nullptr)
        {
            return;
        }

        _LOCK(&sourceMtx);
        int fd = e->GetFD();
        if (fd >=0 )
        {
            eventSource.insert(std::make_pair(e->GetFD(), e));
        }
        else
        {
            ERROR("The fd is invilid");
        }
    }


    void SelectEventListener::DelEventSource(EventSource* e)
    {
        if (e == nullptr)
        {
            return;
        }

        _LOCK(&sourceMtx);
        std::map<int, EventSource*>::iterator iter = eventSource.find(e->GetFD());
        if (iter != eventSource.end())
        {
            eventSource.erase(iter);
        }
    }


    void SelectEventListener::SetTimeout(uint64_t millisecond)
    {
        timeout = millisecond;
    }


    void SelectEventListener::OnLoop()
    {
        while (!IsStopping())
        {
            int maxfd = -1;
            FD_ZERO(&read_fds);
            FD_ZERO(&write_fds);
            FD_ZERO(&except_fds);
            std::map<int, EventSource*>::const_iterator iter = eventSource.begin();
            for (; iter != eventSource.end(); iter++)
            {
                if (iter->second->haveEventFlag(EVENT_FLAG_READ))
                {
                    int fd = iter->second->GetFD();
                    FD_SET(fd, &read_fds);
                    if (fd>maxfd)
                    {
                        maxfd = fd;
                    }
                }

                if (iter->second->haveEventFlag(EVENT_FLAG_WRITE))
                {
                    int fd = iter->second->GetFD();
                    FD_SET(fd, &write_fds);
                    if (fd > maxfd)
                    {
                        maxfd = fd;
                    }
                }

                if (iter->second->haveEventFlag(EVENT_FLAG_EXCEPT))
                {
                    int fd = iter->second->GetFD();
                    FD_SET(fd, &except_fds);
                    if (fd > maxfd)
                    {
                        maxfd = fd;
                    }
                }
            }

            struct timeval tv;
            tv.tv_sec = timeout / 1000;
            tv.tv_usec = (timeout % 1000) *1000;
            int ret = select(maxfd, &read_fds, &write_fds, &except_fds, &tv);
            if (ret < 0)
            {
                ERROR("select failed!\n");
                break;
            }
            else if (ret == 0)
            {
                WARN("get venc stream time out, continue\n");
                continue;
            }
            else
            {
                std::map<int, EventSource*>::const_iterator iter = eventSource.begin();
                for (; iter != eventSource.end(); iter++)
                {
                    if (FD_ISSET(iter->first, &read_fds))
                    {
                        Event* e = new Event(EVENT_FLAG_READ);
                        iter->second->OnEvent(e);
                        delete e;
                    }
                    
                    if (FD_ISSET(iter->first, &write_fds))
                    {
                        Event* e = new Event(EVENT_FLAG_WRITE);
                        iter->second->OnEvent(e);
                        delete e;
                    }

                    if (FD_ISSET(iter->first, &except_fds))
                    {
                        Event* e = new Event(EVENT_FLAG_EXCEPT);
                        iter->second->OnEvent(e);
                        delete e;
                    }
                }
            }
        }
    }

}

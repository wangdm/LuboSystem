#include "Event.hpp"


namespace wdm
{

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
        int fd = e->GetFd();
        if (fd >= 0)
        {
            eventSource.insert(std::make_pair(e->GetFd(), e));
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
        std::map<int, EventSource*>::iterator iter = eventSource.find(e->GetFd());
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
                    int fd = iter->second->GetFd();
                    FD_SET(fd, &read_fds);
                    if (fd > maxfd)
                    {
                        maxfd = fd;
                    }
                }

                if (iter->second->haveEventFlag(EVENT_FLAG_WRITE))
                {
                    int fd = iter->second->GetFd();
                    FD_SET(fd, &write_fds);
                    if (fd > maxfd)
                    {
                        maxfd = fd;
                    }
                }

                if (iter->second->haveEventFlag(EVENT_FLAG_EXCEPT))
                {
                    int fd = iter->second->GetFd();
                    FD_SET(fd, &except_fds);
                    if (fd > maxfd)
                    {
                        maxfd = fd;
                    }
                }
            }

            struct timeval tv;
            tv.tv_sec = timeout / 1000;
            tv.tv_usec = (timeout % 1000) * 1000;
            int ret = select(maxfd, &read_fds, &write_fds, &except_fds, &tv);
            if (ret < 0)
            {
                ERROR("Select failed!\n");
                break;
            }
            else if (ret == 0)
            {
                WARN("Select timeout\n");
                continue;
            }
            else
            {
                std::map<int, EventSource*>::const_iterator iter = eventSource.begin();
                for (; iter != eventSource.end(); iter++)
                {
                    if (FD_ISSET(iter->first, &read_fds))
                    {
                        Event* e = new Event(iter->second, EVENT_FLAG_READ);
                        iter->second->OnEvent(e);
                        delete e;
                    }

                    if (FD_ISSET(iter->first, &write_fds))
                    {
                        Event* e = new Event(iter->second, EVENT_FLAG_WRITE);
                        iter->second->OnEvent(e);
                        delete e;
                    }

                    if (FD_ISSET(iter->first, &except_fds))
                    {
                        WARN("Event is except, fd = %d", iter->first);
                        Event* e = new Event(iter->second, EVENT_FLAG_EXCEPT);
                        iter->second->OnEvent(e);
                        delete e;
                    }
                }
            }
        }
    }

}
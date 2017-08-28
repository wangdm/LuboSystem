
#include <WinSock2.h>

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


    EventType Event::GetEventType()
    {
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

    protected:
        virtual void OnLoop() override;

    private:
        virtual bool Listen();

        std::vector<Event*> events;

        fd_set readset;
        fd_set writeset;
        fd_set exceptset;

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
        switch (e->GetEventType())
        {
        case EVENT_TYPE_READ:
            break;
        default:
            break;
        }
    }


    void SelectEventListener::DelEvent(Event* e)
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

            Listen();

        }
    }


    bool SelectEventListener::Listen()
    {
        return false;
    }


    //////////////////////////////////////////////////////////////////////////
    // EventListener
    //////////////////////////////////////////////////////////////////////////

    static EventListener* CreateEventListener(const std::string& type)
    {
    }

}
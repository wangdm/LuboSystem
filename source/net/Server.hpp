#ifndef _WDM_NET_SERVER_H_
#define _WDM_NET_SERVER_H_


#include "../core/event/Event.hpp"
#include "Acceptor.hpp"

namespace wdm
{
    class Server
    {
    public:
        Server();
        Server(std::string& ip, std::string& port);
        virtual ~Server();

        virtual void SetIp(const std::string& ip);
        virtual void SetPort(const std::string& port);
        virtual void SetListenerCount(const int count);

        virtual void Start();
        virtual void Stop();

    private:
        std::string _ip;
        std::string _port;

        Acceptor _acceptor;
        int _listenerCount;

        std::vector<EventListener*> _listener;
    };
}

#endif

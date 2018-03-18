#ifndef _WDM_NET_ACCEPTOR_H_
#define _WDM_NET_ACCEPTOR_H_


#include "../core/Platform.hpp"

#include "Socket.hpp"
#include "BaseSocket.hpp"

namespace wdm
{
    class Acceptor : public BaseSocket
    {
    public:
        Acceptor();
        Acceptor(const std::string& ip, const std::string& port);
        virtual ~Acceptor();

        virtual int Bind(const std::string& ip, const std::string& port);
        virtual int Bind();
        virtual int Listen();
        virtual Socket* Accecpt();

    };

}

#endif

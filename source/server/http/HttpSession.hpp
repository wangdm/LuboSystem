#ifndef _HTTP_SESSION_H_
#define _HTTP_SESSION_H_

#include "../../net/Socket.hpp"

#define MAX_RECV_BUFFER     (1024*5)

namespace wdm
{

    class HttpServer;

    class HttpSession
    {
    public:
        HttpSession(Socket* socket);
        virtual ~HttpSession();

        virtual void SetServer(HttpServer* server);
        virtual HttpServer* GetServer() const;

    private:
        Socket* _socket;

        HttpServer* _server;

    };

}


#endif

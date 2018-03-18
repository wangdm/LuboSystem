#ifndef _HTTP_SERVER_H_
#define _HTTP_SERVER_H_

#include "../../core/event/Event.hpp"

#include "../../net/Acceptor.hpp"

#include "HttpHandler.hpp"
#include "HttpFilter.hpp"
#include "HttpSession.hpp"
#include "HttpParser.hpp"

namespace wdm
{

    class HttpServer : public EventHandler
    {
    private:
        HttpServer();

    public:
        virtual ~HttpServer();

        static HttpServer* GetInstance();

        virtual int AddAcceptor(const std::string& ip, const std::string& port);
        virtual int AddAcceptor(const Address& address);

        virtual void AddHandler(HttpHandler* handler);
        virtual void AddFilter(HttpFilter* filter);

        virtual int SetRootPath(const std::string& path);

        virtual int Start();
        virtual int Stop();

        virtual void handleEvent(Event* e) override;

    private:
        int Listen();
        void handleAccept(Acceptor* acceptor);
        void handleRequest(Socket* socket);

    private:
        static HttpServer* instance;

        HttpParser parse;

        EventListener* _listener;
        std::vector<Acceptor*> _acceptors;

        std::vector<HttpHandler*> _handlers;
        std::vector<HttpFilter*> _filters;

        std::vector<HttpSession*> _sessions;

        std::string _rootpath;

    };

}


#endif _HTTP_SERVER_H_
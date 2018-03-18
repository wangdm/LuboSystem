#include "HttpServer.hpp"

namespace wdm
{

    HttpServer::HttpServer()
        : _listener(nullptr)
    {
        _listener = EventListener::CreateEventListener("select");
    }


    HttpServer::~HttpServer()
    {
        if (_listener != nullptr)
        {
            delete _listener;
            _listener = nullptr;
        }
    }


    HttpServer* HttpServer::instance = new HttpServer();
    HttpServer* HttpServer::GetInstance() {
        return instance;
    }


    int HttpServer::AddAcceptor(const std::string& ip, const std::string& port)
    {
        Acceptor* acceptor = new Acceptor(ip, port);
        if (acceptor != nullptr)
        {
            _acceptors.push_back(acceptor);
        }
        return 0;
    }


    int HttpServer::AddAcceptor(const Address& address)
    {
        Acceptor* acceptor = new Acceptor();
        if (acceptor != nullptr)
        {
            acceptor->SetAddress(address);
            _acceptors.push_back(acceptor);
        }
        return 0;
    }


    void HttpServer::AddHandler(HttpHandler* handler)
    {
        _handlers.push_back(handler);
    }


    void HttpServer::AddFilter(HttpFilter* filter)
    {
        _filters.push_back(filter);
    }


    int HttpServer::SetRootPath(const std::string& path)
    {
        _rootpath = path;
        return 0;
    }


    int HttpServer::Start()
    {
        Listen();
        _listener->Start();
        return 0;
    }


    int HttpServer::Stop()
    {
        return 0;
    }


    void HttpServer::handleEvent(Event* e)
    {
        Acceptor* acceptor = dynamic_cast<Acceptor*>(e->GetEventSource());
        if (acceptor != nullptr)
        {
            return handleAccept(acceptor);
        }

        Socket* socket = dynamic_cast<Socket*>(e->GetEventSource());
        if (socket != nullptr)
        {
            if (e->haveEventFlag(EVENT_FLAG_READ))
            {
                return handleRequest(socket);
            }
            else
            {

            }
        }
    }


    ///////////////////////////////////////////////////////////////////////////
    // Private method
    ///////////////////////////////////////////////////////////////////////////
    int HttpServer::Listen()
    {
        std::vector<Acceptor*>::const_iterator itor = _acceptors.begin();
        for (; itor!=_acceptors.end(); itor++)
        {
            (*itor)->SetNonBlock(true);
            (*itor)->Bind();
            (*itor)->Listen();

            (*itor)->SetEventFlag(EVENT_FLAG_READ | EVENT_FLAG_EXCEPT);
            (*itor)->SetEventHandler(this);

            _listener->AddEventSource(*itor);
        }

        return 0;
    }


    void HttpServer::handleAccept(Acceptor* acceptor)
    {
        Socket* socket = acceptor->Accecpt();
        if (socket==nullptr)
        {
            ERROR("Accept failed!");
            return;
        }

        HttpSession* session = new HttpSession(socket);
        session->SetServer(this);

        socket->SetNonBlock(true);

        socket->SetEventFlag(EVENT_FLAG_READ | EVENT_FLAG_EXCEPT);
        socket->SetEventHandler(this);

        _listener->AddEventSource(socket);
        _sessions.push_back(session);
    }


    void HttpServer::handleRequest(Socket* socket)
    {
        HttpSession* session = (HttpSession*)socket->GetEventData();

        char buffer[MAX_RECV_BUFFER];
        int size = socket->Read(buffer, MAX_RECV_BUFFER);

        HttpRequest* request = parse.Parse(buffer, size);
        if (request == nullptr)
        {

        }
    }
}
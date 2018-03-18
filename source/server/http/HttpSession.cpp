#include "HttpSession.hpp"


namespace wdm
{

    HttpSession::HttpSession(Socket* socket)
        :_socket(socket)
    {
        _socket->SetEventData(this);
    }


    HttpSession::~HttpSession()
    {
        if (_socket!=nullptr)
        {
            delete _socket;
            _socket = nullptr;
        }
    }


    void HttpSession::SetServer(HttpServer* server)
    {
        _server = server;
    }


    HttpServer* HttpSession::GetServer() const
    {
        return _server;
    }

}

#include "Server.hpp"


namespace wdm
{

    Server::Server()
    {
    }


    Server::Server(std::string& ip, std::string& port)
    {
        _ip = ip;
        _port = port;
    }


    Server::~Server()
    {
    }


    void Server::SetIp(const std::string& ip)
    {
        _ip = ip;
    }


    void Server::SetPort(const std::string& port)
    {
        _port = port;
    }


    void Server::SetListenerCount(const int count)
    {
        _listenerCount = count;
    }


    void Server::Start()
    {
        _acceptor.Bind(_ip, _port);
        _acceptor.Listen();

        std::vector<EventListener*>::const_iterator itor = _listener.begin();
        for (; itor!=_listener.end() ; itor++)
        {
            (*itor)->Start();
        }

    }


    void Server::Stop()
    {
        std::vector<EventListener*>::const_iterator itor = _listener.begin();
        for (; itor != _listener.end(); itor++)
        {
            (*itor)->Stop();
        }
    }

}
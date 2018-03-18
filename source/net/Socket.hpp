#ifndef _WDM_NET_SOCKET_H_
#define _WDM_NET_SOCKET_H_


#include "../core/Platform.hpp"

#include "BaseSocket.hpp"

namespace wdm
{
    class Socket : public BaseSocket
    {
    public:
        virtual ~Socket() {};

        virtual int Connect(const std::string& ip, const std::string& port) { return -1; }
        virtual int Connect() { return -1; }

        virtual int Write(char * buf, int size) = 0;
        virtual int Read(char * buf, int size) = 0;

    };


    class TcpSocket : public Socket
    {
    public:
        TcpSocket();
        TcpSocket(const std::string& ip, const std::string& port);
        TcpSocket(const in_addr_t ip, const in_port_t port);
        virtual ~TcpSocket();

        virtual int Connect(const std::string& ip, const std::string& port);
        virtual int Connect();

        virtual int Write(char * buf, int size);
        virtual int Read(char * buf, int size);

    };


    class UdpSocket : public Socket
    {
    public:
        UdpSocket();
        UdpSocket(const std::string& ip, const std::string& port);
        UdpSocket(const in_addr_t ip, const in_port_t port);
        virtual ~UdpSocket();

        virtual int Write(char * buf, int size);
        virtual int Read(char * buf, int size);

    };
}

#endif

#include "Socket.hpp"

namespace wdm
{

    UdpSocket::UdpSocket()
    {
        int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        SetFd(fd);
    }


    UdpSocket::UdpSocket(const std::string& ip, const std::string& port)
        :UdpSocket()
    {
        SetIp(ip);
        SetPort(port);
    }


    UdpSocket::UdpSocket(const in_addr_t ip, const in_port_t port)
    {
    }


    UdpSocket::~UdpSocket()
    {
        Close();
    }


    int UdpSocket::Write(char * buf, int size)
    {
        return send(GetFd(), buf, size, 0);
    }


    int UdpSocket::Read(char * buf, int size)
    {
        return recv(GetFd(), buf, size, 0);
    }

}
#include "Socket.hpp"


namespace wdm
{

    TcpSocket::TcpSocket()
    {
        int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        SetFd(fd);
    }


    TcpSocket::TcpSocket(const std::string& ip, const std::string& port)
        :TcpSocket()
    {
        SetIp(ip);
        SetPort(port);
    }


    TcpSocket::TcpSocket(const in_addr_t ip, const in_port_t port)
    {
        Address address(ip, port);
        SetAddress(address);
    }


    TcpSocket::~TcpSocket()
    {
        Close();
    }


    int TcpSocket::Connect(const std::string& ip, const std::string& port)
    {
        SetIp(ip);
        SetPort(port);

        return Connect();
    }


    int TcpSocket::Connect()
    {
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(sockaddr_in));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = GetAddress()->GetNetIp();
        addr.sin_port = GetAddress()->GetNetPort();
        int ret = connect(GetFd(), (sockaddr *)&addr, sizeof(sockaddr_in));
        return ret;
    }


    int TcpSocket::Write(char * buf, int size)
    {
        return send(GetFd(), buf, size, 0);
    }


    int TcpSocket::Read(char * buf, int size)
    {
        return recv(GetFd(), buf, size, 0);
    }


}
#include "Acceptor.hpp"


namespace wdm
{

    Acceptor::Acceptor()
    {
        int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        SetFd(fd);
    }


    Acceptor::Acceptor(const std::string& ip, const std::string& port)
        :Acceptor()
    {
        SetIp(ip);
        SetPort(port);
    }


    Acceptor::~Acceptor()
    {
        Close();
    }


    int Acceptor::Bind(const std::string& ip, const std::string& port)
    {
        SetIp(ip);
        SetPort(port);

        return Bind();
    }


    int Acceptor::Bind()
    {
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(sockaddr_in));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = GetAddress()->GetNetIp();
        addr.sin_port = GetAddress()->GetNetPort();
        int ret = bind(GetFd(), (sockaddr *)&addr, sizeof(sockaddr_in));
        return ret;
    }


    int Acceptor::Listen()
    {
        return listen(GetFd(), 0);
    }


    Socket* Acceptor::Accecpt()
    {
        struct sockaddr_in addr;
        int addr_len = sizeof(sockaddr_in);
        Socket* sock = nullptr;

        int conn = accept(GetFd(), (struct sockaddr*)&addr, &addr_len);
        if (conn>0){
            sock = new TcpSocket(addr.sin_addr.s_addr, addr.sin_port);
            sock->SetFd(conn);
        }
        else {
            perror("dddd");
        }

        return sock;
    }

}
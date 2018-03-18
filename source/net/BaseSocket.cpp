#include "BaseSocket.hpp"


namespace wdm
{

    BaseSocket::BaseSocket()
    {
    }


    BaseSocket::~BaseSocket()
    {
        Close();
    }


    void BaseSocket::SetIp(const std::string& ip)
    {
        address.SetIp(ip);
    }


    void BaseSocket::SetPort(const std::string& port)
    {
        address.SetPort(port);
    }


    void BaseSocket::SetAddress(const Address& addr)
    {
        address = addr;
    }


    const Address* BaseSocket::GetAddress() const
    {
        return &address;
    }


    int BaseSocket::Close()
    {
        if (_fd != -1)
        {
            shutdown(_fd, 2);
#ifdef WIN32
            closesocket(_fd);
#else
            close(_fd);
#endif
            _fd = -1;
        }
        return -1;
    }


    int BaseSocket::SetRecvBufferSize(size_t size)
    {
        int ret = setsockopt(_fd, SOL_SOCKET, SO_RCVBUF, (const char *)&size, sizeof(size));
        return ret;
    }


    int BaseSocket::SetSendBufferSize(size_t size)
    {
        int ret = setsockopt(_fd, SOL_SOCKET, SO_SNDBUF, (const char *)&size, sizeof(size));
        return ret;
    }


    int BaseSocket::SetBufferSize(size_t rcv_size, size_t snd_size)
    {
        if (rcv_size > 0)
        {
            SetRecvBufferSize(rcv_size);
        }

        if (snd_size > 0)
        {
            SetSendBufferSize(snd_size);
        }

        return 0;
    }


    int BaseSocket::SetNonBlock(bool block)
    {
#ifdef WIN32
        unsigned long mode = 0;
        if (block){
            mode = 1;
        }else{
            mode = 0;
        }
        ioctlsocket(_fd, FIONBIO, &mode);
#else
        if (block) {
            int flags = fcntl(socket, F_GETFL, 0);
            fcntl(socket, F_SETFL, flags | O_NONBLOCK);
        }
        else {
            int flags = fcntl(socket, F_GETFL, 0);
            fcntl(socket, F_SETFL, flags & ~O_NONBLOCK);
        }
#endif
        return 0;
    }


    int BaseSocket::SetSecure(bool secure)
    {
        _secure = secure;
        return 0;
    }


    bool BaseSocket::IsBlock() const
    {
        return _block;
    }


    bool BaseSocket::IsSecure() const
    {
        return _secure;
    }


    int BaseSocket::GetFd() const
    {
        return _fd;
    }


    void BaseSocket::SetFd(int fd)
    {
        _fd = fd;
    }

}
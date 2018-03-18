#ifndef _WDM_NET_BASESOCKET_H_
#define _WDM_NET_BASESOCKET_H_


#include "../core/Platform.hpp"
#include "../core/event/Event.hpp"

#include "Address.hpp"

namespace wdm
{
    class BaseSocket : public EventSource
    {
    public:
        BaseSocket();
        virtual ~BaseSocket();

        virtual void SetIp(const std::string& ip);
        virtual void SetPort(const std::string& port);
        virtual void SetAddress(const Address& addr);
        virtual const Address* GetAddress() const;

        virtual int Close();

        virtual int SetRecvBufferSize(size_t size);
        virtual int SetSendBufferSize(size_t size);
        virtual int SetBufferSize(size_t rcv_size, size_t snd_size);

        virtual int SetNonBlock(bool block);
        virtual int SetSecure(bool secure);

        virtual bool IsBlock() const;
        virtual bool IsSecure() const;

        virtual int GetFd() const;
        virtual void SetFd(int fd);

    private:

        Address address;

        int _fd;

        bool _block;
        bool _secure;
    };
}

#endif

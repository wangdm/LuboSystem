#ifndef _WDM_NET_ADDRESS_H_
#define _WDM_NET_ADDRESS_H_


#include "../core/Platform.hpp"

typedef unsigned long in_addr_t;
typedef unsigned short in_port_t;

namespace wdm
{
    class Address
    {
    public:
        Address();
        Address(const std::string& ip, const std::string& port);
        Address(const in_addr_t ip, const in_port_t port);
        ~Address();

        void SetIp(const std::string& ip);
        void SetPort(const std::string& port);

        std::string GetIp() const;
        std::string GetPort() const;

        void SetNetIp(const in_addr_t ip);
        void SetNetPort(const in_port_t port);

        in_addr_t GetNetIp() const;
        in_port_t GetNetPort() const;


    private:
        std::string strIP;
        std::string strPort;

        in_addr_t  _ip;
        in_port_t  _port;
    };
}

#endif

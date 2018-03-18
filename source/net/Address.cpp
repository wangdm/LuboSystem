#include "Address.hpp"


namespace wdm
{

    Address::Address()
    {
    }


    Address::Address(const std::string& ip, const std::string& port)
        :Address()
    {
        SetIp(ip);
        SetPort(port);
    }


    Address::Address(const in_addr_t ip, const in_port_t port)
    {
        SetNetIp(ip);
        SetNetPort(port);
    }


    Address::~Address()
    {
    }
    
    
    void Address::SetIp(const std::string& ip)
    {
        strIP = ip;
        _ip = inet_addr(strIP.c_str());
    }


    void Address::SetPort(const std::string& port)
    {
        strPort = port;
        _port = htons(std::stoi(strPort));
    }


    std::string Address::GetIp() const
    {
        return strIP;
    }


    std::string Address::GetPort() const
    {
        return strPort;
    }


    void Address::SetNetIp(const in_addr_t addr)
    {
        _ip = addr;
        struct in_addr in;
        in.s_addr = addr;
        char*p = inet_ntoa(in);

        strIP = p;
    }


    void Address::SetNetPort(const in_port_t port)
    {
        _port = port;
        strPort = std::to_string(_port);
    }


    in_addr_t Address::GetNetIp() const
    {
        return _ip;
    }


    in_port_t Address::GetNetPort() const
    {
        return _port;
    }

}
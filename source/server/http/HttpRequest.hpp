#ifndef _HTTP_REQUEST_H_
#define _HTTP_REQUEST_H_

#include "HttpCommon.hpp"
#include "HttpSession.hpp"

namespace wdm
{

    class HttpRequest
    {
    public:
        HttpRequest();
        virtual ~HttpRequest();

        virtual int SetHeader(const std::string& name, const std::string& value);
        virtual int GetHeader(const std::string& name, std::string& value);
        virtual int RemoveHeader(const std::string& name);

        virtual int SetParameter(const std::string& name, const std::string& value);
        virtual int GetParameter(const std::string& name, std::string& value);
        virtual int RemoveParameter(const std::string& name);


    public:
        HttpSession* session;

        HttpMethod method;
        HttpVersion version;
        std::string uri;

    private:
        std::map<std::string, std::string> _headers;
        std::map<std::string, std::string> _parameters;

        char* _body;

    };

}


#endif

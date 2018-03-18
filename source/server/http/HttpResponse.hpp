#ifndef _HTTP_RESPONSE_H_
#define _HTTP_RESPONSE_H_


#include "HttpCommon.hpp"
#include "HttpSession.hpp"

namespace wdm
{

    class HttpResponse
    {
    public:
        HttpResponse();
        virtual ~HttpResponse();

        virtual int SetHeader(const std::string& name, const std::string& value);
        virtual int GetHeader(const std::string& name, std::string& value);
        virtual int RemoveHeader(const std::string& name);
        

    public:
        HttpSession* session;

        HttpVersion version;
        HttpStatus status;
        std::string desc;

    private:
        std::map<std::string, std::string> _headers;

        char* _body;

    };

}


#endif

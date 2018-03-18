#ifndef _HTTP_PARSER_H_
#define _HTTP_PARSER_H_

#include "HttpRequest.hpp"

namespace wdm
{

    class HttpParser
    {
    public:
        HttpParser();
        virtual ~HttpParser();

        virtual HttpRequest* Parse(const char* buf, int size);

    private:
        bool ParseStartLine();
        bool ParseHeader();
        bool ParseBody();

    private:
        const char* _buf;
        int _size;
        int _pos;

        HttpRequest* _request;
    };

}


#endif

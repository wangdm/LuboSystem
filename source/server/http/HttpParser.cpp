#include "HttpParser.hpp"

#include "../../core/Log.hpp"


namespace wdm
{

    HttpParser::HttpParser()
    {
    }


    HttpParser::~HttpParser()
    {
    }


    HttpRequest* HttpParser::Parse(const char* buf, int size)
    {
        _request = new HttpRequest();
        if (_request == nullptr)
        {
            return nullptr;
        }

        _buf = buf;
        _size = size;
        _pos = 0;

        TRACE(_buf);

        bool ret = ParseStartLine();
        if (!ret)
        {
            delete _request;
            return nullptr;
        }

        do 
        {
            ret = ParseHeader();
        } while (ret);

        return _request;
    }


    bool HttpParser::ParseStartLine()
    {
        return true;
    }


    bool HttpParser::ParseHeader()
    {
        return false;
    }


    bool HttpParser::ParseBody()
    {
        return true;
    }

}

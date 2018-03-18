#include "HttpRequest.hpp"


namespace wdm
{

    HttpRequest::HttpRequest()
    {
    }


    HttpRequest::~HttpRequest()
    {
    }


    int HttpRequest::SetHeader(const std::string& name, const std::string& value)
    {
        return 0;
    }


    int HttpRequest::GetHeader(const std::string& name, std::string& value)
    {
        return 0;
    }


    int HttpRequest::RemoveHeader(const std::string& name)
    {
        return 0;
    }


    int HttpRequest::SetParameter(const std::string& name, const std::string& value)
    {
        return 0;
    }


    int HttpRequest::GetParameter(const std::string& name, std::string& value)
    {
        return 0;
    }


    int HttpRequest::RemoveParameter(const std::string& name)
    {
        return 0;
    }


}

#include "HttpResponse.hpp"


namespace wdm
{

    HttpResponse::HttpResponse()
    {
    }


    HttpResponse::~HttpResponse()
    {
    }


    int HttpResponse::SetHeader(const std::string& name, const std::string& value)
    {
        return 0;
    }


    int HttpResponse::GetHeader(const std::string& name, std::string& value)
    {
        return 0;
    }


    int HttpResponse::RemoveHeader(const std::string& name) 
    {
        return 0;
    }

}

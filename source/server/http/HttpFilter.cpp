#include "HttpFilter.hpp"


namespace wdm
{

    HttpFilter::HttpFilter()
    {
    }


    HttpFilter::~HttpFilter()
    {
    }


    bool HttpFilter::BeforeHandler(HttpRequest& request, HttpResponse& response)
    {
        return true;
    }


    void HttpFilter::AfterHandler(HttpRequest& request, HttpResponse& response)
    {
    }

}

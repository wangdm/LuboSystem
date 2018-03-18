#ifndef _HTTP_FILTER_H_
#define _HTTP_FILTER_H_


#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

namespace wdm
{

    class HttpFilter
    {
    public:
        HttpFilter();
        virtual ~HttpFilter();

        virtual bool BeforeHandler(HttpRequest& request, HttpResponse& response);
        virtual void AfterHandler(HttpRequest& request, HttpResponse& response);

    private:

    };

}


#endif

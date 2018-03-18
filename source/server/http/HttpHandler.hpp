#ifndef _HTTP_HANDLER_H_
#define _HTTP_HANDLER_H_


#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

namespace wdm
{

    class HttpHandler
    {
    public:
        HttpHandler();
        virtual ~HttpHandler();

        virtual void DoHandler(HttpRequest& request, HttpResponse& response);

    private:

    };

}


#endif

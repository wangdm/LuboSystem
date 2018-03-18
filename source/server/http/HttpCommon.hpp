#ifndef _HTTP_ERROR_H_
#define _HTTP_ERROR_H_


#include "../../core/Platform.hpp"

namespace wdm
{

    enum HttpVersion
    {
        HTTP_10,
        HTTP_11
    };

    enum HttpMethod
    {
        HTTP_GET = 0,
        HTTP_POST,
        HTTP_PUT,
        HTTP_DELETE
    };

    enum HttpStatus
    {
        S_200 = 200,

        S_300 = 300,

        S_400 = 400,

        S_500 = 500
    };

}


#endif

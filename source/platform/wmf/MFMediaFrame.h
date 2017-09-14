/*
* Author：王德明
* Email：phight@163.com
* QQ群：220954528
*/

#pragma once

#include "../platform.hpp"

#ifdef PLATFORM_WMF

#include "platform.hpp"

#include "../../channel/Capture.hpp"
#include "../../media/MediaFrame.hpp"

namespace wdm {

    class MFMediaFrame : public MediaFrame
    {
    public:
        MFMediaFrame(IMFMediaBuffer* pBuffer, MediaType type, void* attribute);
        ~MFMediaFrame();

    private:
        void Inversion();

    };

}

#endif
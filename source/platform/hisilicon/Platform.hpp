#ifndef _PLATFORM_WMF_H_
#define _PLATFORM_WMF_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <mutex>
#include <string>
#include <sstream>

#include "hi3531a/mpi_sys.h"
#include "hi3531a/mpi_vb.h"
#include "hi3531a/mpi_vi.h"
#include "hi3531a/mpi_vpss.h"

#include "../../base/Property.hpp"
#include "../../base/Log.hpp"
#include "../../media/MediaType.hpp"

#include "HisiError.hpp"
#include "HisiResource.hpp"

namespace wdm {

    template <class T> void SafeRelease(T **ppT)
    {
        if (*ppT)
        {
            (*ppT)->Release();
            *ppT = NULL;
        }
    }


    enum CAPTURE_STATUS_E
    {
        CAPTURE_STATUS_STOP = 0,
        CAPTURE_STATUS_START
    };


    bool IsPropertyMatch(const Property& prop, VideoAttribute* attrivute);
    bool IsPropertyMatch(const Property& prop, AudioAttribute* attrivute);

    void PropertyFromAttribute(Property& prop, const VideoAttribute* attrivute);
    void PropertyToAttribute(const Property& prop, VideoAttribute* attrivute);

    void PropertyFromAttribute(Property& prop, const AudioAttribute* attrivute);
    void PropertyToAttribute(const Property& prop, AudioAttribute* attrivute);

}

#endif

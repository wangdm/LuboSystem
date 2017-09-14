#ifndef _PLATFORM_WMF_H_
#define _PLATFORM_WMF_H_

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <mferror.h>
#include <shlwapi.h>

#include "../../base/Property.hpp"
#include "../../media/MediaType.hpp"


namespace wdm {

    template <class T> void SafeRelease(T **ppT)
    {
        if (*ppT)
        {
            (*ppT)->Release();
            *ppT = NULL;
        }
    }


    struct VideoAttribute {
        GUID format;
        int width;
        int stride;
        int height;
        int fps;
    };


    struct AudioAttribute {
        GUID format;
        int channel;
        int samplerate;
        int bitwide;
    };


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

    bool MediaFormatToGUID(const MediaFormat& format, GUID& guid);
    bool GUIDToMediaFormat(const GUID& guid, MediaFormat& format);

}

#endif

/*
* Author：王德明
* Email：phight@163.com
* QQ群：220954528
*/



#include "../platform.hpp"

#ifdef PLATFORM_WMF

#include "Platform.hpp"
#include "MFMediaFrame.h"
#include "AudioCapture.h"


namespace wdm {

    MFMediaFrame::MFMediaFrame(IMFMediaBuffer* pBuffer, MediaType type, void* attribute)
        : MediaFrame(type, MEDIA_FORMAT_NV12)
    {
        DWORD bufferSize = 0;
        BYTE* pData = NULL;
        pBuffer->GetCurrentLength(&bufferSize);
        _dataSize = bufferSize;
        _data = (BYTE*)malloc(_dataSize);

        if (GetFrameType() == MEDIA_TYPE_VIDEO)
        {
            VideoAttribute* pattr = (VideoAttribute*)attribute;
            LONG lStride = (LONG)pattr->stride;
            // Helper object to lock the video buffer.

            // Lock the video buffer. This method returns a pointer to the first scan line
            // in the image, and the stride in bytes.
            pBuffer->Lock(&pData, NULL, NULL);
            memcpy(_data, pData, _dataSize);
            pBuffer->Unlock();

            format = pattr->format;
            width = pattr->width;
            height = pattr->height;
            if (lStride < 0) {
                stride = 0 - lStride;
                Inversion();
            }
            else {
                stride = lStride;
            }
        }
        else if (GetFrameType() == MEDIA_TYPE_AUDIO) {
            AudioAttribute* pattr = (AudioAttribute*)attribute;
            format = pattr->format;
            samplerate = pattr->samplerate;
            channels = pattr->channel;
            samplebit = pattr->bitwide;
            pBuffer->Lock(&pData, NULL, NULL);
            memcpy(_data, pData, _dataSize);
            pBuffer->Unlock();
        }

    }


    MFMediaFrame::~MFMediaFrame()
    {
    }


    void MFMediaFrame::Inversion()
    {
        BYTE *pData = (BYTE*)malloc(_dataSize);

        for (uint32_t i = 0; i < height; i++)
        {
            BYTE *pDst = &pData[i*stride];
            BYTE *pSrc = &_data[(height - i - 1)*stride];
            memcpy(pDst, pSrc, stride);
        }
        free(_data);
        _data = pData;
    }

}

#endif

#include "../platform.hpp"

#ifdef PLATFORM_WMF

#include "Platform.hpp"
#include "VideoCapture.h"
#include "AudioCapture.h"

//#pragma comment(lib,"ws2_32.lib")

namespace wdm {

    std::vector<Capture*> Platform::audioCaptures;
    std::vector<Capture*> Platform::videoCaptures;

    bool Platform::Init(const std::string& config)
    {
        // 初始化Media Foundation
        HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        if (SUCCEEDED(hr))
        {
            hr = MFStartup(MF_VERSION);
        }
        //Init Windows Socket
        WSADATA  Ws;
        if (WSAStartup(MAKEWORD(2, 2), &Ws) != 0)
        {
            OutputDebugString(TEXT("Init Windows socket failed!\n"));
        }

        EnumCapture();

        return true;
    }


    void Platform::Uninit()
    {

        std::vector<Capture*>::iterator iter;
        for (iter = videoCaptures.begin(); iter != videoCaptures.end();)
        {
            Capture* capture = *iter;
            iter = videoCaptures.erase(iter);
            delete capture;
        }
        for (iter = audioCaptures.begin(); iter != audioCaptures.end();)
        {
            Capture* capture = *iter;
            iter = audioCaptures.erase(iter);
            delete capture;
        }

        //Cleanup Windows Socket
        WSACleanup();

        // 反初始化 Media Foundation
        MFShutdown();
        CoUninitialize();
    }


    int32_t Platform::EnumCapture()
    {
        HRESULT hr = S_OK;
        IMFAttributes *pAttributes = NULL;
        static IMFActivate **m_ppDevices;

        UINT32 videoCapCnt, audioCapCnt;

        // Enumerate devices.
        hr = MFCreateAttributes(&pAttributes, 1);
        if (SUCCEEDED(hr))
        {
            hr = pAttributes->SetGUID(
                MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
                MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID
                );
        }

        if (SUCCEEDED(hr))
        {
            hr = MFEnumDeviceSources(pAttributes, &m_ppDevices, &videoCapCnt);
            for (UINT32 i = 0; i < videoCapCnt; i++)
            {
                videoCaptures.push_back(new VideoCapture(m_ppDevices[i]));
                SafeRelease(&m_ppDevices[i]);
            }
        }

        SafeRelease(&pAttributes);

        // Enumerate devices.
        hr = MFCreateAttributes(&pAttributes, 1);
        if (SUCCEEDED(hr))
        {
            hr = pAttributes->SetGUID(
                MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
                MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_AUDCAP_GUID
                );
        }

        if (SUCCEEDED(hr))
        {
            hr = MFEnumDeviceSources(pAttributes, &m_ppDevices, &audioCapCnt);
            for (UINT32 i = 0; i < audioCapCnt; i++)
            {
                audioCaptures.push_back(new AudioCapture(m_ppDevices[i]));
                SafeRelease(&m_ppDevices[i]);
            }
        }

        SafeRelease(&pAttributes);

        return (int)(videoCapCnt + audioCapCnt);
    }


    CodecContext* Platform::CreateCondecContext(CodecID id, const std::string& name)
    {
        return nullptr;
    }


    bool IsPropertyMatch(const Property& prop, VideoAttribute* attribute)
    {
        int val;
        prop.GetProperty("width", val);
        if (attribute->width != (int)val)
        {
            return false;
        }

        prop.GetProperty("height", val);
        if (attribute->height != (int)val)
        {
            return false;
        }

        prop.GetProperty("fps", val);
        if (attribute->fps != (int)val)
        {
            return false;
        }

        prop.GetProperty("stride", val);
        if (attribute->stride != (int)val)
        {
            return false;
        }

        prop.GetProperty("format", val);
        if (attribute->format != (int)val)
        {
            return false;
        }

        return true;
    }


    bool IsPropertyMatch(const Property& prop, AudioAttribute* attribute)
    {
        int val;
        prop.GetProperty("samplerate", val);
        if (attribute->samplerate != (int)val)
        {
            return false;
        }

        prop.GetProperty("channel", val);
        if (attribute->channel != (int)val)
        {
            return false;
        }

        prop.GetProperty("bitwide", val);
        if (attribute->bitwide != (int)val)
        {
            return false;
        }

        prop.GetProperty("format", val);
        if (attribute->format != (int)val)
        {
            return false;
        }

        return true;
    }



    void PropertyFromAttribute(Property& prop, const VideoAttribute* attribute)
    {
        prop.SetProperty("width", attribute->width);
        prop.SetProperty("height", attribute->height);
        prop.SetProperty("stride", attribute->stride);
        prop.SetProperty("fps", attribute->fps);
        prop.SetProperty("format", attribute->format);
    }


    void PropertyToAttribute(const Property& prop, VideoAttribute* attribute)
    {
        int val;

        if (prop.GetProperty("width", val))
        {
            attribute->width = val;
        }

        if (prop.GetProperty("height", val))
        {
            attribute->height = val;
        }

        if (prop.GetProperty("fps", val))
        {
            attribute->fps = val;
        }

        if (prop.GetProperty("stride", val))
        {
            attribute->stride = val;
        }

        if (prop.GetProperty("format", val))
        {
            attribute->format = (MediaFormat)val;
        }
    }


    void PropertyFromAttribute(Property& prop, const AudioAttribute* attribute)
    {
        prop.SetProperty("samplerate", attribute->samplerate);
        prop.SetProperty("channel", attribute->channel);
        prop.SetProperty("bitwide", attribute->bitwide);
        prop.SetProperty("format", attribute->format);
    }


    void PropertyToAttribute(const Property& prop, AudioAttribute* attribute)
    {
        int val;

        if (prop.GetProperty("samplerate", val))
        {
            attribute->samplerate = val;
        }

        if (prop.GetProperty("channel", val))
        {
            attribute->channel = val;
        }

        if (prop.GetProperty("bitwide", val))
        {
            attribute->bitwide = val;
        }

        if (prop.GetProperty("format", val))
        {
            attribute->format = (MediaFormat)val;
        }
    }


    bool MediaFormatToGUID(const MediaFormat& format, GUID& guid)
    {
        switch (format)
        {
        case MEDIA_FORMAT_NV12:
            guid = MFVideoFormat_NV12;
            break;
        case MEDIA_FORMAT_I420:
            guid = MFVideoFormat_I420;
            break;
        case MEDIA_FORMAT_RGB24:
            guid = MFVideoFormat_RGB24;
            break;
        default:
            return false;
        }

        return true;
    }


    bool GUIDToMediaFormat(const GUID& guid, MediaFormat& format)
    {
        if (guid == MFVideoFormat_NV12)
        {
            format = MEDIA_FORMAT_NV12;
        }
        else if (guid == MFVideoFormat_I420)
        {
            format = MEDIA_FORMAT_I420;
        }
        else if (guid == MFVideoFormat_RGB24)
        {
            format = MEDIA_FORMAT_RGB24;
        }
        else
        {
            return false;
        }
        return true;
    }


    GUID MediaFormatToGUID(const MediaFormat& format)
    {
        GUID guid = {0};
        MediaFormatToGUID(format, guid);
        return guid;
    }


    MediaFormat GUIDToMediaFormat(const GUID& guid)
    {
        MediaFormat format = MEDIA_FORMAT_NONE;
        GUIDToMediaFormat(guid,format);
        return format;
    }
    
}


#endif

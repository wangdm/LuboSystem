
#include "../Platform.hpp"

#ifdef PLATFORM_WMF

#include "Platform.hpp"
#include "VICapture.hpp"

//#pragma comment(lib,"ws2_32.lib")

namespace wdm {

    std::vector<Capture*> Platform::audioCaptures;
    std::vector<Capture*> Platform::videoCaptures;

    bool Platform::Init(const std::string& config)
    {
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
    }


    int32_t Platform::EnumCapture()
    {

        return 0;
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
    
}


#endif

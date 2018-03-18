

#ifdef PLATFORM_HISI

#include "Platform.hpp"
#include "VICapture.hpp"
#include "Hi264BindEncodec.hpp"

//#pragma comment(lib,"ws2_32.lib")

namespace wdm {

    std::vector<Capture*> Platform::audioCaptures;
    std::vector<Capture*> Platform::videoCaptures;
    Config* Platform::config = nullptr;

    bool Platform::Init(const std::string& cfile)
    {
        DEBUG("Init platform...");
        HisiErrorInit();
        config = new Config(cfile);

        std::vector<Object*> vConfigs;
        for (int i = 0; i < 4; i++)
        {
            Config* vConfig = new Config();
            (*vConfig)["videv"] = i * 2 + 1;
            (*vConfig)["vichn"] = i * 8 + 4;
            vConfigs.push_back(vConfig);
        }
        config->SetValue("videoCapture", vConfigs);

        HI_S32 s32Ret;
        s32Ret = HI_MPI_SYS_Exit();
        if (HI_SUCCESS != s32Ret)
        {
            ERROR("HI_MPI_SYS_Exit failed with " + HiErr(s32Ret));
        }
        s32Ret = HI_MPI_VB_Exit();
        if (HI_SUCCESS != s32Ret)
        {
            ERROR("HI_MPI_VB_Exit failed with " + HiErr(s32Ret));
        }

        VB_CONF_S stVbConf;
        MPP_SYS_CONF_S stSysConf;

        memset(&stVbConf, 0, sizeof(VB_CONF_S));
        stVbConf.u32MaxPoolCnt = 128;
        stVbConf.astCommPool[0].u32BlkSize = 1920 * 1088 * 2;
        stVbConf.astCommPool[0].u32BlkCnt = 40;
        stVbConf.astCommPool[1].u32BlkSize = 960 * 576 * 2;
        stVbConf.astCommPool[1].u32BlkCnt = 40;
        s32Ret = HI_MPI_VB_SetConf(&stVbConf);
        if (HI_SUCCESS != s32Ret)
        {
            ERROR("HI_MPI_VB_SetConf failed with " + HiErr(s32Ret));
            return s32Ret;
        }
        s32Ret = HI_MPI_VB_Init();
        if (HI_SUCCESS != s32Ret)
        {
            ERROR("HI_MPI_VB_Init failed with " + HiErr(s32Ret));
            return s32Ret;
        }

        memset(&stSysConf, 0, sizeof(MPP_SYS_CONF_S));
        stSysConf.u32AlignWidth = 16;
        s32Ret = HI_MPI_SYS_SetConf(&stSysConf);
        if (HI_SUCCESS != s32Ret)
        {
            ERROR("HI_MPI_SYS_SetConf failed with " + HiErr(s32Ret));
            return s32Ret;
        }
        /* init system*/
        s32Ret = HI_MPI_SYS_Init();
        if (HI_SUCCESS != s32Ret)
        {
            ERROR("HI_MPI_SYS_Init failed with " + HiErr(s32Ret));
            return s32Ret;
        }

        EnumCapture();

        return true;
    }


    void Platform::Uninit()
    {
        /* exit system*/
        HI_S32 s32Ret;
        s32Ret = HI_MPI_SYS_Exit();
        if (HI_SUCCESS != s32Ret)
        {
            ERROR("HI_MPI_SYS_Exit failed with " + HiErr(s32Ret));
        }
        s32Ret = HI_MPI_VB_Exit();
        if (HI_SUCCESS != s32Ret)
        {
            ERROR("HI_MPI_VB_Exit failed with " + HiErr(s32Ret));
        }

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
        DEBUG("Enum capture...");
        uint32_t videoCapCnt = 0;
        std::vector<Config*> vConfigs;
        config->Print();
        if (config->GetValue("videoCapture", vConfigs))
        {
            videoCapCnt = vConfigs.size();
            std::cout << "Total video capture count " << videoCapCnt << std::endl;
            std::for_each(vConfigs.begin(), vConfigs.end(), [](Config* pConfig) {
                videoCaptures.push_back(new VICapture(pConfig));
            });
        }
        std::cout << "Total capture count " << videoCapCnt << std::endl;
        return videoCapCnt;
    }


    CodecContext* Platform::CreateCondecContext(CodecID id, const std::string& name)
    {
        return new Hi264BindEncode();
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

#include "HisiResource.hpp"

namespace wdm
{

    HisiResource::HisiResource()
    {
        for (int i = 0; i < VPSS_MAX_GRP_NUM; i++)
        {
            _vpss[i] = false;
        }
        for (int i = 0; i < VENC_MAX_CHN_NUM; i++)
        {
            _venc[i] = false;
        }
        for (int i = 0; i < VDEC_MAX_CHN_NUM; i++)
        {
            _vdec[i] = false;
        }
    }


    HisiResource::~HisiResource()
    {
    }

    HisiResource* HisiResource::instance = nullptr;
    HisiResource* HisiResource::GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new HisiResource();
        }
        return instance;
    }


    VPSS_GRP HisiResource::GetVPSS()
    {
        std::lock_guard<std::recursive_mutex> lock(vpss_mtx);
        for (int i = 0; i < VPSS_MAX_GRP_NUM; i++)
        {
            if (_vpss[i] == false)
            {
                _vpss[i] = true;
                return i;
            }
        }
        return -1;
    }


    void HisiResource::ReleaseVPSS(VPSS_GRP vpss)
    {
        std::lock_guard<std::recursive_mutex> lock(vpss_mtx);
        if (vpss>=0 || vpss<VPSS_MAX_GRP_NUM)
        {
            _vpss[vpss] = false;
        }
    }


    VENC_CHN HisiResource::GetVenc()
    {
        std::lock_guard<std::recursive_mutex> lock(venc_mtx);
        for (int i = 0; i < VENC_MAX_CHN_NUM; i++)
        {
            if (_venc[i] == false)
            {
                return i;
            }
        }
        return -1;
    }


    void HisiResource::ReleaseVenc(VENC_CHN venc)
    {
        std::lock_guard<std::recursive_mutex> lock(venc_mtx);
        if (venc >= 0 || venc < VENC_MAX_CHN_NUM)
        {
            _venc[venc] = true;
        }
    }


    VDEC_CHN HisiResource::GetVdec()
    {
        std::lock_guard<std::recursive_mutex> lock(vdec_mtx);
        for (int i = 0; i < VDEC_MAX_CHN_NUM; i++)
        {
            if (_vdec[i] == false)
            {
                return i;
            }
        }
        return -1;
    }


    void HisiResource::ReleaseVdec(VDEC_CHN vdec)
    {
        std::lock_guard<std::recursive_mutex> lock(venc_mtx);
        if (vdec >= 0 || vdec < VDEC_MAX_CHN_NUM)
        {
            _venc[vdec] = true;
        }
    }
}


#ifndef _HISI_RESOURCE_H_
#define _HISI_RESOURCE_H_

#include "Platform.hpp"

namespace wdm
{
    class HisiResource
    {
    private:
        HisiResource();
    public:
        ~HisiResource();

        static HisiResource* GetInstance();

        VPSS_GRP GetVPSS();
        void ReleaseVPSS(VPSS_GRP vpss);

        VENC_CHN GetVenc();
        void ReleaseVenc(VENC_CHN venc);

        VENC_CHN GetVdec();
        void ReleaseVdec(VDEC_CHN venc);

    private:
        static HisiResource* instance;

        bool _vpss[VPSS_MAX_GRP_NUM];
        bool _venc[VENC_MAX_CHN_NUM];
        bool _vdec[VDEC_MAX_CHN_NUM];

        std::recursive_mutex vpss_mtx;
        std::recursive_mutex venc_mtx;
        std::recursive_mutex vdec_mtx;

    };

}


#endif

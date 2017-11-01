/*
* Author：王德明
* Email：phight@163.com
* QQ群：220954528
*/

#pragma once

#include "../../channel/Capture.hpp"

namespace wdm {

    class VICapture :
        public Capture
    {

    public:
        VICapture(void * priv);
        ~VICapture();


    private:

        std::vector<VideoAttribute*> m_AttributeList;
        VideoAttribute*    m_pBestAttribute = NULL;
        VideoAttribute*    m_pCurrentAttribute = NULL;

        CAPTURE_STATUS_E         m_Status = CAPTURE_STATUS_STOP;

        std::string                  m_CaptureName;

        VI_DEV  videv;
        VI_CHN  vichn;

        VPSS_GRP vpss;

        VI_DEV_ATTR_S stDevAttr;
        VI_CHN_ATTR_S stChnAttr;

        VPSS_GRP_ATTR_S stVpssAttr;
        VPSS_GRP_PARAM_S stVpssPara;

    private:
        HI_S32 StartVi();
        HI_S32 StartVpss();
        HI_S32 BindViVpss();
        HI_S32 UnBindViVpss();
        HI_S32 StopVpss();
        HI_S32 StopVi();

    public:
        bool IsExistVideo() const override;
        bool GetVideoAttribute(VideoAttribute& attr) const override;

        bool SetProperty(const Property& prop) override;
        bool GetProperty(Property& prop) override;
        bool IsPropertySupport(const Property& prop) override;

        bool Start() override;
        bool Stop() override;
    };

}
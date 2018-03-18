/*
* Author：王德明
* Email：phight@163.com
* QQ群：220954528
*/

#include "../Platform.hpp"

#ifdef PLATFORM_HISI

#include "Platform.hpp"
#include "HisiError.hpp"
#include "VICapture.hpp"
#include "Hi264BindEncodec.hpp"


namespace wdm {

    VICapture::VICapture(void * priv)
    {
        Config* pConfig = (Config*)priv;

        videv = 0;
        vichn = 0;
        VpssGrp = 0;

        videv = (*pConfig)["videv"];
        vichn = (*pConfig)["vichn"];

        std::cout << "Create VICapture " << videv << std::endl;

        memset(&stDevAttr, 0, sizeof(VI_DEV_ATTR_S));
        stDevAttr.enIntfMode = VI_MODE_BT1120_STANDARD;
        stDevAttr.enWorkMode = VI_WORK_MODE_1Multiplex;
        stDevAttr.au32CompMask[0] = 0xFF000000;
        stDevAttr.au32CompMask[1] = 0xFF0000;
        stDevAttr.enClkEdge = VI_CLK_EDGE_SINGLE_UP;
        stDevAttr.enDataSeq = VI_INPUT_DATA_UVUV;
        stDevAttr.s32AdChnId[0] = { -1 };
        stDevAttr.s32AdChnId[1] = { -1 };
        stDevAttr.s32AdChnId[2] = { -1 };
        stDevAttr.s32AdChnId[3] = { -1 };

        memset(&stChnAttr, 0, sizeof(VI_CHN_ATTR_S));
        stChnAttr.stCapRect = {0,0,1920,1080};
        stChnAttr.stDestSize = {1920, 1080};
        stChnAttr.enCapSel = VI_CAPSEL_E::VI_CAPSEL_BOTH;
        stChnAttr.enScanMode = VI_SCAN_MODE_E::VI_SCAN_PROGRESSIVE;
        stChnAttr.enPixFormat = PIXEL_FORMAT_E::PIXEL_FORMAT_YUV_SEMIPLANAR_422;
        stChnAttr.bFlip = HI_FALSE;
        stChnAttr.bMirror = HI_FALSE;
        stChnAttr.s32SrcFrameRate = 60;
        stChnAttr.s32DstFrameRate = 30;

        memset(&stVpssAttr, 0, sizeof(VPSS_GRP_ATTR_S));
        stVpssAttr.enPixFmt = PIXEL_FORMAT_E::PIXEL_FORMAT_YUV_SEMIPLANAR_422;
        stVpssAttr.u32MaxW = 1920;
        stVpssAttr.u32MaxH = 1080;
        stVpssAttr.enDieMode = VPSS_DIE_MODE_NODIE;
        stVpssAttr.bDciEn = HI_FALSE;
        stVpssAttr.bIeEn = HI_FALSE;
        stVpssAttr.bNrEn = HI_FALSE;
        stVpssAttr.bHistEn = HI_FALSE;
        stVpssAttr.bEsEn = HI_FALSE;
    }


    VICapture::~VICapture()
    {
    }


    /////////////// Capture methods ///////////////

    bool VICapture::IsPropertySupport(const Property& prop)
    {
        std::vector<VideoAttribute*>::const_iterator iter;
        for (iter = m_AttributeList.begin(); iter != m_AttributeList.end(); iter++)
        {
            if (IsPropertyMatch(prop, *iter))
            {
                return true;
            }
        }
        return false;
    }


    bool VICapture::SetProperty(const Property& prop)
    {
        if (m_Status == CAPTURE_STATUS_START)
        {
            return false;
        } 
        else if(!IsPropertySupport(prop))
        {
            return false;
        }

        PropertyToAttribute(prop, m_pCurrentAttribute);

        return true;
    }


    bool VICapture::GetProperty(Property& prop)
    {
        PropertyFromAttribute(prop, m_pCurrentAttribute);

        return true;
    }


    //////////////////////////////////////////////////////////////////////////
    // MediaSource
    //////////////////////////////////////////////////////////////////////////

    bool VICapture::IsExistVideo() const
    {
        return true;
    }


    bool VICapture::GetVideoAttribute(VideoAttribute& attr) const
    {
        if (m_pCurrentAttribute)
        {
            attr = *m_pCurrentAttribute;
        }
        else
        {
            attr = *m_pBestAttribute;
        }
        return true;
    }


    bool VICapture::Start()
    {
        HI_S32 s32Ret = HI_SUCCESS;
        if (m_Status != CAPTURE_STATUS_START)
        {
            do 
            {
                StartVi();
                StartVpss();
                BindViVpss();
                BindSink();
            } while (0);
        }


        return true;
    }


    bool VICapture::Stop()
    {
        m_Status = CAPTURE_STATUS_STOP;
        UnBindSink();
        UnBindViVpss();
        StopVpss();
        StartVi();

        return true;
    }


    //////////////////////////////////////////////////////////////////////////
    /// private method
    //////////////////////////////////////////////////////////////////////////
    HI_S32 VICapture::StartVi()
    {
        do 
        {
            HI_S32 s32Ret = HI_SUCCESS;
            s32Ret = HI_MPI_VI_SetDevAttr(videv, &stDevAttr);
            if (s32Ret != HI_SUCCESS)
            {
                ERROR("HI_MPI_VI_SetDevAttr failed with " + HiErr(s32Ret));
                break;
            }

            s32Ret = HI_MPI_VI_EnableDev(videv);
            if (s32Ret != HI_SUCCESS)
            {
                ERROR("HI_MPI_VI_SetDevAttr failed with " + HiErr(s32Ret));
                break;
            }

            s32Ret = HI_MPI_VI_SetChnAttr(vichn, &stChnAttr);
            if (s32Ret != HI_SUCCESS)
            {
                ERROR("HI_MPI_VI_SetDevAttr failed with " + HiErr(s32Ret));
                break;
            }

            s32Ret = HI_MPI_VI_EnableChn(vichn);
            if (s32Ret != HI_SUCCESS)
            {
                ERROR("HI_MPI_VI_SetDevAttr failed with " + HiErr(s32Ret));
                break;
            }
        } while (0);
    }


    HI_S32 VICapture::StartVpss()
    {
        do 
        {
            HI_S32 s32Ret = HI_SUCCESS;
            VpssGrp = HisiResource::GetInstance()->GetVPSS();
            if (VpssGrp < 0)
            {
                ERROR("HI_MPI_VPSS_CreateGrp failed with " + HiErr(s32Ret));
                return HI_FAILURE;
            }

            s32Ret = HI_MPI_VPSS_CreateGrp(VpssGrp, &stVpssAttr);
            if (s32Ret != HI_SUCCESS)
            {
                ERROR("HI_MPI_VPSS_CreateGrp failed with " + HiErr(s32Ret));
                return s32Ret;
            }
            
            s32Ret = HI_MPI_VPSS_GetGrpParam(VpssGrp, &stVpssParam);
            if (s32Ret != HI_SUCCESS)
            {
                ERROR("HI_MPI_VPSS_GetGrpParam failed with " + HiErr(s32Ret));
                return HI_FAILURE;
            }

            stVpssParam.u32Contrast = 32;
            stVpssParam.u32IeStrength = 8;
            s32Ret = HI_MPI_VPSS_SetGrpParam(VpssGrp, &stVpssParam);
            if (s32Ret != HI_SUCCESS)
            {
                ERROR("HI_MPI_VPSS_SetGrpParam failed with " + HiErr(s32Ret));
                return HI_FAILURE;
            }

            s32Ret = HI_MPI_VPSS_StartGrp(VpssGrp);
            if (s32Ret != HI_SUCCESS)
            {
                ERROR("HI_MPI_VPSS_StartGrp failed with " + HiErr(s32Ret));
                return s32Ret;
            }

        } while (0);
    }


    HI_S32 VICapture::BindViVpss()
    {
        HI_S32 s32Ret = HI_SUCCESS;
        MPP_CHN_S stSrcChn;
        MPP_CHN_S stDestChn;

        stSrcChn.enModId = HI_ID_VIU;
        stSrcChn.s32DevId = 0;
        stSrcChn.s32ChnId = vichn;

        stDestChn.enModId = HI_ID_VPSS;
        stDestChn.s32DevId = VpssGrp;
        stDestChn.s32ChnId = 0;

        s32Ret = HI_MPI_SYS_Bind(&stSrcChn, &stDestChn);
        if (s32Ret != HI_SUCCESS)
        {
            ERROR("HI_MPI_SYS_Bind failed with " + HiErr(s32Ret));
            return s32Ret;
        }
    }


    HI_S32 VICapture::UnBindViVpss()
    {
        HI_S32 s32Ret = HI_SUCCESS;
        MPP_CHN_S stSrcChn;
        MPP_CHN_S stDestChn;

        stSrcChn.enModId = HI_ID_VIU;
        stSrcChn.s32DevId = 0;
        stSrcChn.s32ChnId = vichn;

        stDestChn.enModId = HI_ID_VPSS;
        stDestChn.s32DevId = VpssGrp;
        stDestChn.s32ChnId = 0;

        s32Ret = HI_MPI_SYS_UnBind(&stSrcChn, &stDestChn);
        if (s32Ret != HI_SUCCESS)
        {
            ERROR("HI_MPI_SYS_UnBind failed with " + HiErr(s32Ret));
            return s32Ret;
        }
    }


    HI_S32 VICapture::BindSink()
    {
        HI_S32 s32Ret = HI_SUCCESS;
        int vpssCnt = VPSS_MAX_PHY_CHN_NUM - 1;
        int sinkSize = sinks.size();
        int chnCnt = vpssCnt > sinkSize ? sinkSize : vpssCnt;
        for (int i = 0; i < chnCnt; i++)
        {

            Hi264BindEncode* sink = dynamic_cast<Hi264BindEncode*>(sinks[i]);
            if (sink != nullptr && sink->GetSinkMethod() == BIND)
            {
                VPSS_CHN VpssChn = i;
                VPSS_CHN_ATTR_S stChnAttr;
                stChnAttr.bSpEn = HI_FALSE;
                stChnAttr.bUVInvert = HI_FALSE;
                stChnAttr.bBorderEn = HI_FALSE;
                s32Ret = HI_MPI_VPSS_SetChnAttr(VpssGrp, VpssChn, &stChnAttr);
                if (s32Ret != HI_SUCCESS)
                {
                    ERROR("HI_MPI_VPSS_SetChnAttr failed with " + HiErr(s32Ret));
                    return HI_FAILURE;
                }

                s32Ret = HI_MPI_VPSS_EnableChn(VpssGrp, VpssChn);
                if (s32Ret != HI_SUCCESS)
                {
                    ERROR("HI_MPI_VPSS_EnableChn failed with " + HiErr(s32Ret));
                    return HI_FAILURE;
                }

                MPP_CHN_S stSrcChn;
                MPP_CHN_S stDestChn;

                stSrcChn.enModId = HI_ID_VPSS;
                stSrcChn.s32DevId = VpssGrp;
                stSrcChn.s32ChnId = VpssChn;

                if (sink->GetMppChn(stDestChn))
                {
                    s32Ret = HI_MPI_SYS_Bind(&stSrcChn, &stDestChn);
                    if (s32Ret != HI_SUCCESS)
                    {
                        ERROR("HI_MPI_SYS_Bind failed with " + HiErr(s32Ret));
                        return s32Ret;
                    }
                }

            }
        }

        return s32Ret;
    }


    HI_S32 VICapture::UnBindSink()
    {
        HI_S32 s32Ret = HI_SUCCESS;
        int vpssCnt = VPSS_MAX_PHY_CHN_NUM - 1;
        int sinkSize = sinks.size();
        int chnCnt = vpssCnt > sinkSize ? sinkSize : vpssCnt;
        for (int i = 0; i < chnCnt; i++)
        {
            VPSS_CHN VpssChn = i;

            Hi264BindEncode* sink = dynamic_cast<Hi264BindEncode*>(sinks[i]);
            if (sink != nullptr && sink->GetSinkMethod()==BIND)
            {
                MPP_CHN_S stSrcChn;
                MPP_CHN_S stDestChn;

                stSrcChn.enModId = HI_ID_VPSS;
                stSrcChn.s32DevId = VpssGrp;
                stSrcChn.s32ChnId = VpssChn;

                if (sink->GetMppChn(stDestChn))
                {
                    s32Ret = HI_MPI_SYS_Bind(&stSrcChn, &stDestChn);
                    if (s32Ret != HI_SUCCESS)
                    {
                        ERROR("HI_MPI_SYS_Bind failed with " + HiErr(s32Ret));
                        return s32Ret;
                    }
                }

                s32Ret = HI_MPI_VPSS_DisableChn(VpssGrp, VpssChn);
                if (s32Ret != HI_SUCCESS)
                {
                    ERROR("HI_MPI_VPSS_DisableChn failed with " + HiErr(s32Ret));
                    return HI_FAILURE;
                }
            }
        }

        return s32Ret;
    }


    HI_S32 VICapture::StopVpss()
    {
        HI_S32 s32Ret = HI_SUCCESS;

        s32Ret = HI_MPI_VPSS_StopGrp(VpssGrp);
        if (s32Ret != HI_SUCCESS)
        {
            ERROR("HI_MPI_VPSS_StopGrp failed with " + HiErr(s32Ret));
        }

        for (int i = 0; i < VPSS_MAX_CHN_NUM; i++)
        {
            VPSS_CHN VpssChn = i;
            s32Ret = HI_MPI_VPSS_DisableChn(VpssGrp, VpssChn);
            if (s32Ret != HI_SUCCESS)
            {
                ERROR("HI_MPI_VPSS_DisableChn failed with " + HiErr(s32Ret));
            }
        }

        s32Ret = HI_MPI_VPSS_DestroyGrp(VpssGrp);
        if (s32Ret != HI_SUCCESS)
        {
            //ERROR("HI_MPI_VPSS_DestroyGrp[" + vpss + "] failed with " + HiErr(s32Ret));
        }

        HisiResource::GetInstance()->ReleaseVPSS(VpssGrp);
    }


    HI_S32 VICapture::StopVi()
    {
        HI_S32 s32Ret = HI_SUCCESS;

        s32Ret = HI_MPI_VI_DisableChn(vichn);
        if (HI_SUCCESS != s32Ret)
        {
            //ERROR("HI_MPI_VI_DisableChn[" + vichn + "] failed with " + HiErr(s32Ret));
        }

        s32Ret = HI_MPI_VI_DisableDev(videv);
        if (HI_SUCCESS != s32Ret)
        {
            //ERROR("HI_MPI_VI_DisableDev[" + videv + "] failed with " + HiErr(s32Ret));
        }
    }

}

#endif
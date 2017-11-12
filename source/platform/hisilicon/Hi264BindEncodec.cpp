
#include "../Platform.hpp"

#ifdef PLATFORM_HISI

#include "../../channel/MediaStream.hpp"
#include "Platform.hpp"
#include "HisiError.hpp"
#include "HisiResource.hpp"
#include "Hi264BindEncodec.hpp"


namespace wdm {


    Hi264BindEncode::Hi264BindEncode()
    {
        VeChn = HI_INVALID_CHN;
        VencFd = -1;

        event = nullptr;
    }


    Hi264BindEncode::~Hi264BindEncode()
    {
    }

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    void Hi264BindEncode::OnFrame(MediaFrame* frame)
    {
    }


    SinkMethod Hi264BindEncode::GetSinkMethod()
    {
        return BIND;
    }


    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    MediaPacket* Hi264BindEncode::GetMedaiPacket()
    {
        HI_S32 s32Ret = HI_SUCCESS;
        VENC_CHN_STAT_S stStat;
        VENC_STREAM_S stStream;
        MediaPacket* packet = nullptr;

        memset(&stStream, 0, sizeof(stStream));
        s32Ret = HI_MPI_VENC_Query(VeChn, &stStat);
        if (HI_SUCCESS != s32Ret)
        {
            return nullptr;
        }
        if (stStat.u32CurPacks == 0)
        {
            return nullptr;
        }

        stStream.pstPack = new VENC_PACK_S[stStat.u32CurPacks];
        if (stStream.pstPack == nullptr)
        {
            ERROR("Allocate stream pack memery failed");
            return nullptr;
        }
        stStream.u32PackCount = stStat.u32CurPacks;
        s32Ret = HI_MPI_VENC_GetStream(VeChn, &stStream, -1);
        if (s32Ret != HI_SUCCESS)
        {
            std::cout << "HI_MPI_VENC_GetStream failed with " << std::hex << s32Ret << std::endl;
        }
        else
        {
            DEBUG("Get stream ...");
            uint8_t* data = nullptr;
            uint32_t size = 0;
            for (int i = 0; i < stStream.u32PackCount; i++)
            {
                size += stStream.pstPack[i].u32Len - stStream.pstPack[i].u32Offset;
            }
            packet = new MediaPacket(MEDIA_TYPE_VIDEO, size);
            data = packet->GetDataPtr();

            uint32_t copysize = 0;
            for (int i = 0; i < stStream.u32PackCount; i++)
            {
                uint32_t packsize = stStream.pstPack[i].u32Len - stStream.pstPack[i].u32Offset;
                memcpy(data + copysize, stStream.pstPack[i].pu8Addr + stStream.pstPack[i].u32Offset, packsize);
                copysize += packsize;
            }

            packet->width = 1920;
            packet->height = 1080; 
            packet->timestamp = stStream.pstPack->u64PTS;
            if (stStream.pstPack->DataType.enH264EType == H264E_NALU_IPSLICE){
                packet->keyframe = true;
            }else{
                packet->keyframe = false;
            }
            s32Ret = HI_MPI_VENC_ReleaseStream(VeChn, &stStream);
        }

        if (stStream.pstPack != nullptr)
        {
            delete[] stStream.pstPack;
            stStream.pstPack = nullptr;
        }

        return packet;

    }


    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    bool Hi264BindEncode::Start()
    {
        DEBUG("Start Hi264BindEncode...");
        if (StartVenc() != HI_SUCCESS)
        {
            return false;
        }
        return true;
    }


    bool Hi264BindEncode::Stop()
    {
        DEBUG("Stop Hi264BindEncode...");
        if (StopVenc() != HI_SUCCESS)
        {
            return false;
        }
        return true;
    }


    int Hi264BindEncode::GetFD()
    {
        if (VencFd < 0)
        {
            return -1;
        }
        return VencFd;
    }


    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    HI_S32 Hi264BindEncode::StartVenc()
    {
        HI_S32 s32Ret = HI_SUCCESS;

        VeChn = HisiResource::GetInstance()->GetVenc();
        if (VeChn != HI_INVALID_CHN)
        {
            VENC_CHN_ATTR_S stVencChnAttr;
            VENC_ATTR_H264_S stH264Attr;
            VENC_ATTR_H264_CBR_S stH264Cbr;

            stVencChnAttr.stVeAttr.enType = PT_H264;

            stH264Attr.u32MaxPicWidth = 1920;
            stH264Attr.u32MaxPicHeight = 1080;
            stH264Attr.u32PicWidth = 1920;
            stH264Attr.u32PicHeight = 1080;
            stH264Attr.u32BufSize = 1920 * 1080 * 2;
            stH264Attr.u32Profile = 2;  /*0: baseline; 1:MP; 2:HP 3:svc-t */
            stH264Attr.bByFrame = HI_TRUE;/*get stream mode is slice mode or frame mode?*/
            memcpy(&stVencChnAttr.stVeAttr.stAttrH264e, &stH264Attr, sizeof(VENC_ATTR_H264_S));

            stVencChnAttr.stRcAttr.enRcMode = VENC_RC_MODE_H264CBR;
            stH264Cbr.u32StatTime = 1;
            stH264Cbr.u32Gop = 30;
            stH264Cbr.u32SrcFrmRate = 30;
            stH264Cbr.fr32DstFrmRate = 30;
            stH264Cbr.u32BitRate = 1024 * 8;
            stH264Cbr.u32FluctuateLevel = 0;
            memcpy(&stVencChnAttr.stRcAttr.stAttrH264Cbr, &stH264Cbr, sizeof(VENC_ATTR_H264_CBR_S));

            s32Ret = HI_MPI_VENC_CreateChn(VeChn, &stVencChnAttr);
            if (s32Ret != HI_SUCCESS)
            {
                ERROR("HI_MPI_VENC_CreateChn failed with " + HiErr(s32Ret));
                return s32Ret;
            }

            s32Ret = HI_MPI_VENC_StartRecvPic(VeChn);
            if (HI_SUCCESS != s32Ret)
            {
                ERROR("HI_MPI_VENC_StartRecvPic failed with " + HiErr(s32Ret));
                return s32Ret;
            }

            VencFd = HI_MPI_VENC_GetFd(VeChn);

            return HI_SUCCESS;
        }
        return HI_FAILURE;
    }


    HI_S32 Hi264BindEncode::StopVenc()
    {
        HI_S32 s32Ret;
        if (VeChn != HI_INVALID_CHN)
        {
            s32Ret = HI_MPI_VENC_StopRecvPic(VeChn);
            if (HI_SUCCESS != s32Ret)
            {
                ERROR("HI_MPI_VENC_StopRecvPic failed with " + HiErr(s32Ret));
                return s32Ret;
            }

            s32Ret = HI_MPI_VENC_DestroyChn(VeChn);
            if (HI_SUCCESS != s32Ret)
            {
                ERROR("HI_MPI_VENC_DestroyChn failed with " + HiErr(s32Ret));
                return s32Ret;
            }

            HisiResource::GetInstance()->ReleaseVenc(VeChn);
            VeChn = HI_INVALID_CHN;
            VencFd = -1;

            return HI_SUCCESS;
        }
        return HI_FAILURE;
    }


    HI_S32 Hi264BindEncode::GetMppChn(MPP_CHN_S& stMppChn)
    {
        if (VeChn!=HI_INVALID_CHN)
        {
            stMppChn.enModId = HI_ID_VENC;
            stMppChn.s32DevId = 0;
            stMppChn.s32ChnId = VeChn;
        }
    }
}

#endif
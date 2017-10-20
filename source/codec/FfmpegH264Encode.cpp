
#include "FfmpegUtils.hpp"
#include "FfmpegH264Encode.hpp"


namespace wdm
{

    FfmpegH264Encode* encode = new FfmpegH264Encode();

    FfmpegH264Encode::FfmpegH264Encode()
        :Encoder(CODEC_ID_H264, std::string("h264"))
    {
        FfmpegContext::GetInstance();
    }


    FfmpegH264Encode::~FfmpegH264Encode()
    {
    }


    bool FfmpegH264Encode::Config(CodecContext* context, Property& config)
    {
        AVCodecContext* codecCtx = nullptr;
        AVCodec* codec = nullptr;
//         codec = avcodec_find_encoder_by_name("libx264");
//         if (codec == NULL)
//         {
//             codec = avcodec_find_encoder(AV_CODEC_ID_H264);
//         }
        codec = avcodec_find_encoder(AV_CODEC_ID_H265);
        if (codec == NULL)
        {
            return nullptr;
        }

        codecCtx = avcodec_alloc_context3(codec);
        if (context==nullptr)
        {
            return nullptr;
        }
        codecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
        config.GetProperty("width", codecCtx->width);
        config.GetProperty("height", codecCtx->height);
        config.GetProperty("fps", codecCtx->gop_size);
        codecCtx->max_b_frames = 0;
        codecCtx->time_base = { 1, 1000000 };
        int bitrate = 0;
        config.GetProperty("bitrate", bitrate);
        codecCtx->bit_rate = bitrate * 1000;
        codecCtx->rc_max_rate = codecCtx->bit_rate;
        codecCtx->rc_min_rate = codecCtx->bit_rate;
        codecCtx->bit_rate_tolerance = codecCtx->bit_rate;
        codecCtx->rc_buffer_size = codecCtx->bit_rate;
        codecCtx->rc_initial_buffer_occupancy = codecCtx->rc_buffer_size * 3 / 4;
        codecCtx->rc_buffer_aggressivity = (float)1.0;
        codecCtx->rc_initial_cplx = 0.5;
        // 	av_opt_set(m_pVideoEncoder->priv_data, "preset", "superfast", 0);
        // 	av_opt_set(m_pVideoEncoder->priv_data, "tune", "zerolatency", 0);

        int ret = avcodec_open2(codecCtx, codec, NULL);
        if (ret < 0)
        {
            avcodec_free_context(&codecCtx);
            return false;
        }

        VideoAttribute attr;
        context->GetVideoAttribute(attr);
        SwsContext* converter = sws_getContext(attr.width, attr.height, MediaFormatToPixFormat(attr.format),
                                               codecCtx->width,codecCtx->height, codecCtx->pix_fmt,
                                                SWS_FAST_BILINEAR,NULL,NULL,NULL);
        if (converter==NULL)
        {
            avcodec_free_context(&codecCtx);
            return false;
        }

        this->SetPrivateContext(context, codecCtx);
        this->SetPrivateConverter(context, converter);

        return true;
    }


    bool FfmpegH264Encode::Encode(CodecContext* context, MediaFrame* frame, MediaPacket** ppacket)
    {
        AVCodecContext* codecCtx = nullptr;
        SwsContext* swsCtx = nullptr;
        this->GetPrivateContext(context, (void**)&codecCtx);
        this->GetPrivateConverter(context, (void**)&swsCtx);

        int got_pkt = 0;
        AVPacket pkt;
        av_init_packet(&pkt);
        pkt.data = NULL;    // packet data will be allocated by the encoder
        pkt.size = 0;

        frame->Reference();
        AVFrame* pic = MediaFormatToAVFrame(frame);

        if (swsCtx)
        {
            AVFrame* dst = av_frame_alloc();
            dst->format = codecCtx->pix_fmt;
            dst->width = codecCtx->width;
            dst->height = codecCtx->height;
            av_frame_get_buffer(dst, 32);

            int ret = sws_scale(swsCtx, pic->data, pic->linesize, 0, pic->height, dst->data, dst->linesize);
            if (ret > 0)
            {
            }
            dst->pts = pic->pts;

            pic = dst;
        }

        int ret = avcodec_encode_video2(codecCtx, &pkt, pic, &got_pkt);
        if (ret < 0)
        {

        }
        if (got_pkt)
        {
            MediaPacket* packet = new MediaPacket(MEDIA_TYPE_VIDEO, pkt.data, pkt.size);
            if (pkt.flags | AV_PKT_FLAG_KEY)
            {
                packet->keyframe = true;
            }
            packet->width = pic->width;
            packet->height = pic->height;
            packet->timestamp = pkt.pts;
            *ppacket = packet;
        }

        if (swsCtx)
        {
            av_frame_free(&pic);
        }
        frame->Release();

        return true;
    }


    void FfmpegH264Encode::FreePrivate(CodecContext* context)
    {
        AVCodecContext* codecCtx = nullptr;
        SwsContext* swsCtx = nullptr;
        this->GetPrivateContext(context, (void**)&codecCtx);
        this->GetPrivateConverter(context, (void**)&swsCtx);

        avcodec_free_context(&codecCtx);
        sws_freeContext(swsCtx);
    }

}
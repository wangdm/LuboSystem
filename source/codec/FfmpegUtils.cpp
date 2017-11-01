#include "FfmpegUtils.hpp"


namespace wdm
{


    FfmpegContext::FfmpegContext() {

        av_register_all();
        avcodec_register_all();
    }

    FfmpegContext* FfmpegContext::instance = nullptr;
    FfmpegContext* FfmpegContext::GetInstance()
    {
        if (instance==nullptr)
        {
            instance = new FfmpegContext();
        }

        return instance;
    }


    bool MediaFormatToPixFormat(MediaFormat format, AVPixelFormat& pix_fmt)
    {
        switch (format)
        {
        case MEDIA_FORMAT_NV12:
            pix_fmt = AV_PIX_FMT_NV12;
            return true;
        case MEDIA_FORMAT_I420:
            pix_fmt = AV_PIX_FMT_YUV410P;
            return true;
        case MEDIA_FORMAT_RGB24:
            pix_fmt = AV_PIX_FMT_RGB24;
            return true;
        case MEDIA_FORMAT_NONE:
            return false;
        }

        return false;
    }


    AVPixelFormat MediaFormatToPixFormat(MediaFormat format)
    {
        switch (format)
        {
        case MEDIA_FORMAT_NV12:
            return AV_PIX_FMT_NV12;
        case MEDIA_FORMAT_I420:
            return AV_PIX_FMT_YUV410P;
        case MEDIA_FORMAT_RGB24:
            return AV_PIX_FMT_RGB24;
        case MEDIA_FORMAT_NONE:
            return AV_PIX_FMT_NONE;
        }

        return AV_PIX_FMT_NONE;
    }


    AVFrame* MediaFormatToAVFrame(MediaFrame* frame)
    {
        AVFrame* pic = av_frame_alloc();
        pic->format = MediaFormatToPixFormat(frame->format);
        pic->width = frame->width;
        pic->height = frame->height;
        pic->pts = frame->timestamp;
        
        av_image_fill_arrays(pic->data, pic->linesize, frame->GetData(), (AVPixelFormat)pic->format, pic->width, pic->height, 32);


        return pic;
    }

}

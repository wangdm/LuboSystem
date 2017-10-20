#ifndef _FFMPEG_UTILS_H_
#define _FFMPEG_UTILS_H_

#include "../media/MediaType.hpp"
#include "../media/MediaFrame.hpp"

#ifdef __cplusplus
extern "C" {
#endif
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
#include "libavutil/opt.h"
#ifdef __cplusplus
}
#endif


namespace wdm
{

    class FfmpegContext
    {
    private:
        FfmpegContext();
    public:
        static FfmpegContext* GetInstance();
        ~FfmpegContext() {};

        static FfmpegContext* instance;

    private:

    };


    bool MediaFormatToPixFormat(MediaFormat format, AVPixelFormat& pix_fmt);
    AVPixelFormat MediaFormatToPixFormat(MediaFormat format);
    AVFrame* MediaFormatToAVFrame(MediaFrame* frame);

}

#endif
#ifndef _FFMPEG_H264_ENCODE_
#define _FFMPEG_H264_ENCODE_

#include "../media/Codec.hpp"

#ifdef __cplusplus
extern "C" {
#endif
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/opt.h"
#ifdef __cplusplus
}
#endif

namespace wdm
{

    class FfmpegH264Encode : public Encoder
    {
    public:
        FfmpegH264Encode();
        ~FfmpegH264Encode();

        virtual bool Config(CodecContext* context, Property& config) override;
        virtual bool Encode(CodecContext* context, MediaFrame* frame, MediaPacket** packet) override;
        virtual void FreePrivate(CodecContext* context) override;

    private:

    };

}


#endif

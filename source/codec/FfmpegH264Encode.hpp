#ifndef _FFMPEG_H264_ENCODE_
#define _FFMPEG_H264_ENCODE_

#include "../media/Codec.hpp"
#include "../media/CodecContext.hpp"

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

        virtual bool Config(SampleCodecContext* context, Property& config) override;
        virtual bool Encode(SampleCodecContext* context, MediaFrame* frame, MediaPacket** packet) override;
        virtual void FreePrivate(SampleCodecContext* context) override;

    private:

    };

}


#endif

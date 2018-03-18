#ifndef _CODECCONTEXT_H_
#define _CODECCONTEXT_H_

#include "../core/Property.hpp"

#include "../stream/StreamProducer.hpp"

#include "MediaFrame.hpp"
#include "MediaPacket.hpp"
#include "MediaSink.hpp"
#include "Codec.hpp"


namespace wdm
{
    class CodecContext : public MediaSink, public StreamProducer
    {
    public:
        CodecContext() {};
        virtual ~CodecContext() {};

    };


    class SampleCodecContext : public CodecContext
    {
    private:
        SampleCodecContext();
    public:
        SampleCodecContext(Codec* codec) : codec(codec) {};
        SampleCodecContext(CodecType type, CodecID id);
        SampleCodecContext(CodecType type, std::string& name);
        virtual ~SampleCodecContext();

        virtual bool Config(Property& config);
        virtual bool encode(MediaFrame* frame, MediaPacket** packet);
        virtual bool decode(MediaPacket* packet, MediaFrame** frame);

        virtual void SetVideoAttribute(VideoAttribute& attribute);
        virtual void GetVideoAttribute(VideoAttribute& attribute);
        virtual void SetAudioAttribute(AudioAttribute& attribute);
        virtual void GetAudioAttribute(AudioAttribute& attribute);

        virtual void* GetContext() const { return context; };

        virtual void OnFrame(MediaFrame* frame);

    private:
        Codec* codec;
        void* context;
        void* converter;

        VideoAttribute v_attr;
        AudioAttribute a_attr;

        friend class Codec;

    };

}

#endif // !_CODECCONTEXT_H_
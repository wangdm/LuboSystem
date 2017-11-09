#include "Codec.hpp"
#include "CodecContext.hpp"

#include "../base/Log.hpp"


namespace wdm
{


    //////////////////////////////////////////////////////////////////////////
    // CodecContext
    //////////////////////////////////////////////////////////////////////////

    SampleCodecContext::SampleCodecContext()
        : codec(nullptr)
        , context(nullptr)
        , converter(nullptr)
    {
    }


    SampleCodecContext::SampleCodecContext(CodecType type, CodecID id)
        : CodecContext()
    {
        if (type == CODEC_TYPE_ENCODER)
        {
            codec = CodecManager::GetInstance()->FindEncoder(id);
        } 
        else if (type == CODEC_TYPE_DECODER)
        {
            codec = CodecManager::GetInstance()->FindDecoder(id);
        }
    }


    SampleCodecContext::SampleCodecContext(CodecType type, std::string& name)
        :CodecContext()
    {
        if (type == CODEC_TYPE_ENCODER)
        {
            codec = CodecManager::GetInstance()->FindEncoder(name);
        }
        else if (type == CODEC_TYPE_DECODER)
        {
            codec = CodecManager::GetInstance()->FindDecoder(name);
        }
    
    }


    SampleCodecContext::~SampleCodecContext()
    {
        codec->FreePrivate(this);
    }


    bool SampleCodecContext::Config(Property& config)
    {
        if (codec!=nullptr)
        {
            codec->Config(this, config);
            if (context!=nullptr)
            {
                return true;
            }
        }
        return false;
    }


    bool SampleCodecContext::encode(MediaFrame* frame, MediaPacket** packet)
    {
        if (codec != nullptr && codec->GetCodecType() == CODEC_TYPE_ENCODER)
        {
            Encoder* encoder = dynamic_cast<Encoder*>(codec);
            if (encoder != nullptr)
            {
                return encoder->Encode(this, frame, packet);
            }
        }

        return false;
    }


    bool SampleCodecContext::decode(MediaPacket* packet, MediaFrame** frame)
    {
        if (codec != nullptr && codec->GetCodecType() == CODEC_TYPE_DECODER)
        {
            Decoder* decoder = dynamic_cast<Decoder*>(codec);
            if (decoder != nullptr)
            {
                return decoder->Decode(this, packet, frame);
            }
        }

        return false;
    }


    void SampleCodecContext::SetVideoAttribute(VideoAttribute& attribute)
    {
        v_attr = attribute;
    }


    void SampleCodecContext::GetVideoAttribute(VideoAttribute& attribute)
    {
        attribute = v_attr;
    }


    void SampleCodecContext::SetAudioAttribute(AudioAttribute& attribute)
    {
        a_attr = attribute;
    }


    void SampleCodecContext::GetAudioAttribute(AudioAttribute& attribute)
    {
        attribute = a_attr;
    }


    void SampleCodecContext::OnFrame(MediaFrame* frame)
    {
        MediaPacket* packet = nullptr;
        encode(frame, &packet);
        if (packet)
        {
            packet->Release();
        }
        DEBUG("Get Frame...");
    }
}
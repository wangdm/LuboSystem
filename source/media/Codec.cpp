#include "Codec.hpp"


namespace wdm
{

    Codec::Codec(CodecType type, CodecID id, const std::string& name)
        : type(type)
        , codecId(id)
        , name(name)
    {
        CodecManager::GetInstance()->RegisterCodec(this);
    }


    void Codec::SetPrivateContext(CodecContext* context, void* priv)
    {
        context->context = priv;
    }


    void Codec::GetPrivateContext(CodecContext* context, void** priv)
    {
        *priv = context->context;
    }


    void Codec::SetPrivateConverter(CodecContext* context, void* priv)
    {
        context->converter = priv;
    }


    void Codec::GetPrivateConverter(CodecContext* context, void** priv)
    {
        *priv = context->converter;
    }


    CodecManager::CodecManager()
    {
    }


    CodecManager::~CodecManager()
    {
    }


    //////////////////////////////////////////////////////////////////////////
    // CodecContext
    //////////////////////////////////////////////////////////////////////////

    CodecContext::CodecContext()
        : codec(nullptr)
        , context(nullptr)
        , converter(nullptr)
    {
    }


    CodecContext::CodecContext(CodecType type, CodecID id)
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


    CodecContext::CodecContext(CodecType type, std::string& name)
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


    CodecContext::~CodecContext()
    {
        codec->FreePrivate(this);
    }


    bool CodecContext::Config(Property& config)
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


    bool CodecContext::encode(MediaFrame* frame, MediaPacket** packet)
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


    bool CodecContext::decode(MediaPacket* packet, MediaFrame** frame)
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


    void CodecContext::SetVideoAttribute(VideoAttribute& attribute)
    {
        v_attr = attribute;
    }


    void CodecContext::GetVideoAttribute(VideoAttribute& attribute)
    {
        attribute = v_attr;
    }


    void CodecContext::SetAudioAttribute(AudioAttribute& attribute)
    {
        a_attr = attribute;
    }


    void CodecContext::GetAudioAttribute(AudioAttribute& attribute)
    {
        attribute = a_attr;
    }


    //////////////////////////////////////////////////////////////////////////
    // static method
    //////////////////////////////////////////////////////////////////////////

    CodecManager* CodecManager::instance = nullptr;
    CodecManager* CodecManager::GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new CodecManager();
        }
        return instance;
    }


    //////////////////////////////////////////////////////////////////////////
    // public method
    //////////////////////////////////////////////////////////////////////////

    bool CodecManager::RegisterCodec(Codec* codec)
    {
        if (codec->GetCodecType() == CODEC_TYPE_ENCODER)
        {
            return RegisterEncoder((Encoder*)codec);
        }
        else if (codec->GetCodecType() == CODEC_TYPE_DECODER)
        {
            return RegisterDecoder((Decoder*)codec);
        }

        return false;
    }



    Encoder* CodecManager::FindEncoder(CodecID id)
    {

        std::map<std::string, Encoder*>::const_iterator iter = encoders.begin();
        for (; iter != encoders.end(); iter++)
        {
            if ((iter->second)->GetCodecID() == id)
            {
                return iter->second;
            }
        }
        return nullptr;
    }


    Decoder* CodecManager::FindDecoder(CodecID id)
    {

        std::map<std::string, Decoder*>::const_iterator iter = decoders.begin();
        for (; iter != decoders.end(); iter++)
        {
            if ((iter->second)->GetCodecID() == id)
            {
                return iter->second;
            }
        }
        return nullptr;
    }


    Encoder* CodecManager::FindEncoder(std::string& name)
    {
        if (encoders.count(name)>0)
        {
            return encoders[name];
        }
        return nullptr;
    }


    Decoder* CodecManager::FindDecoder(std::string& name)
    {
        if (decoders.count(name)>0)
        {
            return decoders[name];
        }
        return nullptr;
    }


    //////////////////////////////////////////////////////////////////////////
    // private method
    //////////////////////////////////////////////////////////////////////////

    bool CodecManager::RegisterEncoder(Encoder* codec)
    {
        if (encoders.count(codec->GetCodecName())<=0)
        {
            encoders[codec->GetCodecName()] = codec;
            return true;
        }
        return false;
    }


    bool CodecManager::RegisterDecoder(Decoder* codec)
    {
        if (decoders.count(codec->GetCodecName())<=0)
        {
            decoders[codec->GetCodecName()] = codec;
            return true;
        }
        return false;
    }

}
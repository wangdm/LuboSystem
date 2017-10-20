#pragma once

#include "../base/Property.hpp"

#include "MediaFrame.hpp"
#include "MediaPacket.hpp"


namespace wdm
{

    enum CodecType
    {
        CODEC_TYPE_UNKNOWN = 0,
        CODEC_TYPE_ENCODER,
        CODEC_TYPE_DECODER,
    };

    enum CodecID
    {
        CODEC_ID_UNKNOWN = 0,
        CODEC_ID_H264,
        CODEC_ID_H265,
        CODEC_ID_VP8,
        CODEC_ID_VP9,

        CODEC_ID_AAC,
        CODEC_ID_OPUS
    };

    class CodecContext;

    class Codec
    {
    public:
        Codec() : type(CODEC_TYPE_UNKNOWN), codecId(CODEC_ID_UNKNOWN) {};
        Codec(CodecType type, CodecID id, std::string& name);
        virtual ~Codec() {};

        virtual bool Config(CodecContext* context, Property& config) = 0;
        virtual void FreePrivate(CodecContext* context) = 0;

        virtual CodecType GetCodecType() const { return type; };
        virtual CodecID GetCodecID() const { return codecId; };
        virtual std::string GetCodecName() const { return name; };

    protected:
        void SetPrivateContext(CodecContext* context, void* priv);
        void GetPrivateContext(CodecContext* context, void** priv);
        void SetPrivateConverter(CodecContext* context, void* priv);
        void GetPrivateConverter(CodecContext* context, void** priv);


    protected:
        const CodecType type;
        const CodecID   codecId;
        std::string     name;

    };


    class Encoder : public Codec
    {
    public:
        Encoder() : Codec(CODEC_TYPE_ENCODER, CODEC_ID_UNKNOWN, std::string("")) {};
        Encoder(CodecID id, std::string& name) : Codec(CODEC_TYPE_ENCODER, id, name) {};
        virtual ~Encoder() {};

        virtual bool Encode(CodecContext* context, MediaFrame* frame, MediaPacket** packet) = 0;

    private:

    };


    class Decoder : public Codec
    {
    public:
        Decoder() : Codec(CODEC_TYPE_DECODER, CODEC_ID_UNKNOWN, std::string("")) {};
        Decoder(CodecID id, std::string& name) : Codec(CODEC_TYPE_DECODER, id, name) {};
        virtual ~Decoder() {};

        virtual bool Decode(CodecContext* context, MediaPacket* packet, MediaFrame** frame) = 0;

    private:

    };


    class CodecContext
    {
    private:
        CodecContext();
    public:
        CodecContext(Codec* codec) : codec(codec) {};
        CodecContext(CodecType type, CodecID id);
        CodecContext(CodecType type, std::string& name);
        ~CodecContext();

        virtual bool Config(Property& config);
        virtual bool encode(MediaFrame* frame, MediaPacket** packet);
        virtual bool decode(MediaPacket* packet, MediaFrame** frame);

        virtual void SetVideoAttribute(VideoAttribute& attribute);
        virtual void GetVideoAttribute(VideoAttribute& attribute);
        virtual void SetAudioAttribute(AudioAttribute& attribute);
        virtual void GetAudioAttribute(AudioAttribute& attribute);



        virtual void* GetContext() const { return context; };

    private:
        Codec* codec;
        void* context;
        void* converter;

        VideoAttribute v_attr;
        AudioAttribute a_attr;

        friend class Codec;

    };


    class CodecManager
    {
    private:
        CodecManager();
    public:
        ~CodecManager();

        static CodecManager* GetInstance();

        bool RegisterCodec(Codec* codec);

        Encoder* FindEncoder(CodecID id);
        Decoder* FindDecoder(CodecID id);
        Encoder* FindEncoder(std::string& name);
        Decoder* FindDecoder(std::string& name);


    private:
        bool RegisterEncoder(Encoder* codec);
        bool RegisterDecoder(Decoder* codec);


    private:
        static CodecManager* instance;

        std::map<std::string, Encoder*> encoders;
        std::map<std::string, Decoder*> decoders;

    };

}
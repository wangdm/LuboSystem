#pragma once

#include <algorithm>
#include <vector>

#include "../core/event/Event.hpp"
#include "../core/Config.hpp"
#include "../core/Property.hpp"

#include "../media/MediaType.hpp"
#include "../media/MediaSink.hpp"
#include "../media/Codec.hpp"
#include "../media/CodecContext.hpp"

#include "../stream/StreamConsumer.hpp"
#include "../stream/StreamProducer.hpp"


namespace wdm {


	struct StreamInfo
	{

	};

    class Channel;
    class StreamConsumer;


	class MediaStream : public EventHandler
	{
    public:
        MediaStream(Channel* channel);
		MediaStream(Channel* channel, Config* config);
        virtual ~MediaStream();

        virtual MediaType GetStreamType() { return type; };
        virtual bool GetStreamAttribute(VideoStreamAttribute& attr);
        virtual bool GetStreamAttribute(AudioStreamAttribute& attr);

        virtual void AddConsumer(StreamConsumer* consumer);
        virtual void DelConsumer(StreamConsumer* consumer);

        virtual void SetProducer(StreamProducer* producer);
        virtual StreamProducer*  GetProducer();

        virtual bool Init(Config* config);
        virtual bool Uninit();
        virtual bool Start();
        virtual bool Stop();

        virtual void handleEvent(Event* e) override;

    private:
        MediaPacket* CreatePacket();
        MediaPacket* ReadPacket();

    private:
        Channel* channel;

        StreamProducer* producer;
        std::vector<StreamConsumer*> consumers;

        Mutex consumerMtx;

        Property prop;

        MediaType type;

        //video property
        uint32_t width;
        uint32_t height;

        //audio property
        uint32_t samplesize;
        uint32_t samplerate;
        uint32_t samplebit;
        uint32_t channels;

	};

}
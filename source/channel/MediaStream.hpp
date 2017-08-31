#pragma once

#include <vector>

#include "../base//Event.hpp"

#include "../stream/StreamConsumer.hpp"

#include "MediaType.hpp"


namespace wdm {


	struct StreamInfo
	{

	};

    class StreamConsumer;


	class MediaStream : public EventHandler
	{
	public:
		MediaStream();
		virtual ~MediaStream();

        virtual void AddConsumer(StreamConsumer* consumer);
        virtual void DelConsumer(StreamConsumer* consumer);

        virtual bool Init();
        virtual bool UnInit();
        virtual bool Start();
        virtual bool Stop();

    protected:
        virtual void handleEvent(Event* e, EventFlag f) override;

    private:
        MediaPacket* CreatePacket();
        MediaPacket* ReadPacket();

	private:
        std::vector<StreamConsumer*> consumers;
        Event* event;

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
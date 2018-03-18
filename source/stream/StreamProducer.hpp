#pragma once


#include "../core/Thread.hpp"
#include "../core/event/Event.hpp"

#include "../media/MediaPacket.hpp"

namespace wdm {

    class MediaStream;

	class StreamProducer : public EventSource
	{
	public:
        StreamProducer();
        StreamProducer(MediaStream* stream);
		virtual ~StreamProducer();

        virtual void SetMediaStream(MediaStream* stream);

        virtual MediaPacket* GetMedaiPacket() = 0;

        virtual bool Start() = 0;
        virtual bool Stop() = 0;

    protected:
        MediaStream* stream;

	};

}
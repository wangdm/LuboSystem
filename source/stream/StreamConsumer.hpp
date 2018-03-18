#pragma once


#include "../core/Thread.hpp"

#include "../media/MediaPacket.hpp"
#include "../media/PacketQueue.hpp"

namespace wdm {

    class MediaStream;

	class StreamConsumer : public Thread
	{
	public:
        StreamConsumer();
        StreamConsumer(MediaStream* stream);
		virtual ~StreamConsumer();

        virtual void SetMediaStream(MediaStream* stream);

        virtual void OnStream(MediaPacket* packet);

	protected:
        PacketQueue queue;

    private:
        MediaStream* stream;

	};

}
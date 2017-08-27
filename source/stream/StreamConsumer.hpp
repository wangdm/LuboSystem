#pragma once


#include "../base/Thread.hpp"
#include "../channel/MediaPacket.hpp"
#include "../channel/MediaStream.hpp"

#include "PacketQueue.hpp"

namespace wdm {

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
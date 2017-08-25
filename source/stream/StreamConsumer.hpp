#pragma once


#include "../base/Thread.hpp"
#include "../channel/MediaPacket.hpp"

#include "PacketQueue.hpp"

namespace wdm {

	class StreamConsumer : public Thread
	{
	public:
		StreamConsumer();
		virtual ~StreamConsumer();

        virtual void OnStream(MediaPacket* packet);

	protected:
        PacketQueue queue;

	};

}
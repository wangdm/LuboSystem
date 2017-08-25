#include "StreamConsumer.hpp"


namespace wdm {

	StreamConsumer::StreamConsumer()
	{
	}

	StreamConsumer::~StreamConsumer()
	{
	}


    void StreamConsumer::OnStream(MediaPacket* packet)
    {
        queue.Push(packet);
    }

}
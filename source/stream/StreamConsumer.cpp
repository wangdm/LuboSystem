#include "StreamConsumer.hpp"


namespace wdm {

    StreamConsumer::StreamConsumer()
        :stream(nullptr)
	{
	}


    StreamConsumer::StreamConsumer(MediaStream* stream)
        :stream(stream)
    {
        stream->AddConsumer(this);
    }

	StreamConsumer::~StreamConsumer()
	{
        if (stream!=nullptr)
        {
            stream->DelConsumer(this);
        }
	}


    void StreamConsumer::SetMediaStream(MediaStream* stream)
    {
        this->stream = stream;
        this->stream->AddConsumer(this);
    }


    void StreamConsumer::OnStream(MediaPacket* packet)
    {
        queue.Push(packet);
    }

}
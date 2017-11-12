#include "StreamProducer.hpp"

#include "../channel/MediaStream.hpp"


namespace wdm {

    StreamProducer::StreamProducer()
        :stream(nullptr)
	{
	}


    StreamProducer::StreamProducer(MediaStream* stream)
        :stream(stream)
    {
        stream->SetProducer(this);
    }


    StreamProducer::~StreamProducer()
	{
	}


    void StreamProducer::SetMediaStream(MediaStream* stream)
    {
        this->stream = stream;
    }

}
#pragma once


#include "../base/Thread.hpp"

#include "../media/MediaPacket.hpp"

namespace wdm {

    class MediaStream;

	class StreamProducer
	{
	public:
        StreamProducer();
        StreamProducer(MediaStream* stream);
		virtual ~StreamProducer();

        virtual void SetMediaStream(MediaStream* stream);

        virtual bool Start() = 0;
        virtual bool Stop() = 0;

    protected:
        MediaStream* stream;

	};

}
#pragma once

#include <vector>

#include "MediaType.hpp"
#include "../stream/StreamConsumer.hpp"


namespace wdm {


	struct StreamInfo
	{

	};


	class MediaStream
	{
	public:
		MediaStream();
		virtual ~MediaStream();

        virtual void AddConsumer(StreamConsumer* consumer);
        virtual void DelConsumer(StreamConsumer* consumer);

    protected:
        virtual void OnStream(MediaPacket* stream);

	private:
		MediaType type;
        std::vector<StreamConsumer*> consumers;

	};

}
#include "MediaStream.hpp"
#include "MediaPacket.hpp"

namespace wdm {

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////

	MediaStream::MediaStream()
	{
	}


	MediaStream::~MediaStream()
	{
    }


    void MediaStream::AddConsumer(StreamConsumer* consumer)
    {
        consumers.push_back(consumer);
    }


    void MediaStream::DelConsumer(StreamConsumer* consumer)
    {
        std::vector<StreamConsumer*>::iterator iter = consumers.begin();
        for (; iter != consumers.end(); iter++)
        {
            if (*iter == consumer)
            {
                consumers.erase(iter);
            }
        }
    }


    void MediaStream::OnStream(MediaPacket* stream)
    {
        for_each(consumers.begin(), consumers.end(), [&](StreamConsumer* consumer)
        {
            consumer->OnStream(stream); 
        });
    }

}
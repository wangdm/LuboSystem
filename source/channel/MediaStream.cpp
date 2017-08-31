#include "MediaStream.hpp"
#include "../media/MediaPacket.hpp"

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


    bool MediaStream::Init()
    {
        return true;
    }


    bool MediaStream::UnInit()
    {
        return true;
    }


    bool MediaStream::Start()
    {
        return true;
    }


    bool MediaStream::Stop()
    {
        return true;
    }


    void MediaStream::handleEvent(Event* e, EventFlag f)
    {
        MediaPacket* packet = ReadPacket();
        for_each(consumers.begin(), consumers.end(), [&](StreamConsumer* consumer)
        {
            consumer->OnStream(packet);
        });
    }


    MediaPacket* MediaStream::CreatePacket()
    {
        MediaPacket* packet = new MediaPacket(type);
        if (type == MEDIA_TYPE_VIDEO)
        {
            packet->width = width;
            packet->height = height;
        }
        else if (type == MEDIA_TYPE_AUDIO)
        {
            packet->samplesize = samplesize;
            packet->samplerate = samplerate;
            packet->samplebit = samplebit;
            packet->channels = channels;
        }
        return packet;
    }


    MediaPacket* MediaStream::ReadPacket()
    {
        MediaPacket* packet = CreatePacket();
        return packet;
    }

}
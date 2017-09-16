#include "MediaStream.hpp"
#include "../media/MediaPacket.hpp"

namespace wdm {

	//////////////////////////////////////////////////////////////////////////
	//
    //////////////////////////////////////////////////////////////////////////

    MediaStream::MediaStream()
    {
    }


	MediaStream::MediaStream(Config* config)
	{
        Init(config);
	}


	MediaStream::~MediaStream()
	{
    }


    bool MediaStream::GetStreamAttribute(VideoStreamAttribute& attr)
    {
        if (type==MEDIA_TYPE_VIDEO)
        {
            attr.width = width;
            attr.height = height;
            return true;
        }
        return false;
    }


    bool MediaStream::GetStreamAttribute(AudioStreamAttribute& attr)
    {
        if (type == MEDIA_TYPE_AUDIO)
        {
            attr.channel = channels;
            attr.samplerate = samplerate;
            attr.bitwide = samplebit;
            return true;
        }
        return false;
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


    bool MediaStream::Init(Config* config)
    {
        config->Print();
        return true;
    }


    bool MediaStream::Uninit()
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


    void MediaStream::OnFrame(MediaFrame* frame)
    {

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
#include "../base/Log.hpp"
#include "../media/MediaPacket.hpp"
#include "../channel/Channel.hpp"

#include "MediaStream.hpp"


namespace wdm {

	//////////////////////////////////////////////////////////////////////////
	//
    //////////////////////////////////////////////////////////////////////////

    MediaStream::MediaStream(Channel* channel)
        : channel(channel)
        , producer(nullptr)
    {
    }


    MediaStream::MediaStream(Channel* channel, Config* config)
        : channel(channel)
        , producer(nullptr)
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


    void MediaStream::SetProducer(StreamProducer* producer)
    {
        if (producer!=nullptr)
        {
            this->producer = producer;
        }
    }


    StreamProducer*  MediaStream::GetProducer()
    {
        return producer;
    }


    bool MediaStream::Init(Config* config)
    {
        config->Print();

        prop["name"] = (*config)["name"];
        std::string stream_type = (*config)["type"];
        if (stream_type == "video")
        {
            type = MEDIA_TYPE_VIDEO;
            prop["width"] = (*config)["width"];
            prop["height"] = (*config)["height"];
            prop["fps"] = (*config)["fps"];
            prop["codec"] = (*config)["codec"];
            prop["profile"] = (*config)["profile"];
            prop["bitrate"] = (*config)["bitrate"];
            prop["gop"] = (*config)["gop"];
        }
        else if (stream_type == "audio")
        {
            type = MEDIA_TYPE_AUDIO;
            prop["channel"] = (*config)["channel"];
            prop["samplerate"] = (*config)["samplerate"];
            prop["bitwide"] = (*config)["bitwide"];
            prop["codec"] = (*config)["codec"];
            prop["profile"] = (*config)["profile"];
            prop["bitrate"] = (*config)["bitrate"];
        }
        else
        {
            ERROR("Unkonwn media type " + stream_type);
            return false;
        }

        return true;
    }


    bool MediaStream::Uninit()
    {
        return true;
    }


    bool MediaStream::Start()
    {
        DEBUG("Start Media Stream...");
        if (producer != nullptr)
        {
            producer->Start();
            return false;
        }

        return true;
    }


    bool MediaStream::Stop()
    {
        DEBUG("Stop Media Stream...");
        if (producer != nullptr)
        {
            producer->Stop();
            return false;
        }
        return true;
    }


    void MediaStream::handleEvent(Event* e, EventFlag f)
    {
        MediaPacket* packet = ReadPacket();
        std::for_each(consumers.begin(), consumers.end(), [&](StreamConsumer* consumer)
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
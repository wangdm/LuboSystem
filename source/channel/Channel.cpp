#include "../base/Log.hpp"
#include "Channel.hpp"


namespace wdm {
	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////

    Channel::Channel()
        : channelType(CHANNEL_TYPE_UNKNOWN)
        , config(nullptr)
        , channelStatus(UNINITIALIZED)
	{
    }


    Channel::Channel(ChannelType type)
        : channelType(type)
        , config(nullptr)
        , channelStatus(UNINITIALIZED)
    {
    }


	Channel::~Channel()
    {
        if (config != nullptr)
        {
            delete config;
        }
	}


	std::string Channel::GetChannelName()
	{
		return channelName;
	}


	ChannelType Channel::GetChannelType()
	{
		return channelType;
	}


	ChannelStatus Channel::GetChannelStatus()
	{
		return channelStatus;
	}


	int Channel::GetStreamCnt()
	{
		return (int)streams.size();
	}


	MediaStream* Channel::GetStream(const std::string& stream)
	{
		if (streams.find(stream)!=streams.end())
		{
			return streams[stream];
		}
		return nullptr;
	}


	MediaStream* Channel::GetMajorStream()
	{
		return GetStream(MAJOR_STREAM);
	}


	MediaStream* Channel::GetMinorStream()
	{
		return GetStream(MINOR_STREAM);
	}


	MediaStream* Channel::GetAudioStream()
	{
		return GetStream(AUDIO_STREAM);
	}


    void Channel::AddStreamConsumer(StreamConsumer* consumer, const std::string& stream)
    {
        if (consumer==nullptr)
        {
            return;
        }

        MediaStream* pstream = GetStream(stream);
        if (pstream!=nullptr)
        {
            consumer->SetMediaStream(pstream);
        }
    }


    void Channel::DelStreamConsumer(StreamConsumer* consumer, const std::string& stream)
    {
        if (consumer == nullptr)
        {
            return;
        }

        MediaStream* pstream = GetStream(stream);
        if (pstream != nullptr)
        {
            pstream->DelConsumer(consumer);
        }
    }


	void Channel::SetColorParam(ColorParam &color)
	{

	}


	void Channel::GetColorParam(ColorParam &color)
	{

	}


	void Channel::SetFilterParam(FilterParam &param)
	{

	}


	void Channel::GetFilterParam(FilterParam &param)
	{
	
    }


    //////////////////////////////////////////////////////////////////////////
    /// MediaSink method
    //////////////////////////////////////////////////////////////////////////

    void Channel::OnFrame(MediaFrame* frame)
    {
        DEBUG("Channel Get Frame...");
        //frame->Reference();
        SendFrame(frame);
    }


	//////////////////////////////////////////////////////////////////////////
	/// protect method
	//////////////////////////////////////////////////////////////////////////

    void Channel::handleEvent(Event* e, EventFlag f)
    {
    }


	void Channel::OnSourceEvent(MediaType& type, SourceEvent& event, void* param)
	{
	}

}
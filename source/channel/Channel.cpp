#include "Channel.hpp"


namespace wdm {
	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////

	Channel::Channel()
	{
	}


	Channel::~Channel()
	{
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
		return streams.size();
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
	/// protect method
	//////////////////////////////////////////////////////////////////////////

    void Channel::handleEvent(Event* e, EventFlag f)
    {
    }


	void Channel::OnSourceEvent(MediaType& type, SourceEvent& event, void* param)
	{
	}


	void Channel::OnFrame(MediaFrame frame)
	{

	}
}
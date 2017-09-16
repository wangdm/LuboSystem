#include "ChannelManager.hpp"

#include "../platform/Platform.hpp"
#include "LocalChannel.hpp"


namespace wdm
{

	ChannelManager::ChannelManager()
    {
        for (Capture* capture : Platform::videoCaptures)
        {
            Channel* channel = new LocalChannel(capture, nullptr);
            channel->Init(nullptr);
            channels.push_back(channel);
        }
	}


	ChannelManager::~ChannelManager()
    {
        std::vector<Channel*>::iterator iter;
        for (iter = channels.begin(); iter != channels.end();)
        {
            Channel* channel = *iter;
            iter = channels.erase(iter);
            delete channel;
        }
	}

	//////////////////////////////////////////////////////////////////////////
	// static method
	//////////////////////////////////////////////////////////////////////////

	bool ChannelManager::Initialize(const std::string& cfilename)
	{
        instance = new ChannelManager();
        return true;
	}


	void ChannelManager::Uninitialize()
    {
        delete instance;
	}


	ChannelManager* ChannelManager::instance = nullptr;
	ChannelManager* ChannelManager::GetInstance()
	{
		return instance;
	}


	//////////////////////////////////////////////////////////////////////////
	// public method
	//////////////////////////////////////////////////////////////////////////

	Channel* ChannelManager::GetChannel(uint32_t idx)
	{
		if (idx < channels.size())
		{
			return channels[idx];
		}
		return nullptr;
	}


	void ChannelManager::StartLocalChannel()
	{
		std::vector<Channel*>::const_iterator iter = channels.begin();
		for (; iter != channels.end(); iter++)
		{
			if ((*iter)->GetChannelType() == CHANNEL_TYPE_LOCAL)
			{
				(*iter)->Start();
			}
		}
	}

	void ChannelManager::StopLocalChannel()
	{
		std::vector<Channel*>::const_iterator iter = channels.begin();
		for (; iter != channels.end(); iter++)
		{
			if ((*iter)->GetChannelType() == CHANNEL_TYPE_LOCAL)
			{
				(*iter)->Stop();
			}
		}
	}

	void ChannelManager::StartChannel(uint32_t idx)
	{
		if (idx < channels.size())
		{
			channels[idx]->Start();
		}
	}

	
	void ChannelManager::StopChannel(uint32_t idx)
	{
		if (idx < channels.size())
		{
			channels[idx]->Stop();
		}
	}


	Channel* ChannelManager::CreateFileChannel()
	{
		return nullptr;
	}


	void ChannelManager::StartSourceMoniter()
	{

	}


	void ChannelManager::StopSourceMoniter()
	{
	
	}


    void ChannelManager::AddEvent(Event* e)
    {
        listener->AddEvent(e);
    }


    void ChannelManager::DelEvent(Event* e)
    {
        listener->DelEvent(e);
    }


    void ChannelManager::StartListenEvent()
    {
        listener->Start();
    }


    void ChannelManager::StopListenEvent()
    {
        listener->Stop();
    }

}
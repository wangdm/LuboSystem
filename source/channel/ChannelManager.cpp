#include "ChannelManager.hpp"


namespace wdm
{

	ChannelManager::ChannelManager()
	{
	}


	ChannelManager::~ChannelManager()
	{
	}

	//////////////////////////////////////////////////////////////////////////
	// static method
	//////////////////////////////////////////////////////////////////////////

	bool ChannelManager::Initialize(std::string& cfilename)
	{
		return false;
	}


	void ChannelManager::Uninitialize()
	{

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

}
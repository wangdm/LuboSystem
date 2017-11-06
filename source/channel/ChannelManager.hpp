#pragma once

#include <string>
#include <vector>

#include "../base/Log.hpp"
#include "../base/Config.hpp"
#include "../base/Event.hpp"

#include "Channel.hpp"

namespace wdm
{

	class ChannelManager
	{
	private:
		ChannelManager();
	public:
		~ChannelManager();

		static bool Initialize(const std::string& cfilename);
		static void Uninitialize();
		static ChannelManager* GetInstance();

		Channel* GetChannel(uint32_t idx);

		void StartLocalChannel();
		void StopLocalChannel();

		void StartChannel(uint32_t idx);
		void StopChannel(uint32_t idx);

		Channel* CreateFileChannel();

		void StartSourceMoniter();
		void StopSourceMoniter();

        void AddEvent(Event* e);
        void DelEvent(Event* e);
        void StartListenEvent();
        void StopListenEvent();

	private:
		static ChannelManager* instance;

		std::vector<Channel*> channels;
        EventListener* listener;
		Config* config;

	};

}
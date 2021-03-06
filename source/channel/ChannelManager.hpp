#pragma once

#include <string>
#include <vector>

#include "../core/Log.hpp"
#include "../core/Config.hpp"
#include "../core/event/Event.hpp"

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

        void AddEvent(EventSource* es);
        void DelEvent(EventSource* es);
        void StartListenEvent();
        void StopListenEvent();

	private:
		static ChannelManager* instance;

		std::vector<Channel*> channels;
        EventListener* listener;
		Config* config;

	};

}
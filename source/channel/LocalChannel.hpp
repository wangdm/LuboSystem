#pragma once

#include "Channel.hpp"
#include "../media/MediaSource.hpp"


namespace wdm 
{

	class LocalChannel : public Channel {

	public:
		LocalChannel();
        LocalChannel(std::string& config);
		virtual ~LocalChannel();

        virtual bool Init(std::string& config) override;
        virtual bool UnInit() override;


        virtual bool Start() override;
        virtual bool Stop() override;
	};

}
#pragma once

#include "Channel.hpp"
#include "MediaSource.hpp"


namespace wdm 
{

	class LocalChannel : public Channel {

	public:
		LocalChannel();
		virtual ~LocalChannel();

        virtual bool Start() override;
        virtual bool Stop(bool block = true) override;

	private:
		MediaSource* videoSource;
		MediaSource* audioSource;
	};

}
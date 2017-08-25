#pragma once

#include "Channel.hpp"
#include "MediaSource.hpp"


namespace wdm 
{

	class LocalChannel : public Channel {

	public:
		LocalChannel();
		virtual ~LocalChannel();

        virtual bool Init() override;
        virtual bool UnInit() override;


        virtual bool Start() override;
        virtual bool Stop(bool block = true) override;

        virtual void Run() override;

	private:
		MediaSource* videoSource;
		MediaSource* audioSource;
	};

}
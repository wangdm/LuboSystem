#pragma once

#include "Channel.hpp"
#include "../core/Log.hpp"
#include "../media/MediaSource.hpp"


namespace wdm 
{
	class LocalChannel : public Channel {

	public:
        LocalChannel(MediaSource* videoSource, MediaSource* audioSource);
		virtual ~LocalChannel();

        virtual bool Init(Config* config) override;
        virtual bool Uninit() override;

        virtual bool GetVideoAttribute(VideoAttribute& attr) const override;
        virtual bool GetAudioAttribute(AudioAttribute& attr) const override;


        virtual bool Start() override;
        virtual bool Stop() override;

    private:
        Config* GetDefaultConfig();

    private:
        MediaSource* _videoSource;
        MediaSource* _audioSource;
	};

}
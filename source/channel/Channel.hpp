#pragma once

#include <string>
#include <vector>

#include "../base/Config.hpp"
#include "../base/Thread.hpp"

#include "../media/MediaType.hpp"
#include "../media/MediaFrame.hpp"
#include "../media/MediaPacket.hpp"
#include "../media/MediaSource.hpp"

#include "MediaStream.hpp"

namespace wdm {

	struct ColorParam
	{
	};

	struct FilterParam
	{
	};

	enum ChannelType
    {
        CHANNEL_TYPE_UNKNOWN = 0,
		CHANNEL_TYPE_LOCAL,
		CHANNEL_TYPE_FILE,
		CHANNEL_TYPE_REMOTE,
		CHANNEL_TYPE_COM
	};

	enum ChannelStatus
	{
		UNINITIALIZED = 0,
		STOP,
		START
	};

	const std::string MAJOR_STREAM = "major";
	const std::string MINOR_STREAM = "minor";
	const std::string AUDIO_STREAM = "audio";

	class Channel : public EventHandler, public MediaSource, public MediaSink
	{
	public:
        Channel();
        Channel(ChannelType type);
		virtual ~Channel();

		virtual std::string GetChannelName();
		virtual ChannelType GetChannelType();
		virtual ChannelStatus GetChannelStatus();

		virtual int GetStreamCnt();
		virtual MediaStream* GetStream(const std::string& stream);
		virtual MediaStream* GetMajorStream();
		virtual MediaStream* GetMinorStream();
		virtual MediaStream* GetAudioStream();

        virtual void AddStreamConsumer(StreamConsumer* consumer, const std::string& stream);
        virtual void DelStreamConsumer(StreamConsumer* consumer, const std::string& stream);

		virtual void SetColorParam(ColorParam &param);
		virtual void GetColorParam(ColorParam &param);

		virtual void SetFilterParam(FilterParam &param);
		virtual void GetFilterParam(FilterParam &param);

		virtual bool Init(Config* config) = 0;
		virtual bool Uninit() = 0;
        virtual bool Start() = 0;
        virtual bool Stop() = 0;

        virtual void OnFrame(MediaFrame* frame);
        
    protected:
        virtual void handleEvent(Event* e, EventFlag f) override;
		virtual void OnSourceEvent(MediaType& type, SourceEvent& event, void* param);

		std::map<std::string, MediaStream*> streams;
		Config* config;
		std::string channelName;
		ChannelStatus channelStatus;

    private:
        const ChannelType channelType;

		ColorParam colorInfo;
        FilterParam filterParam;

	};

}
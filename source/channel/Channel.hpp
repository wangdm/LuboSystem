#pragma once

#include <string>
#include <vector>

#include "../base/Config.hpp"

#include "MediaType.hpp"
#include "MediaStream.hpp"
#include "MediaFrame.hpp"
#include "MediaPacket.hpp"


namespace wdm {

	struct ColorParam
	{
	};

	struct FilterParam
	{
	};

	enum ChannelType
	{
		CHANNEL_TYPE_LOCAL = 0,
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

	class Channel
	{
	public:
		Channel();
		virtual ~Channel();

		virtual std::string GetChannelName();
		virtual ChannelType GetChannelType();
		virtual ChannelStatus GetChannelStatus();

		virtual int GetStreamCnt();
		virtual MediaStream* GetStream(const std::string& stream);
		virtual MediaStream* GetMajorStream();
		virtual MediaStream* GetMinorStream();
		virtual MediaStream* GetAudioStream();

		virtual void SetColorParam(ColorParam &param);
		virtual void GetColorParam(ColorParam &param);

		virtual void SetFilterParam(FilterParam &param);
		virtual void GetFilterParam(FilterParam &param);

		virtual bool Init() = 0;
		virtual bool UnInit() = 0;

		virtual bool Start() = 0;
		virtual bool Stop() = 0;

	protected:
		virtual void OnSourceEvent(MediaType& type, SourceEvent& event, void* param);
		virtual void OnStream(MediaPacket stream);
		virtual void OnFrame(MediaFrame frame);

	private:
		std::map<std::string, MediaStream*> streams;
		Config* config;

		std::string channelName;
		ChannelType channelType;
		ChannelStatus channelStatus;

		ColorParam colorInfo;
		FilterParam filterParam;

	};

}
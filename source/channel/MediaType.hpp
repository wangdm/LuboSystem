#pragma once

#include <stdint.h>

#include <atomic>


namespace wdm {

	enum MediaType
	{
		MEDIA_TYPE_VIDEO = 0,
		MEDIA_TYPE_AUDIO,
		MEDIA_TYPE_DATA
	};


	enum SourceEvent
	{
		SOURCE_EVENT_SIGNAL = 0,
		SOURCE_WVENT_CHANGE,
		SOURCE_EVENT_LOST
	};


	typedef struct VideoStreamInfo
	{
	}VideoStreamInfo;


	typedef struct AudioStreamInfo 
	{
	}AudioStreamInfo;


	class MediaObject
	{
	public:
		MediaObject();
		virtual ~MediaObject();

		virtual void Reference();
		virtual void Release();
		virtual uint32_t RefCount();

	private:
		std::atomic<uint32_t> count;

	};

}
#pragma once

#include <stdint.h>

#include <atomic>


namespace wdm {

	enum MediaType
	{
        MEDIA_TYPE_NONE = 0,
		MEDIA_TYPE_VIDEO,
		MEDIA_TYPE_AUDIO,
		MEDIA_TYPE_DATA
	};


    enum MediaFormat
    {
        MEDIA_FORMAT_NONE = 0,

        //video
        MEDIA_FORMAT_NV12,
        MEDIA_FORMAT_I420,
        MEDIA_FORMAT_RGB24


        //audio
    };


	enum SourceEvent
	{
		SOURCE_EVENT_SIGNAL = 0,
		SOURCE_WVENT_CHANGE,
		SOURCE_EVENT_LOST
	};


    struct VideoAttribute 
    {
        MediaFormat format;
        int stride;
        int width;
        int height;
        int fps;
    };


    struct AudioAttribute
    {
        MediaFormat format;
        int channel;
        int samplerate;
        int bitwide;
    };


	struct VideoStreamAttribute
	{
        VideoStreamAttribute(VideoAttribute attr) {
            width = attr.width;
            height = attr.height;
            fps = attr.fps;
        }

        int width;
        int height;
        int fps;
	};


	struct AudioStreamAttribute
    {
        AudioStreamAttribute(AudioAttribute attr) {
            channel = attr.channel;
            samplerate = attr.samplerate;
            bitwide = attr.bitwide;
        }

        int channel;
        int samplerate;
        int bitwide;
	};


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
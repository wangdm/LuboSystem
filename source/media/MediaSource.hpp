#pragma once

#include <vector>

#include "../core/Mutex.hpp"

#include "MediaFrame.hpp"
#include "MediaSink.hpp"


namespace wdm
{

	class MediaSource
	{
	public:
		MediaSource();
        virtual ~MediaSource();

        virtual bool IsExistVideo() const;
        virtual bool IsExistAudio() const;

        virtual bool GetVideoAttribute(VideoAttribute& attr) const;
        virtual bool GetAudioAttribute(AudioAttribute& attr) const;

        virtual void AddMediaSink(MediaSink* sink);
        virtual void DelMediaSink(MediaSink* sink);


        virtual bool Start() = 0;
        virtual bool Stop() = 0;

    protected:
        virtual void SendFrame(MediaFrame* frame);

    protected:
        std::vector<MediaSink*> sinks;
        Mutex sinkMtx;

	};

}
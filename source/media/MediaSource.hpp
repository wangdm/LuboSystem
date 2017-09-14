#pragma once

#include <vector>

#include "MediaFrame.hpp"
#include "MediaSink.hpp"


namespace wdm
{

	class MediaSource
	{
	public:
		MediaSource();
		virtual ~MediaSource();

        virtual void AddMediaSink(MediaSink* sink);
        virtual void DelMediaSink(MediaSink* sink);


        virtual bool Start() = 0;
        virtual bool Stop() = 0;

    protected:
        virtual void SendFrame(MediaFrame* frame);

	private:
        std::vector<MediaSink*> sinks;

	};

}
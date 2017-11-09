#pragma once

#include "MediaFrame.hpp"


namespace wdm
{

    enum SinkMethod
    {
        SEND = 0,
        BIND,
    };

	class MediaSink
	{
	public:

        MediaSink();
		virtual ~MediaSink();

        virtual void OnFrame(MediaFrame* frame) = 0;
        virtual SinkMethod GetSinkMethod();
        virtual bool IsSupportscale();
        virtual bool ISSupportCSC();

	private:

	};

}
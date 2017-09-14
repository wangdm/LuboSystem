#pragma once

#include "MediaFrame.hpp"


namespace wdm
{

	class MediaSink
	{
	public:
        MediaSink();
		virtual ~MediaSink();

        virtual void OnFrame(MediaFrame* frame) = 0;

	private:

	};

}
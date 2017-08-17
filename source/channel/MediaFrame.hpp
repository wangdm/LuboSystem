#pragma once

#include "MediaType.hpp"


namespace wdm {


	class MediaFrame : public MediaObject
	{
	public:
		MediaFrame();
		virtual ~MediaFrame();

		MediaType GetFrameType();

	private:
		MediaType type;

	};


	class VideoFrame : public MediaFrame
	{
	public:
		VideoFrame();
		~VideoFrame();

	private:

	};

}
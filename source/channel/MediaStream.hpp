#pragma once

#include "MediaType.hpp"


namespace wdm {


	struct StreamInfo
	{

	};


	class MediaStream
	{
	public:
		MediaStream();
		virtual ~MediaStream();

	private:
		MediaType type;

	};

}
#pragma once

#include "Channel.hpp"
#include "MediaSource.hpp"


namespace wdm 
{

	class LocalChannel : public Channel {

	public:
		LocalChannel();
		virtual ~LocalChannel();

	private:
		MediaSource* videoSource;
		MediaSource* audioSource;
	};

}
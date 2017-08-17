#pragma once

#include "MediaType.hpp"


namespace wdm {


	class MediaPacket : public MediaObject
	{
	public:
		MediaPacket();
		virtual ~MediaPacket();

		MediaType GetPacketType();

	private:
		MediaType type;

	};

}
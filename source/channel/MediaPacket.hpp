#pragma once

#include "MediaType.hpp"


namespace wdm {


	class MediaPacket : public MediaObject
	{
	public:
		MediaPacket();
		virtual ~MediaPacket();

		MediaType GetPacketType();
        virtual bool IsKeyFrame();

	private:
		MediaType type;
        bool bKeyFrame;

	};

}
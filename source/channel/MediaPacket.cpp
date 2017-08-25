#include "MediaPacket.hpp"

namespace wdm {

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////

	MediaPacket::MediaPacket()
	{
	}


	MediaPacket::~MediaPacket()
	{
	}


	MediaType MediaPacket::GetPacketType()
	{
		return type;
	}

    bool MediaPacket::IsKeyFrame()
    {
        return bKeyFrame;
    }
}
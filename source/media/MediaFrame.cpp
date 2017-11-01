#include "MediaFrame.hpp"

namespace wdm {

	//////////////////////////////////////////////////////////////////////////
	// MediaFrame
	//////////////////////////////////////////////////////////////////////////

	MediaFrame::MediaFrame(MediaType type, MediaFormat format)
        :_type(type)
	{
	}


	MediaFrame::~MediaFrame()
    {
        if (_data)
        {
            delete _data;
        }
	}


	MediaType MediaFrame::GetFrameType()
	{
		return _type;
	}


    MediaFormat MediaFrame::GetFrameFormat()
    {
        return format;
    }


    uint8_t* MediaFrame::GetData()
    {
        return _data;
    }

}
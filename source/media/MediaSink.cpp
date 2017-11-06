#include "MediaSink.hpp"


namespace wdm
{

    MediaSink::MediaSink()
	{
	}

    MediaSink::~MediaSink()
	{
	}

    SinkMethod MediaSink::GetSinkMethod()
    {
        return SEND;
    }
}
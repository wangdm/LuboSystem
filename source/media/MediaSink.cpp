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


    bool MediaSink::IsSupportscale()
    {
        return false;
    }


    bool MediaSink::ISSupportCSC()
    {
        return false;
    }
}
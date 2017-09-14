#include "MediaSource.hpp"


namespace wdm
{

	MediaSource::MediaSource()
	{
	}

	MediaSource::~MediaSource()
	{
	}

    
    void MediaSource::AddMediaSink(MediaSink* sink)
    {
        if (sink==nullptr)
        {
            return;
        }
        sinks.push_back(sink);
    }


    void MediaSource::DelMediaSink(MediaSink* sink)
    {
        std::vector<MediaSink*>::iterator iter;
        for (iter = sinks.begin(); iter != sinks.end(); iter++)
        {
            if (sink = *iter)
            {
                sinks.erase(iter);
            }
        }
    }


    void MediaSource::SendFrame(MediaFrame* frame)
    {
        std::vector<MediaSink*>::const_iterator iter;
        for (iter = sinks.begin(); iter != sinks.end(); iter++)
        {
            (*iter)->OnFrame(frame);
        }
    }
}
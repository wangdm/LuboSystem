#include "MediaSource.hpp"


namespace wdm
{

	MediaSource::MediaSource()
	{
	}

	MediaSource::~MediaSource()
	{
    }


    bool MediaSource::IsExistVideo() const
    {
        return false;
    }


    bool MediaSource::IsExistAudio() const
    {
        return false;
    }


    bool MediaSource::GetVideoAttribute(VideoAttribute& attr) const
    {
        return false;
    }


    bool MediaSource::GetAudioAttribute(AudioAttribute& attr) const
    {
        return false;
    }

    
    void MediaSource::AddMediaSink(MediaSink* sink)
    {
        _LOCK(&sinkMtx);

        if (sink==nullptr)
        {
            return;
        }
        sinks.push_back(sink);
    }


    void MediaSource::DelMediaSink(MediaSink* sink)
    {
        _LOCK(&sinkMtx);

        std::vector<MediaSink*>::iterator iter;
        for (iter = sinks.begin(); iter != sinks.end(); iter++)
        {
            if (sink == *iter)
            {
                sinks.erase(iter);
                break;
            }
        }
    }


    void MediaSource::SendFrame(MediaFrame* frame)
    {
        _LOCK(&sinkMtx);

        std::vector<MediaSink*>::const_iterator iter;
        for (iter = sinks.begin(); iter != sinks.end(); iter++)
        {
            (*iter)->OnFrame(frame);
        }
    }
}
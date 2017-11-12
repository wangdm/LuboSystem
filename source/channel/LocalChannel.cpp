
#include "../platform/Platform.hpp"

#include "ChannelManager.hpp"
#include "LocalChannel.hpp"


namespace wdm
{

    LocalChannel::LocalChannel(MediaSource* videoSource, MediaSource* audioSource)
        :Channel(CHANNEL_TYPE_LOCAL)
        ,_videoSource(videoSource)
        ,_audioSource(audioSource)
    {
    }


	LocalChannel::~LocalChannel()
    {
        Uninit();
	}


    bool LocalChannel::Init(Config* config_)
    {
        if (config_ ==nullptr)
        {
            config = GetDefaultConfig();
        }
        else
        {
            config = config_;
        }
        std::vector<Object*> streamConfigs;
        streamConfigs = (*config)["streams"];
        if (streamConfigs.size()>0)
        {
            for (Object* obj : streamConfigs)
            {
                Config* streamConfig = dynamic_cast<Config*>(obj);
                if (streamConfig!=nullptr)
                {
                    MediaStream* stream = new MediaStream(this);
                    CodecContext* codec = Platform::CreateCondecContext();
                    stream->Init(streamConfig);
                    stream->SetProducer(codec);
                    streams[(*streamConfig)["name"]] = stream;
                }
            }
        }

        return true;
    }


    bool LocalChannel::Uninit()
    {
        std::map<std::string, MediaStream*>::iterator iter;
        for (iter = streams.begin(); iter != streams.end();)
        {
            MediaStream* stream = iter->second;
            iter = streams.erase(iter);
            if (stream!=nullptr)
            {
                delete stream;
            }
        }

        if (config!=nullptr)
        {
            delete config;
            config = nullptr;
        }

        channelStatus = UNINITIALIZED;
        return true;
    }


    bool LocalChannel::GetVideoAttribute(VideoAttribute& attr) const
    {
        return _videoSource->GetVideoAttribute(attr);
    }


    bool LocalChannel::GetAudioAttribute(AudioAttribute& attr) const
    {
        return _audioSource->GetAudioAttribute(attr);
    }


    bool LocalChannel::Start()
    {
        INFO("Start local channel");
        std::map<std::string, MediaStream*>::iterator iter;
        for (iter = streams.begin(); iter != streams.end(); iter++)
        {
            MediaStream* stream = iter->second;
            CodecContext* codec = dynamic_cast<CodecContext*>(stream->GetProducer());
            if (codec != nullptr)
            {
                if (_videoSource != nullptr && stream->GetStreamType() == MEDIA_TYPE_VIDEO)
                {
                    _videoSource->AddMediaSink(codec);
                }
                else if (_audioSource != nullptr && stream->GetStreamType() == MEDIA_TYPE_AUDIO)
                {
                    _audioSource->AddMediaSink(codec);
                }
            }
            else
            {
                ERROR("the Producer isn't a MediaSink instance");
            }
            stream->Start();
            ChannelManager::GetInstance()->AddEvent(stream->GetProducer());
        }
        if (_videoSource != nullptr)
        {
            _videoSource->AddMediaSink(this);
        }
        if (_audioSource != nullptr)
        {
            _audioSource->AddMediaSink(this);
        }


        if (_videoSource != nullptr)
        {
            _videoSource->Start();
        }

        if (_audioSource != nullptr)
        {
            _audioSource->Start();
        }

        return false;
    }


    bool LocalChannel::Stop()
    {
        INFO("Stop local channel");

        if (_videoSource != nullptr)
        {
            _videoSource->Stop();
        }

        if (_audioSource != nullptr)
        {
            _audioSource->Stop();
        }

        if (_videoSource != nullptr)
        {
            _videoSource->DelMediaSink(this);
        }
        if (_audioSource != nullptr)
        {
            _audioSource->DelMediaSink(this);
        }

        std::map<std::string, MediaStream*>::iterator iter;
        for (iter = streams.begin(); iter != streams.end(); iter++)
        {
            MediaStream* stream = iter->second;
            ChannelManager::GetInstance()->DelEvent(stream->GetProducer());
            stream->Stop();
            CodecContext* codec = dynamic_cast<CodecContext*>(stream->GetProducer());
            if (codec != nullptr)
            {
                if (_videoSource != nullptr && stream->GetStreamType() == MEDIA_TYPE_VIDEO)
                {
                    _videoSource->DelMediaSink(codec);
                }
                else if (_audioSource != nullptr && stream->GetStreamType() == MEDIA_TYPE_AUDIO)
                {
                    _audioSource->DelMediaSink(codec);
                }
            }
            else
            {
                ERROR("the Producer isn't a MediaSink instance");
            }
        }

        return false;
    }


    //////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////

    Config* LocalChannel::GetDefaultConfig()
    {
        Config* config = new Config();

        std::vector<Object*> streamConfigs;

        Config* majorConfig = new Config(std::string("a"));
        (*majorConfig)["name"] = "major";
        (*majorConfig)["type"] = "video";
        (*majorConfig)["width"] = 1920;
        (*majorConfig)["height"] = 1080;
        (*majorConfig)["fps"] = 30;
        (*majorConfig)["codec"] = "h264";
        (*majorConfig)["profile"] = "high";
        (*majorConfig)["bitrate"] = 4096;
        (*majorConfig)["gop"] = 30;
        streamConfigs.push_back(majorConfig);

        Config* minorConfig = new Config(std::string("b"));
        (*minorConfig)["name"] = "minor";
        (*minorConfig)["type"] = "video";
        (*minorConfig)["width"] = 640;
        (*minorConfig)["height"] = 360;
        (*minorConfig)["fps"] = 30;
        (*minorConfig)["codec"] = "h264";
        (*minorConfig)["profile"] = "high";
        (*minorConfig)["bitrate"] = 512;
        (*minorConfig)["gop"] = 30;
        streamConfigs.push_back(minorConfig);

        Config* audioConfig = new Config(std::string("c"));
        (*audioConfig)["name"] = "audio";
        (*audioConfig)["type"] = "audio";
        (*audioConfig)["channel"] = 2;
        (*audioConfig)["samplerate"] = 48000;
        (*audioConfig)["bitwide"] = 16;
        (*audioConfig)["codec"] = "aac";
        (*audioConfig)["profile"] = "LC";
        (*audioConfig)["bitrate"] = 68;
        streamConfigs.push_back(audioConfig);

        (*config)["streams"] = streamConfigs;
        
        return config;
    }
}
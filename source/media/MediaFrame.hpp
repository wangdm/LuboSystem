#pragma once

#include "MediaType.hpp"


namespace wdm {


	class MediaFrame : public MediaObject
	{
	public:
		MediaFrame(MediaType type, MediaFormat format);
		virtual ~MediaFrame();

        MediaType GetFrameType();
        MediaFormat GetFrameFormat();
        uint8_t* GetData();

    private:
        MediaType _type;

    protected:
        uint8_t* _data;
        uint32_t _dataSize;

    public:
        //common
        MediaFormat format;
        uint64_t timestamp;

        //video
        int32_t stride;
        uint32_t width;
        uint32_t height;

        //audio
        uint32_t samplesize;
        uint32_t samplerate;
        uint32_t samplebit;
        uint32_t channels;

	};

}
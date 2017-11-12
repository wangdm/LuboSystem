#pragma once

#include "MediaType.hpp"


namespace wdm {


	class MediaPacket : public MediaObject
	{
	public:
        MediaPacket(const MediaType type);
        MediaPacket(const MediaType type, const uint32_t size);
        MediaPacket(const MediaType type, const uint8_t* data, const uint32_t size);
		virtual ~MediaPacket();

		MediaType GetPacketType() const;
        bool IsKeyFrame() const;

        uint32_t Copy(const MediaPacket* packet);
        uint32_t Copy(const uint8_t* data, const uint32_t size);
        uint32_t GetPacketSize() const;
        uint8_t* GetDataPtr() const;

	private:
		MediaType _type;

        uint8_t* _data;
        uint32_t _dataSize;

    public:
        uint64_t timestamp;

        //video
        bool keyframe;
        uint32_t width;
        uint32_t height;

        //audio
        uint32_t samplesize;
        uint32_t samplerate;
        uint32_t samplebit;
        uint32_t channels;

	};

}
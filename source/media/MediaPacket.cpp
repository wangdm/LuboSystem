#include "MediaPacket.hpp"

#include <cstring>

namespace wdm {

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////

    MediaPacket::MediaPacket(const MediaType type)
        :_type(type)
        , _data(nullptr)
        , _dataSize(0)
    {
    }


    MediaPacket::MediaPacket(const MediaType type, const uint8_t* data, const uint32_t size)
        :_type(type)
        , _data(nullptr)
        , _dataSize(0)
    {
        _data = new uint8_t[size];
        if (_data!=nullptr)
        {
            _dataSize = size;
            memcpy(_data, data, _dataSize);
        }
    }


	MediaPacket::~MediaPacket()
	{
        if (_data != nullptr)
        {
            delete[] _data;
        }
	}


	MediaType MediaPacket::GetPacketType() const
	{
		return _type;
	}


    bool MediaPacket::IsKeyFrame() const
    {
        return keyframe;
    }


    uint32_t MediaPacket::Copy(const MediaPacket* packet)
    {
        if (packet==nullptr || packet->GetPacketSize()==0)
        {
            return 0;
        }
        if (_data != nullptr)
        {
            delete[] _data;
        }

        _data = new uint8_t[packet->_dataSize];
        if (_data!=nullptr)
        {
            _dataSize = packet->_dataSize;
            memcpy(_data, packet->_data, _dataSize);

            _type = packet->_type;

            keyframe = packet->keyframe;
            width = packet->width;
            height = packet->height;

            samplesize = packet->samplesize;
            samplerate = packet->samplerate;
            samplebit = packet->samplebit;
            channels = packet->channels;
        }

        return _dataSize;
    }


    uint32_t MediaPacket::Copy(const uint8_t* data, const uint32_t size)
    {
        if (data == nullptr || size == 0)
        {
            return 0;
        }
        if (_data != nullptr)
        {
            delete[] _data;
        }

        _data = new uint8_t[size];
        if (_data != nullptr)
        {
            _dataSize = size;
            memcpy(_data, data, _dataSize);
        }

        return _dataSize;
    }


    uint32_t MediaPacket::GetPacketSize() const
    {
        return _dataSize;
    }

}
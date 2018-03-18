#pragma once

#include <stdint.h>

#include <queue>

#include "../core/Mutex.hpp"

#include "../media/MediaPacket.hpp"

namespace wdm
{

    class PacketQueue
    {
    public:
        PacketQueue(uint32_t capacity = 30, bool autoDiscard = true);
        ~PacketQueue();

        virtual MediaPacket* Pop( );
        virtual bool Push(MediaPacket* packet);
        virtual void Clear();
        virtual uint32_t Discard();

        virtual uint32_t GetPacketCount();
        virtual uint32_t GetVideoCount();
        virtual uint32_t GetAudioCount();

    private:
        uint32_t nb_video;
        uint32_t nb_audio;
        uint32_t capacity;

        bool autoDiscard;

        std::priority_queue<MediaPacket*> packets;
        Mutex mtx;

    };
}
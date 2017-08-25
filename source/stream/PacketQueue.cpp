#include "PacketQueue.hpp"

namespace wdm 
{

    PacketQueue::PacketQueue(uint32_t capacity, bool autoDiscard) :
        nb_audio(0),
        nb_video(0),
        capacity(capacity),
        autoDiscard(autoDiscard)
    {

    }

    PacketQueue::~PacketQueue()
    {
        Clear();
    }

    MediaPacket* PacketQueue::Pop()
    {
        if (GetPacketCount() == 0)
        {
            return nullptr;
        }

        _LOCK(&mtx);

        MediaPacket* packet = packets.top();
        if (packet->GetPacketType() == MEDIA_TYPE_VIDEO)
        {
            nb_video--;
        }
        else if (packet->GetPacketType() == MEDIA_TYPE_AUDIO)
        {
            nb_audio--;
        }

        packets.pop();

        return packet;
    }


    bool PacketQueue::Push(MediaPacket* packet)
    {
        if (GetPacketCount()>=capacity && autoDiscard)
        {
            Discard();
        }
        else if(GetPacketCount() >= capacity)
        {
            return false;
        }

        _LOCK(&mtx);

        if (packet->GetPacketType() == MEDIA_TYPE_VIDEO)
        {
            nb_video++;
        }
        else if(packet->GetPacketType() == MEDIA_TYPE_AUDIO)
        {
            nb_audio++;
        }
        else
        {
            return false;
        }

        packets.push(packet);
        packet->Reference();

        return true;
    }


    void PacketQueue::Clear()
    {
        _LOCK(&mtx);
        while (!packets.empty())
        {
            MediaPacket* packet = Pop();
            packet->Release();
        }
    }


    uint32_t PacketQueue::Discard()
    {
        _LOCK(&mtx);

        uint32_t count = 0;
        while (!packets.empty())
        {
            MediaPacket* packet = packets.top();
            if (count!=0 && packet->IsKeyFrame())
            {
                break;

            }
            if (packet->GetPacketType() == MEDIA_TYPE_VIDEO)
            {
                nb_video--;
            }
            else if (packet->GetPacketType() == MEDIA_TYPE_AUDIO)
            {
                nb_audio--;
            }

            packets.pop();
            packet->Release();
            count++;
        }

        return count;
    }


    uint32_t PacketQueue::GetPacketCount()
    {
        _LOCK(&mtx);
        return nb_audio + nb_video;
    }


    uint32_t PacketQueue::GetVideoCount()
    {
        _LOCK(&mtx);
        return nb_video;
    }


    uint32_t PacketQueue::GetAudioCount()
    {
        _LOCK(&mtx);
        return nb_audio;
    }


}
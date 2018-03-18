
#include <sstream>
#include "../core/Log.hpp"

#include "Recorder.hpp"


namespace wdm
{

    Recorder::Recorder()
        : bneedkey(true)
    {
    }


    Recorder::~Recorder()
    {
        if (recfile.is_open())
        {
            recfile.flush();
            recfile.close();
        }
    }


    void Recorder::OnLoop()
    {
        while (!IsStopping())
        {
            MediaPacket* packet = queue.Pop();
            if (packet != nullptr)
            {
                if (bneedkey)
                {
                    if (packet->IsKeyFrame())
                    {
                        bneedkey = false;
                    }
                    else 
                    {
                        DEBUG("need key frame");
                        packet->Release();
                        continue;
                    }
                }
                DEBUG("Write packet");
                recfile.write((char*)packet->GetDataPtr(), packet->GetPacketSize());
                packet->Release();
            }
            else
            {
                Sleep(10);
            }
        }
    }


    void Recorder::OnStart()
    {
        DEBUG("Recorder start..");
        bneedkey = true;
        //std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        //std::localtime(std::chrono::system_clock::to_time_t(&now));
        static int i = 0;
        std::stringstream filename;
        filename << "record_" << (i++) << ".h264";
        recfile.open(filename.str(), std::ios::binary);
    }


    void Recorder::OnStop()
    {
        DEBUG("Recorder stop..");
        if (recfile.is_open())
        {
            recfile.flush();
            recfile.close();
        }
    }

}
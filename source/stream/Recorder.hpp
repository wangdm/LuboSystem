#pragma once

#include <fstream>
#include <chrono>
#include <ctime>

#include "../core/Thread.hpp"

#include "StreamConsumer.hpp"


namespace wdm
{

    class Recorder : public StreamConsumer
    {
    public:
        Recorder();
        virtual ~Recorder();

    protected:
        virtual void OnLoop() override;
        virtual void OnStart() override;
        virtual void OnStop() override;

    private:
        std::ofstream recfile;
        bool bneedkey;

    };
}
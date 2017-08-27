#pragma once

#include "../base/Thread.hpp"

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

    };
}
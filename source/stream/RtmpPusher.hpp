#pragma once

#include "StreamConsumer.hpp"


namespace wdm
{

    class RtmpPusher : public StreamConsumer
    {
    public:
        RtmpPusher();
        ~RtmpPusher();

    protected:
        virtual void OnLoop() override;
        virtual void OnStart() override;
        virtual void OnStop() override;

    private:

    };
}
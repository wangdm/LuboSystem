#pragma once

#include "Variant.hpp" 


namespace wdm
{

    class Thread
    {
    public:
        Thread();
        virtual ~Thread();

        virtual bool Start();
        virtual bool Stop(bool block = true);

    protected:
        virtual void Run() = 0;
        virtual bool IsStopping() final { return stopping; };

    private:
        bool stopping;
    };

}
#pragma once

#include "Variant.hpp" 

#include <pthread.h>


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
        virtual void OnLoop() = 0;
        virtual void OnStart();
        virtual void OnStop();
        virtual bool IsStopping() final { return stopping; };
    private:
        static void * Process(void *);

    private:
        bool stopping;

		pthread_t thread;

    };

}
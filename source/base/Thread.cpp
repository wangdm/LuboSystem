#include "Thread.hpp"

#include <iostream>


namespace wdm
{

    Thread::Thread()
        :stopping(true)
    {
    }


    Thread::~Thread()
    {
    }


    bool Thread::Start() 
    {
        if (stopping == true)
        {
            stopping = false;
            pthread_create(&thread, NULL, Process, this);
        }
        return true;
    }


    bool Thread::Stop(bool block)
    {
        stopping = true;

        if (block)
        {
            pthread_join(thread, NULL);
        }
        else 
        {
            pthread_detach(thread);
        }

        return true;
    }


    void* Thread::Process(void* arg)
    {
        Thread* t = (Thread*)arg;
        std::cout << "thread start" << std::endl;
        t->Run();
        std::cout << "thread stop" << std::endl;
        return NULL;
    }

}
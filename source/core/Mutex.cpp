#include"Mutex.hpp"

#include<iostream>

namespace wdm
{

    Mutex::Mutex()
    {
    }


    Mutex::~Mutex()
    {
    }


    void Mutex::Lock()
    {
        mtx.lock();
    }


    void Mutex::TryLock()
    {
        mtx.try_lock();
    }


    void Mutex::UnLock()
    {
        mtx.unlock();
    }

}
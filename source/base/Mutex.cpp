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
        std::cout << "Lock" << std::endl;
        mtx.lock();
    }


    void Mutex::TryLock()
    {
        mtx.try_lock();
    }


    void Mutex::UnLock()
    {
        mtx.unlock();
        std::cout << "UnLock" << std::endl;
    }

}
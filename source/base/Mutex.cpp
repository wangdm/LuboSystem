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
    }


    void Mutex::TryLock()
    {
    }


    void Mutex::UnLock()
    {
        std::cout << "UnLock" << std::endl;
    }

}
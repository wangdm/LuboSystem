#pragma once

namespace wdm
{

    class Mutex
    {
    public:
        Mutex();
        virtual ~Mutex();

        virtual void Lock();
        virtual void TryLock();
        virtual void UnLock();

    private:
   
    };

    class MutexWrapper
    {
    public:
        MutexWrapper(Mutex* mtx) :mtx(mtx) { mtx->Lock(); };
        ~MutexWrapper() { mtx->UnLock(); };

    private:
        Mutex* mtx;
    };

#define _LOCK(mtx) MutexWrapper __mtx_lock__(mtx)

}
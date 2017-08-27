#include "LocalChannel.hpp"


namespace wdm
{

	LocalChannel::LocalChannel()
	{
	}


	LocalChannel::~LocalChannel()
	{
	
	}


    bool LocalChannel::Init()
    {
        return true;
    }


    bool LocalChannel::UnInit()
    {
        return true;
    }


    bool LocalChannel::Start()
    {
        return Thread::Start();
    }


    bool LocalChannel::Stop(bool block)
    {
        return Thread::Stop(block);
    }


    void LocalChannel::OnLoop()
    {
        while (!IsStopping())
        {

        }
    }

}
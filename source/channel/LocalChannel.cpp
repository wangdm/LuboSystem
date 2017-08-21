#include "LocalChannel.hpp"


namespace wdm
{

	LocalChannel::LocalChannel()
	{
	}


	LocalChannel::~LocalChannel()
	{
	
	}


    bool LocalChannel::Start()
    {
        return Thread::Start();
    }


    bool LocalChannel::Stop(bool block)
    {
        return Thread::Stop(block);
    }

}
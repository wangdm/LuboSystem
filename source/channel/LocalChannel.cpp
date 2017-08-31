#include "LocalChannel.hpp"


namespace wdm
{

	LocalChannel::LocalChannel()
	{
	}


    LocalChannel::LocalChannel(std::string& config)
    {
    }


	LocalChannel::~LocalChannel()
	{
	
	}


    bool LocalChannel::Init(std::string& config)
    {
        return true;
    }


    bool LocalChannel::UnInit()
    {
        return true;
    }


    bool LocalChannel::Start()
    {
        return false;
    }


    bool LocalChannel::Stop()
    {
        return false;
    }

}
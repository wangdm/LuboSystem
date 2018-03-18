#pragma once

#include "../core/Property.hpp"
#include "../media/MediaSource.hpp"


namespace wdm
{

	class Capture : public MediaSource
	{
	public:
        virtual bool GetProperty(Property& prop) = 0;
        virtual bool SetProperty(const Property& prop) = 0;

        virtual bool IsPropertySupport(const Property& prop) = 0;

	private:

	};

}
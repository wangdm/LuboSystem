#include "MediaType.hpp"


namespace wdm {


	MediaObject::MediaObject()
		:count(1)
	{
	}


	MediaObject::~MediaObject()
	{
	}


	void MediaObject::Reference()
	{
		count++;
	}


	void MediaObject::Release()
	{
		if (--count == 0)
		{
			delete this;
		}
	}


	uint32_t MediaObject::RefCount()
	{
		return count;
	}

}
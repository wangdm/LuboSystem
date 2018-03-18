#include "Property.hpp"


namespace wdm {

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////

	Property::Property()
	{
	}


	Property::~Property()
	{

	}


    bool Property::SetProperty(const char* key, const Variant& val)
    {
        Variant* p = new Variant();
        *p = val;
        propertys[key] = p;
        return true;
    }


	bool Property::SetProperty(const std::string& key, const Variant& val)
    {
        Variant* p = new Variant();
        *p = val;
        propertys[key] = p;
		return true;
    }


	bool Property::GetProperty(const std::string& key, Variant& val) const
	{
        std::map<std::string, Variant*>::const_iterator iter = propertys.find(key);
		if (iter != propertys.end()) {
			val = *(iter->second);
			return true;
		}

		return false;
	}


	bool Property::GetProperty(const std::string key, int& val) const
	{
		Variant _val;
		if (GetProperty(key, _val))
		{
			val = _val;
			return true;
		}
		return false;
	}


	bool Property::GetProperty(const std::string& key, double& val) const
	{
		Variant _val;
		if (GetProperty(key, _val))
		{
			val = _val;
			return true;
		}
		return false;
	}


	bool Property::GetProperty(const std::string& key, std::string& val) const
	{
		Variant _val;
		if (GetProperty(key, _val))
		{
			val = (std::string)_val;
			return true;
		}
		return false;
    }


    Variant& Property::operator[](const std::string& key)
    {
        std::map<std::string, Variant*>::const_iterator iter = propertys.find(key);
        if (iter != propertys.end()) {
            return *(iter->second);
        }
        Variant* val = new Variant();
        propertys[key] = val;
        return *val;
    }


    const Variant& Property::operator[](const std::string& key) const
    {
        std::map<std::string, Variant*>::const_iterator iter = propertys.find(key);
        if (iter != propertys.end()) {
            return *(iter->second);
        }
        return Variant::nil;
    }


	bool Property::RemoveProperty(const std::string& key)
	{
		if (propertys.find(key) != propertys.end()) {
			propertys.erase(key);
			return true;
		}

		return false;
	}

}
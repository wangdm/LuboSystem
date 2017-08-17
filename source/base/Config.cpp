#include "Config.hpp"


namespace wdm {

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////

	Config::Config::Config(std::string& filename)
	{
		Load(filename);
	}


	Config::~Config()
	{

	}


	bool Config::Load(const std::string& filename)
	{
		return false;
	}


	bool Config::Save()
	{
		return false;
	}


	bool Config::SaveAs(const std::string& filename)
	{
		return false;
	}


	bool Config::SetValue(const std::string& key, const Variant& val)
	{
		configs[key] = val;
		return true;
	}


	bool Config::GetValue(const std::string& key, Variant& val)
	{
		if (configs.find(key) != configs.end()) {
			val = configs[key];
			return true;
		}

		return false;
	}


	bool Config::GetValue(const std::string& key, int& val)
	{
		Variant _val;
		if (GetValue(key, _val))
		{
			val = _val;
			return true;
		}
		return false;
	}


	bool Config::GetValue(const std::string& key, double& val)
	{
		Variant _val;
		if (GetValue(key, _val))
		{
			val = _val;
			return true;
		}
		return false;
	}


	bool Config::GetValue(const std::string& key, std::string& val)
	{
		Variant _val;
		if (GetValue(key, _val))
		{
			val = _val;
			return true;
		}
		return false;
	}


	bool Config::RemoveKey(const std::string& key)
	{
		if (configs.find(key) != configs.end()) {
			configs.erase(key);
			return true;
		}

		return false;
	}

}
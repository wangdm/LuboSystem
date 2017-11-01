#include "Config.hpp"


namespace wdm {

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////

	Config::Config::Config(const std::string& filename)
	{
		Load(filename);
	}


	Config::~Config()
    {
        Clear();
	}


	bool Config::Load(const std::string& filename)
	{
        this->filename = filename;
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


    void Config::Clear()
    {
        std::cout << "Clear config " << filename << std::endl;
        std::map<std::string, Variant*>::const_iterator iter;
        for (iter = configs.begin(); iter != configs.end();) {
            Variant* p = iter->second;
            iter = configs.erase(iter);
            if (p->type == V_OBJECT)
            {
                Config* config = dynamic_cast<Config*>((Object*)(*p));
                if (config)
                {
                    delete config;
                }
            }
            else if(p->type == V_ARRAY)
            {
                std::vector<Object*> configs = *p;
                for (Object* obj : configs)
                {
                    Config* config = dynamic_cast<Config*>(obj);
                    if (config)
                    {
                        delete config;
                    }
                }
                
            }
            delete p;
        }
    }


	bool Config::SetValue(const std::string& key, const Variant& val)
    {
        Variant* p = new Variant();
        *p = val;
		configs[key] = p;
		return true;
	}


	bool Config::GetValue(const std::string& key, Variant& val) const
	{
        std::map<std::string, Variant*>::const_iterator iter = configs.find(key);
		if (iter != configs.end()) {
			val = *(iter->second);
			return true;
		}

		return false;
	}


	bool Config::GetValue(const std::string& key, int& val) const
	{
		Variant _val;
		if (GetValue(key, _val))
		{
			val = _val;
			return true;
		}
		return false;
	}


	bool Config::GetValue(const std::string& key, double& val) const
	{
		Variant _val;
		if (GetValue(key, _val))
		{
			val = _val;
			return true;
		}
		return false;
	}


	bool Config::GetValue(const std::string& key, std::string& val) const
	{
		Variant _val;
		if (GetValue(key, _val))
		{
			val = (std::string)_val;
			return true;
		}
		return false;
	}


    bool Config::GetValue(const std::string& key, Config*& config) const
    {
        Variant _val;
        if (GetValue(key, _val))
        {
            void*p = _val;
            config = static_cast<Config*>(p);
            if (config!=nullptr)
            {
                return true;
            }
        }
        return false;
    }


    bool Config::GetValue(const std::string& key, std::vector<Config*>*& configs) const
    {
        Variant _val;
        if (GetValue(key, _val))
        {
            void*p = _val;
            configs = static_cast<std::vector<Config*>*>(p);
            if (configs != nullptr)
            {
                return true;
            }
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


    Variant& Config::operator[](const std::string& key)
    {
        std::map<std::string, Variant*>::const_iterator iter = configs.find(key);
        if (iter != configs.end()) {
            return *(iter->second);
        }
        Variant* val = new Variant();
        configs[key] = val;
        return *val;
    }


    const Variant& Config::operator[](const std::string& key) const
    {
        std::map<std::string, Variant*>::const_iterator iter = configs.find(key);
        if (iter != configs.end()) {
            return *(iter->second);
        }
        return Variant::nil;
    }


    void Config::Print() const
    {
        std::map<std::string, Variant*>::const_iterator iter;
        std::cout << "########################################" << std::endl;
        for (iter = configs.begin(); iter != configs.end(); iter++)
        {
            Variant* val = iter->second;
            switch (val->type)
            {
            case V_NULL:
                break;
            case V_BOOL:
                break;
            case V_INTEGER:
                std::cout << (iter->first) << "\t" << "V_INTEGER" << "\t" << int(*val) << std::endl;
                break;
            case V_DOUBLE:
                std::cout << (iter->first) << "\t" << "V_DOUBLE" << "\t" << double(*val) << std::endl;
                break;
            case V_STRING:
                std::cout << (iter->first) << "\t" << "V_STRING" << "\t" << std::string(*val) << std::endl;
                break;
            case V_OBJECT:
                std::cout << (iter->first) << "\t" << "V_OBJECT" << "\t" << (void*)(*val) << std::endl;
                break;
            case V_ARRAY:
                break;
            }
        }
        std::cout << "########################################" << std::endl;
    }

}
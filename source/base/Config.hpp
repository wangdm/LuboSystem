#pragma once

#include <string>
#include <vector>
#include <map>
#include <typeinfo>

#include "Object.hpp"
#include "Variant.hpp"

namespace wdm {

	class Config : public Object
    {

	public:
		Config() {};
		Config(const std::string& filename);
		~Config();

		virtual bool SetValue(const std::string& key, const Variant& val);

		virtual bool GetValue(const std::string& key, Variant& val) const;
		virtual bool GetValue(const std::string& key, int& val) const;
		virtual bool GetValue(const std::string& key, double& val) const;
		virtual bool GetValue(const std::string& key, std::string& val) const;

        virtual bool GetValue(const std::string& key, Config*& config) const;
        virtual bool GetValue(const std::string& key, std::vector<Config*>*& configs) const;

		virtual bool RemoveKey(const std::string& key);

		virtual bool Load(const std::string& filename);
		virtual bool Save();
        virtual bool SaveAs(const std::string& filename);
        virtual void Clear();
        virtual void Print() const;

        virtual Variant& operator[](const std::string& filename);
        virtual const Variant& operator[](const std::string& filename) const;

	private:
		std::string filename;
		std::map<std::string, Variant*> configs;

	};

}
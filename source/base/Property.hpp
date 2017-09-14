#pragma once

#include <string>
#include <map>

#include "Variant.hpp"

namespace wdm {

	class Property {

	public:
		Property();
		~Property();

        virtual bool SetProperty(const char* key, const Variant& val);
        virtual bool SetProperty(const std::string& key, const Variant& val);

		virtual bool GetProperty(const std::string& key, Variant& val) const;
		virtual bool GetProperty(const std::string key, int& val) const;
		virtual bool GetProperty(const std::string& key, double& val) const;
		virtual bool GetProperty(const std::string& key, std::string& val) const;

		virtual bool RemoveProperty(const std::string& key);

	private:
		std::map<std::string, Variant> propertys;

	};

}
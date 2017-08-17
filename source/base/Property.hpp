#pragma once

#include <string>
#include <map>

#include "Variant.hpp"

namespace wdm {

	class Property {

	public:
		Property();
		~Property();

		virtual bool SetProperty(const std::string& key, const Variant& val);
		virtual bool GetProperty(const std::string& key, Variant& val);
		virtual bool GetProperty(const std::string& key, int& val);
		virtual bool GetProperty(const std::string& key, double& val);
		virtual bool GetProperty(const std::string& key, std::string& val);

		virtual bool RemoveProperty(const std::string& key);

	private:
		std::map<std::string, Variant> propertys;

	};

}
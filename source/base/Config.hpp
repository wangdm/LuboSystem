#pragma once

#include <string>
#include <map>

#include "Variant.hpp"

namespace wdm {

	class Config {

	public:
		Config() {};
		Config(std::string& filename);
		~Config();

		virtual bool SetValue(const std::string& key, const Variant& val);
		virtual bool GetValue(const std::string& key, Variant& val);
		virtual bool GetValue(const std::string& key, int& val);
		virtual bool GetValue(const std::string& key, double& val);
		virtual bool GetValue(const std::string& key, std::string& val);

		virtual bool RemoveKey(const std::string& key);

		virtual bool Load(const std::string& filename);
		virtual bool Save();
		virtual bool SaveAs(const std::string& filename);


	private:
		std::string filename;
		std::map<std::string, Variant> configs;

	};

}
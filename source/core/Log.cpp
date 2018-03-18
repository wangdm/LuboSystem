#include "Log.hpp"

#include <sstream>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>

//////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////
namespace wdm {

	Logger* Logger::instance = nullptr;
	Logger* Logger::GetLogger() {

		return instance;
	}


	void Logger::Initialize(const std::string& cfilename)
	{
		if (instance == nullptr)
		{
			instance = new Logger();
		}
		else
		{

		}
	}


	void Logger::Uninitialize()
	{
		delete instance;
	}


	void Logger::log(const std::string level, const std::string filename, const std::string funcname, const int linenum, const std::string str)
	{
		using namespace std::chrono;
		std::stringstream ss;

		system_clock::time_point sysclock = system_clock::now();
		std::time_t tt = system_clock::to_time_t(sysclock);
		std::tm* tm_time = std::localtime(&tt);
		char timebuf[20];
		strftime(timebuf, 20, "%Y-%m-%d %H:%M:%S", tm_time);

		ss << "[" << level << "]";
		ss << "[" << timebuf << "]";
		ss << "[" << filename << "]";
		ss << "[" << funcname << "]";
		ss << "[" << linenum << "]:";
		ss << str;

		std::cout << ss.str() << std::endl;
	}

}
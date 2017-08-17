#pragma once

#include <string>

namespace wdm {

	class Logger {

	private:
		Logger() {};
	public:
		virtual ~Logger() {};

		static void Initialize(std::string& cfilename);
		static void Uninitialize();

		static Logger* GetLogger();

	public:
		virtual void log(std::string level, std::string filename, std::string funcname, int linenum, std::string str);

	private:
		static Logger* instance;

	};


#define DEBUG(str) do \
{ \
	Logger::GetLogger()->log("DEBUG",__FILE__,__FUNCTION__,__LINE__,str); \
} while (0)

#define INFO(str) do \
{ \
	Logger::GetLogger()->log("INFO",__FILE__,__FUNCTION__,__LINE__,str); \
} while (0)

#define WARN(str) do \
{ \
	Logger::GetLogger()->log("WARN",__FILE__,__FUNCTION__,__LINE__,str); \
} while (0)

#define ERROR(str) do \
{ \
	Logger::GetLogger()->log("ERROR",__FILE__,__FUNCTION__,__LINE__,str); \
} while (0)

#define FATAL(str) do \
{ \
	Logger::GetLogger()->log("FATAL",__FILE__,__FUNCTION__,__LINE__,str); \
} while (0)

}
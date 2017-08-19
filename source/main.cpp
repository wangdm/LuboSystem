#include "base/Log.hpp"
#include "base/Config.hpp"
#include "base/Mutex.hpp"

using namespace wdm;

void test()
{
    Mutex mtx;
    _LOCK(&mtx);
}


int main(int argc, char* [])
{
	Logger::Initialize(std::string(""));
    test();
	DEBUG("gdfgsdgfdsf");

	Config* config = new Config();

	config->SetValue("test", "strValue");


	Variant val = "varValue";
	config->SetValue("varKey", val);

	std::string strKey;
	config->GetValue("test", strKey);
	DEBUG("this value of strKey is " + strKey);

	std::string varKey;
	config->GetValue("varKey", varKey);
	DEBUG("this value of varKey is " + varKey);


	Logger::Uninitialize();
	return 0;
}
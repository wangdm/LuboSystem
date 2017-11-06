#include "base/Log.hpp"
#include "base/Config.hpp"
#include "base/Mutex.hpp"

#include "platform/Platform.hpp"
#include "channel/ChannelManager.hpp"
#include "channel/LocalChannel.hpp"

#include <iostream>

using namespace wdm;

void test()
{
//     Mutex mtx;
//     _LOCK(&mtx);

//     Variant val;
//     val = "val";
// 
//     Config config;
//     config["key1"] = "value1";
//     config["key2"] = 10;
// 
//     std::cout << std::string(config["key1"]) << std::endl;
//     std::cout << int(config["key2"]) << std::endl;

}

void test_wchar()
{
    setlocale(LC_CTYPE, "");
    wchar_t* wStr = L"aaaaaaaaa";
    size_t len = wcslen(wStr)+1;
    char* mStr = new char[len];
    size_t s = wcstombs(mStr, wStr, len);

}


int g_Quit = false;

int main(int argc, char* [])
{
    test_wchar();
	Logger::Initialize(std::string(""));
    Platform::Init("platform.conf");
    ChannelManager::Initialize("");
    ChannelManager::GetInstance()->StartLocalChannel();

    bool quit = false;
    while (!quit)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }


    ChannelManager::GetInstance()->StopLocalChannel();
    ChannelManager::Uninitialize();
    Platform::Uninit();
	Logger::Uninitialize();
	return 0;
}
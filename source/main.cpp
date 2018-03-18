#include "core/Log.hpp"
#include "core/Config.hpp"
#include "core/Mutex.hpp"

#include "platform/Platform.hpp"
#include "channel/ChannelManager.hpp"
#include "channel/LocalChannel.hpp"

#include "server/http/HttpServer.hpp"


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


void test_http()
{
    HttpServer* server = HttpServer::GetInstance();
    server->AddAcceptor("127.0.0.1", "80");

    server->Start();

    bool quit = false;
    while (!quit)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    server->Stop();
}


void test_channel()
{
    test_wchar();
    ChannelManager::Initialize("");
    ChannelManager::GetInstance()->StartLocalChannel();
    ChannelManager::GetInstance()->StartListenEvent();

    bool quit = false;
    while (!quit)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    ChannelManager::GetInstance()->StopListenEvent();
    ChannelManager::GetInstance()->StopLocalChannel();
    ChannelManager::Uninitialize();
}


int g_Quit = false;

int main(int argc, char* [])
{
    Logger::Initialize(std::string(""));
    Platform::Init("platform.conf");
    test_http();
    Platform::Uninit();
    Logger::Uninitialize();
	return 0;
}
#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include <stdint.h>

#include <vector>

#include "../base/Config.hpp"
#include "../channel/Capture.hpp"

//#define PLATFORM_WMF
#define PLATFORM_HISI

namespace wdm {

    class Platform
    {
    public:
        static bool Init(const std::string& config);
        static void Uninit();

        static int32_t EnumCapture();

    public:
        static std::vector<Capture*> audioCaptures;
        static std::vector<Capture*> videoCaptures;

    private:
        static Config* config;

    };

}


#endif

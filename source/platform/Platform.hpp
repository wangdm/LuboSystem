#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include <stdint.h>

#include <vector>

#include "../channel/Capture.hpp"

#define PLATFORM_WMF

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

    };

}


#endif

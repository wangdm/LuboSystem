#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include <stdint.h>

#include <vector>

#include "../base/Config.hpp"
#include "../channel/Capture.hpp"
#include "../media/CodecContext.hpp"


namespace wdm {

    class Platform
    {
    public:
        static bool Init(const std::string& config);
        static void Uninit();

        static int32_t EnumCapture();
        static CodecContext* CreateCondecContext();

    public:
        static std::vector<Capture*> audioCaptures;
        static std::vector<Capture*> videoCaptures;

    private:
        static Config* config;

    };

}


#endif

#ifndef _HISIERROR_H_
#define _HISIERROR_H_

#include "Platform.hpp"

#include <string>
#include <map>

namespace wdm {

    void HisiErrorInit();
    std::string HiErr(HI_S32);

}


#endif
#include "HisiError.hpp"

namespace wdm {

    std::map<HI_S32, std::string> errorMap;

    void HisiErrorInit()
    {
        errorMap[HI_ERR_VI_INVALID_DEVID] = "HI_ERR_VI_INVALID_DEVID";
    }


    std::string HiErr(HI_S32 code)
    {
        std::map<HI_S32, std::string>::const_iterator iter = errorMap.find(code);
        if (iter!= errorMap.end())
        {
            return errorMap.at(code);
        }
        else
        {
            return "Unknown Error";
        }
    }
}
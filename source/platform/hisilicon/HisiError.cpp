#include "HisiError.hpp"

namespace wdm {

    std::map<HI_S32, std::string> errorMap;

    void HisiErrorInit()
    {
        //VI
        errorMap[HI_ERR_VI_INVALID_DEVID]    = "视频输入设备号无效";
        errorMap[HI_ERR_VI_INVALID_CHNID]    = "视频输入通道号无效";
        errorMap[HI_ERR_VI_INVALID_PARA]     = "视频输入参数设置无效";
        errorMap[HI_ERR_VI_INVALID_NULL_PTR] = "输入参数空指针错误";
        errorMap[HI_ERR_VI_FAILED_NOTCONFIG] = "视频设备或通道属性未配置";
        errorMap[HI_ERR_VI_NOT_SUPPORT]      = "操作不支持";
        errorMap[HI_ERR_VI_NOT_PERM]         = "操作不允许";
        //VPSS
        errorMap[HI_ERR_VPSS_INVALID_DEVID] = "VPSS GROUP 号无效";
        errorMap[HI_ERR_VPSS_INVALID_CHNID] = "VPSS 通道号无效 ";
        errorMap[HI_ERR_VPSS_ILLEGAL_PARAM] = "VPSS 参数设置无效";
        errorMap[HI_ERR_VPSS_EXIST]         = "VPSS GROUP 已创建";
        errorMap[HI_ERR_VPSS_UNEXIST]       = "VPSS GROUP 未创建";
        errorMap[HI_ERR_VPSS_NULL_PTR]      = "输入参数空指针错误";
        errorMap[HI_ERR_VPSS_NOT_SUPPORT]   = "操作不支持";
        errorMap[HI_ERR_VPSS_NOT_PERM]      = "操作不允许";
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
            std::stringstream ss;
            ss << "Unknown Error 0x" << std::hex << code;
            return ss.str();
        }
    }
}
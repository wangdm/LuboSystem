#include "HisiError.hpp"

namespace wdm {

    std::map<HI_S32, std::string> errorMap;

    void HisiErrorInit()
    {
        //VI
        errorMap[HI_ERR_VI_INVALID_DEVID]    = "��Ƶ�����豸����Ч";
        errorMap[HI_ERR_VI_INVALID_CHNID]    = "��Ƶ����ͨ������Ч";
        errorMap[HI_ERR_VI_INVALID_PARA]     = "��Ƶ�������������Ч";
        errorMap[HI_ERR_VI_INVALID_NULL_PTR] = "���������ָ�����";
        errorMap[HI_ERR_VI_FAILED_NOTCONFIG] = "��Ƶ�豸��ͨ������δ����";
        errorMap[HI_ERR_VI_NOT_SUPPORT]      = "������֧��";
        errorMap[HI_ERR_VI_NOT_PERM]         = "����������";
        //VPSS
        errorMap[HI_ERR_VPSS_INVALID_DEVID] = "VPSS GROUP ����Ч";
        errorMap[HI_ERR_VPSS_INVALID_CHNID] = "VPSS ͨ������Ч ";
        errorMap[HI_ERR_VPSS_ILLEGAL_PARAM] = "VPSS ����������Ч";
        errorMap[HI_ERR_VPSS_EXIST]         = "VPSS GROUP �Ѵ���";
        errorMap[HI_ERR_VPSS_UNEXIST]       = "VPSS GROUP δ����";
        errorMap[HI_ERR_VPSS_NULL_PTR]      = "���������ָ�����";
        errorMap[HI_ERR_VPSS_NOT_SUPPORT]   = "������֧��";
        errorMap[HI_ERR_VPSS_NOT_PERM]      = "����������";
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
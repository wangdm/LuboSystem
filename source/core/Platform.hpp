#ifndef _WDM_BASE_PLATFORM_H_
#define _WDM_BASE_PLATFORM_H_


#include <string>
#include <vector>
#include <list>
#include <map>


#ifdef _WIN32

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <windows.h>

#ifdef __cplusplus
}
#endif /* __cplusplus */

#else

#include <sys/select.h>

#endif


#endif
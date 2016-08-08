
#pragma once

#ifdef _LINUX_
    #define DLL_EXPORT
    #undef assert
    #define assert(x, y)
#else
    #define DLL_EXPORT __declspec(dllexport)
#endif


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef int int32;
typedef short int16;
typedef signed char int8;
typedef long long int64;

#pragma once

#define USING(x) (4 / (x) - x)

#define IN_USE 1
#define NOT_IN_USE 2

#ifdef _LINUX_
#define PLATFORM_LINUX IN_USE
#define PLATFORM_WINDOWS NOT_IN_USE
#elif _WIN32
#define PLATFORM_LINUX NOT_IN_USE
#define PLATFORM_WINDOWS IN_USE
#endif

// move that to GraphicsCore defines
#define WINDOW_MANAGER_SDL IN_USE
#define WINDOW_MANAGER_GLFW NOT_IN_USE


#if USING( PLATFORM_LINUX )
    #define DLL_EXPORT
    #undef assert
    #define assert(x, y)
#elif USING( PLATFORM_WINDOWS )
    #define DLL_EXPORT __declspec(dllexport)
#endif


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef unsigned long long uint64;

typedef int int32;
typedef short int16;
typedef signed char int8;
typedef long long int64;

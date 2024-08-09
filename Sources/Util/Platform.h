#pragma once

// Windows platform
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifdef _WIN64

#define ZV_PLATFORM_IS_WIN64 1

#else

#define ZV_PLATFORM_IS_WIN32 1

#endif

// Apple platform
#elif __APPLE__
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR

#define ZV_PLATFORM_IS_IOS_SIM 1

#elif TARGET_OS_MACCATALYST

// Mac's Catalyst (ports iOS API into Mac, like UIKit).

#elif TARGET_OS_IPHONE

#define ZV_PLATFORM_IS_IOS 1

#elif TARGET_OS_MAC

#define ZV_PLATFORM_IS_OSX 1

#else
#   error "Unknown Apple platform"
#endif

// Linux platform
#elif __linux__
// TODO

// Android platform
#elif __ANDROID__
// TODO

#endif

extern "C" {
  // Target architecture
  #if defined(__x86_64__) || defined(_M_X64)
  #define X86_64
  #elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
  #define X86_32
  #elif defined(__aarch64__) || defined(_M_ARM64)
  #define AARCH64
  #endif
}

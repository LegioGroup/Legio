#pragma once

#ifdef LG_PLATFORM_WINDOWS
#if LG_BUILD_DLL
  #define LG_API __declspec(dllexport)
#else
  #define LG_API __declspec(dllimport)
#endif
#else
  #error Legio only supports Windows.
#endif

#define BIT(x) (1 << x)

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

#ifdef LG_ENABLE_ASSERTS
  #define LG_ASSERT(x, ...) { if(!(x)) { LG_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak();  } }
  #define LG_CORE_ASSERT(x, ...) { if(!(x)) { LG_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak();  } }
#else
  #define LG_ASSERT(x, ...)
  #define LG_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

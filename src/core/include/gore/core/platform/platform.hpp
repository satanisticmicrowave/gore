/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-07-26 02:40:39
 * Package: src/core/include/gore/core/platform/platform.hpp
 *
 * GORE platform detecter
 *
 * ~ gore
 */

#ifndef GORE_PLATFORM_HPP_486839
#define GORE_PLATFORM_HPP_486839

#if defined(__APPLE__)
#include <TargetConditionals.h>
#endif

#ifdef __ANDROID__
#define _gore_platform platform_id::android
#define _gore_platform_name "ANDROID"
#elif defined(_WIN32)
#define _gore_platform platform_id::windows
#define _gore_platform_name "WINDOWS"
#elif defined(__APPLE__) && TARGET_OS_IPHONE
#define _gore_platform platform_id::ios
#define _gore_platform_name "IOS"
#elif defined(__APPLE__)
#define _gore_platform platform_id::macos
#define _gore_platform_name "MACOS"
#elif defined(__linux__)
#define _gore_platform platform_id::oslinux
#define _gore_platform_name "LINUX"
#else
#define _gore_platform platform_id::unknown
#define _gore_platform_name "UNKNOWN"
#error UNKNOWN PLATFORM
#endif

#include <cstdint>
namespace gore::core::platform {

enum class platform_id : uint8_t {
  unknown = 0,
  windows,
  oslinux,
  macos,
  android,
  ios
};

struct platform_info {
  platform_id id;
  const char *name;
};

inline const constexpr platform_info current_platform = {
    .id = _gore_platform, .name = _gore_platform_name};

}; // namespace gore::core::platform

#endif // GORE_PLATFORM_HPP_486839

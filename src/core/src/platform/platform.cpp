/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-07-26 19:14:47
 * Package: src/core/src/platform/platform.cpp
 *
 * ~ gore
 */

#include "../../include/gore/core/platform/platform.hpp"

namespace gore::core::platform {

consteval platform_info current_platform() {
  return {.id = _gore_platform, .name = _gore_platform_name};
}

} // namespace gore::core::platform

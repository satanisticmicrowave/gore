/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-09-12 02:02:24
 * Package: modules/core/src/core.cpp
 *
 * ~ gore
 */

#include "../include/core.hpp"
#include <gore/module_registry.hpp>

namespace gore::core {
bool initialize() { return true; }
} // namespace gore::core

GORE_REGISTER_MODULE(core)

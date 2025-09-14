/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-09-13 17:40:31
 * Package: modules/logger/src/logger.cpp
 *
 * ~ gore
 */

#include <gore/module_registry.hpp>

namespace gore::logger {
bool initialize() { return true; }
} // namespace gore::logger

GORE_REGISTER_MODULE(logger)

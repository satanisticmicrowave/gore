/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-09-13 16:16:27
 * Package: modules/time/src/time.cpp
 *
 * ~ gore
 */

#include <gore/module_registry.hpp>

namespace gore::time {

bool initialize() { return true; }

} // namespace gore::time

GORE_REGISTER_MODULE(time)

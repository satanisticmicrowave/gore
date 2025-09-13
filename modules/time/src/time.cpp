/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-09-13 16:16:27
 * Package: modules/time/src/time.cpp
 *
 * ~ gore
 */

#include <gore/module_registry.hpp>
#include <iostream>

namespace gore::time {

bool initialize() {
  std::cout << "Hello, world from time module!\n";
  return true;
}

} // namespace gore::time

GORE_REGISTER_MODULE(time)

/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-09-15 05:56:13
 * Package: modules/core/src/module_registry/module_registry.cpp
 *
 * ~ gore
 */

#include <gore/module_registry.hpp>

#include <iostream>

namespace gore {

void register_module(const char *name) {
  std::cout << "Attempting to register module " << name << "\n";
}

} // namespace gore

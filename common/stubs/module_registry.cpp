/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-09-15 06:21:26
 * Package: common/gore/module_registry.cpp
 *
 * ~ gore
 */

#include <cstdlib>
#include <gore/module_registry.hpp>
#include <gore/weak.hpp>

#include <iostream>

namespace gore {
GORE_WEAK void register_module(const char *name) {

  std::cerr << "Attempt to register module '" << name
            << "' failed.\nGORE::core is not loaded.\n";

  std::exit(1); // NOLINT
}
} // namespace gore

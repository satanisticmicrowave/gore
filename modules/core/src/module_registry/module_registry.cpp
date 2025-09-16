/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-09-15 05:56:13
 * Package: modules/core/src/module_registry/module_registry.cpp
 *
 * ~ gore
 */

#include "../../include/module_registry/p_module_registry.hpp"

#include <cstdlib>
#include <gore/module_registry.hpp>
#include <iostream>

namespace gore {

void register_module(const char *name) { get_registry().add(name); }

bool is_module_registered(const char *name) {
  return get_registry().is_module_registered(name);
}

} // namespace gore

module_registry &get_registry() {
  static module_registry instance;
  return instance;
}

void module_registry::add(const char *name) noexcept {
  if (!this->_modules.contains(name)) {
    this->_modules.insert(name);
  } else {
    std::cerr << "Cannot load module '" << name << "'\nModule already loaded\n";
    std::exit(1); // NOLINT
  }
}

bool module_registry::is_module_registered(const char *name) noexcept {
  return this->_modules.contains(name);
}

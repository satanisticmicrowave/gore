/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-09-13 16:11:27
 * Package: common/gore/module_registry.hpp
 *
 * Unified module registry interface
 *
 * ~ gore
 */

#ifndef GORE_MODULE_REGISTRY_HPP_769087
#define GORE_MODULE_REGISTRY_HPP_769087

#include <gore/gore_api.hpp>
#include <gore/weak.hpp>

namespace gore {

GORE_API GORE_WEAK void register_module(const char *name);
}

#endif // GORE_MODULE_REGISTRY_HPP_769087

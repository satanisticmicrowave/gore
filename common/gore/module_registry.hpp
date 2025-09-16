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

#include <gore/autoexec.hpp>
#include <gore/gore_api.hpp>

namespace gore {

extern "C" GORE_API void register_module(const char *name);
extern "C" GORE_API bool is_module_registered(const char *name);

} // namespace gore

#define GORE_REGISTER_MODULE(name)                                             \
  inline constexpr bool __GORE_##name##_REGISTERED = true;                     \
  GORE_AUTOEXEC_MODULE_INITIALIZE                                              \
  void __gore__autoexec_register_module_##name() {                             \
    gore::register_module(#name);                                              \
  }
#define GORE_MODULE_IS_REGISTERED(name) (__GORE_##name##_REGISTERED)
#define GORE_MODULE_IS_RUNTIME_REGISTERED(name)                                \
  gore::is_module_registered(#name)

#endif // GORE_MODULE_REGISTRY_HPP_769087

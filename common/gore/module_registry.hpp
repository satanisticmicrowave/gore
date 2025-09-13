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

#include <functional>
#include <map>
#include <string>

namespace gore {

class module_registry {
public:
  using init_function = std::function<bool()>;

  static bool register_module(const std::string &name,
                              const init_function &init) {
    get_registry()[name] = init;
    return init();
  }

  static const std::map<std::string, init_function> &get_modules() {
    return get_registry();
  }

  static bool is_module_registered(const std::string &name) {
    return get_registry().contains(name);
  }

private:
  static std::map<std::string, init_function> &get_registry() {

    static std::map<std::string, init_function> registry;
    return registry;
  }
};

} // namespace gore

#define GORE_REGISTER_MODULE(name)                                             \
  namespace {                                                                  \
  static const bool __gore_##name##_registered =                               \
      gore::module_registry::register_module(#name, gore::name::initialize);   \
  }                                                                            \
  inline const constexpr bool __GORE_MODULE_##name##_REGISTERED = true;

#define GORE_MODULE_IS_REGISTERED(name) (__GORE_MODULE_##name##_REGISTERED)

#define GORE_MODULE_CHECK_RUNTIME(name)                                        \
  gore::module_registry::is_module_registered(#name)

#endif // GORE_MODULE_REGISTRY_HPP_769087

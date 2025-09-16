/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-09-16 11:07:30
 * Package: modules/core/include/module_registry/p_module_registry.hpp
 *
 * Private module registry container
 *
 * ~ gore
 */

#ifndef GORE_P_MODULE_REGISTRY_HPP_010050
#define GORE_P_MODULE_REGISTRY_HPP_010050

#include <unordered_set>

class module_registry final {
public:
  explicit module_registry() = default;

  void add(const char *name) noexcept;
  bool is_module_registered(const char *name) noexcept;

private:
  std::unordered_set<const char *> _modules;
};

module_registry &get_registry();

#endif // GORE_P_MODULE_REGISTRY_HPP_010050

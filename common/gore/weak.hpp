/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-09-15 06:03:39
 * Package: common/gore/weak.hpp
 *
 * Weak realization macros
 *
 * ~ gore
 */

#ifndef GORE_WEAK_HPP_905419
#define GORE_WEAK_HPP_905419

#if defined(__GNUC__) || defined(__clang__)

#define GORE_WEAK __attribute__((weak))

#elif defined(_MSC_VER)

#define GORE_WEAK                                                              \
  __pragma(comment(linker, "/alternatename:"                                   \
                           "_register_module=_register_module_default"))       \
      __declspec(selectany)

#else

#define GORE_WEAK
#error "Unsupported compiller: unable to create weak realization"
#endif

#endif // GORE_WEAK_HPP_905419

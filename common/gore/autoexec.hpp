/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-09-14 01:39:46
 * Package: common/gore/autoexec.hpp
 *
 * Automatically execute function before main()
 *
 * ~ gore
 */

#ifndef GORE_AUTOEXEC_HPP_803186
#define GORE_AUTOEXEC_HPP_803186

#if defined(_MSC_VER)
#define GORE_PRIORITY_HIGHEST A // NOLINT(cppcoreguidelines-macro-usage)
#define GORE_PRIORITY_HIGH D    // NOLINT(cppcoreguidelines-macro-usage)
#define GORE_PRIORITY_MEDIUM M  // NOLINT(cppcoreguidelines-macro-usage)
#define GORE_PRIORITY_LOW T     // NOLINT(cppcoreguidelines-macro-usage)
#define GORE_PRIORITY_LOWEST Z  // NOLINT(cppcoreguidelines-macro-usage)
#elif defined(__GNUC__) || defined(__clang__)
#define GORE_PRIORITY_HIGHEST 101 // NOLINT(cppcoreguidelines-macro-usage)
#define GORE_PRIORITY_HIGH 250    // NOLINT(cppcoreguidelines-macro-usage)

#define GORE_PRIORITY_MEDIUM 500   // NOLINT(cppcoreguidelines-macro-usage)
#define GORE_PRIORITY_LOW 1000     // NOLINT(cppcoreguidelines-macro-usage)
#define GORE_PRIORITY_LOWEST 65535 // NOLINT(cppcoreguidelines-macro-usage)
#else

#error "Unsupported compiler: define GORE_PRIORITY_*"
#endif

#if defined(_MSC_VER)
#define GORE_AUTOEXEC_0()                                                      \
  __pragma(section(".CRT$XCU", read)) __declspec(allocate(                     \
      ".CRT$XCU")) static void __stdcall // NOLINT(cppcoreguidelines-macro-usage)

#define GORE_AUTOEXEC_1(prio)                                                  \
  __pragma(section(".CRT$XC" #prio, read)) __declspec(allocate(                \
      ".CRT$XC" #prio)) static void __stdcall // NOLINT(cppcoreguidelines-macro-usage)

#elif defined(__GNUC__) || defined(__clang__)
#define GORE_AUTOEXEC_0()                                                      \
  __attribute__((constructor)) // NOLINT(cppcoreguidelines-macro-usage)

#define GORE_AUTOEXEC_1(prio)                                                  \
  __attribute__((constructor(prio))) // NOLINT(cppcoreguidelines-macro-usage)

#else
#define GORE_AUTOEXEC_0() static // NOLINT(cppcoreguidelines-macro-usage)

#define GORE_AUTOEXEC_1(prio) static // NOLINT(cppcoreguidelines-macro-usage)
#endif

#define GORE_AUTOEXEC GORE_AUTOEXEC_0() // NOLINT(cppcoreguidelines-macro-usage)

#define GORE_AUTOEXEC_PRIO(p)                                                  \
  GORE_AUTOEXEC_1(p) // NOLINT(cppcoreguidelines-macro-usage)

#endif // GORE_AUTOEXEC_HPP_803186
